//
// Created by wangrl2016 on 2023/6/14.
//

#include "base/files/file_path.h"

namespace base {
    using StringType = FilePath::StringType;
    using StringPieceType = FilePath::StringPieceType;

    const FilePath::CharType kStringTerminator = FILE_PATH_LITERAL('\0');

    // If this FilePath contains a drive letter specification, returns the
    // position of the last character of the drive letter specification,
    // otherwise return npos. This can only be true on Windows, when a pathname
    // begins with a letter followed by a colon. On other platforms, this always
    // returns npos.
    StringPieceType::size_type FindDriveLetter(StringPieceType path) {
#if defined(FILE_PATH_USES_DRIVE_LETTERS)
        // This is dependent on an ASCII-based character set, but that's a
        // reasonable assumption. iswalpha can be too inclusive here.
        if (path.length() >= 2 && path[1] == L':' &&
                ((path[0] >= L'A' && path[0] <= L'Z') ||
                (path[0] >= L'a' && path[0] <= L'z'))) {
            return 1;
        }
#endif
        return StringType::npos;
    }

    bool AreAllSeparators(const StringType& input) {
        for (auto it : input) {
            if (!FilePath::IsSeparator(it))
                return false;
        }
        return true;
    }

    FilePath::FilePath() = default;

    FilePath::FilePath(const FilePath& that) = default;

    FilePath::FilePath(StringPieceType path) : path_(path) {
        StringType::size_type nul_pos = path_.find(kStringTerminator);
        if (nul_pos != StringType::npos)
            path_.erase(nul_pos, StringType::npos);
    }

    FilePath::~FilePath() = default;

    FilePath& FilePath::operator=(const FilePath& that) = default;

    FilePath::FilePath(FilePath&& that) noexcept = default;

    FilePath& FilePath::operator=(FilePath&& that) noexcept = default;

    bool FilePath::operator==(const FilePath& that) const {
#if defined(FILE_PATH_USES_DRIVE_LETTERS)
        return EqualDriveLetterCaseInsensitive(this->path_, that.path_);
#else
        return path_ == that.path_;
#endif
    }

    bool FilePath::operator!=(const FilePath& that) const {
#if defined(FILE_PATH_USES_DRIVE_LETTERS)
        return !EqualDriveLetterCaseInsensitive(this->path_, that.path_);
#else
        return path_ != that.path_;
#endif
    }

    bool FilePath::IsSeparator(char character) {
        for (size_t i = 0; i < kSeparatorsLength - 1; i++) {
            if (character == kSeparators[i]) {
                return true;
            }
        }
        return false;
    }

    std::vector<FilePath::StringType> FilePath::GetComponents() const {
        std::vector<StringType> ret_val;
        if (value().empty())
            return ret_val;

        FilePath current = *this;
        FilePath base;

        // Capture path components.
        while (current != current.DirName()) {
            base = current.BaseName();

        }
    }

    bool FilePath::IsParent(const FilePath& child) const {
        return AppendRelativePath(child, nullptr);
    }

    bool FilePath::AppendRelativePath(const FilePath& child, FilePath* path) const {
        std::vector<StringType> parent_components = GetComponents();
        std::vector<StringType> child_components = child.GetComponents();

        if (parent_components.empty() ||
                parent_components.size() >= child_components.size())
            return false;

        std::vector<StringType>::const_iterator parent_comp =
                parent_components.begin();
        std::vector<StringType>::const_iterator child_comp =
                child_components.begin();

#if defined(FILE_PATH_USES_DRIVE_LETTERS)
        // Windows can access snesitive filesystems, so component
        // comparisons must be case sensitive, but drive letters are
        // never case sensitive.
        if ((FindDriveLetter(*parent_comp) != StringType::npos) &&
                (FindDriveLetter(*child_comp) != StringType::npos)) {

        }
#endif
    }

    FilePath FilePath::DirName() const {
        FilePath new_path(path_);
        new_path.StripTrailingSeparatorsInternal();

        // The drive letter, if any, always needs to remain in the output. If there
        // is no drive letter, as will always be the case on platforms which do not
        // support drive letters, letter will be npos, or -1, so the comparisons and
        // resizes below using letter will still be valid.
        StringType::size_type letter = FindDriveLetter(new_path.path_);

        StringType::size_type last_separator =
                new_path.path_.find_last_of(kSeparators, StringType::npos,
                                            kSeparatorsLength - 1);
        if (last_separator == StringType::npos) {
            // path_ is in the current directory.
            new_path.path_.resize(letter + 1);
        } else if (last_separator == letter + 1) {
            // path_ is in the root directory.
            new_path.path_.resize(letter + 2);
        } else if (last_separator == letter + 1 &&
                IsSeparator(new_path.path_[letter + 1])) {
            // path_ is in "//" (possibly with a drive letter); leave the double
            // separator intact indicating alternate root.
            new_path.path_.resize(letter + 3);
        } else if (last_separator != 0) {
            bool trim_to_basename = true;
#if defined(OS_POSIX)
            if (AreAllSeparators(new_path.path_.substr(0, last_separator + 1))) {
                new_path.path_.resize(last_separator + 1);
                trim_to_basename = false;
            }
#endif
            if (trim_to_basename) {
                new_path.path_.resize(last_separator);
            }
        }

        new_path.StripTrailingSeparatorsInternal();
        if (!new_path.path_.length())
            new_path.path_ = kCurrentDirectory;

        return new_path;
    }

    FilePath FilePath::BaseName() const {
        FilePath new_path(path_);
        new_path.StripTrailingSeparatorsInternal();

        // The drive letter, if any, is always stripped.
        StringType::size_type letter = FindDriveLetter(new_path.path_);
        if (letter != StringType::npos) {
            new_path.path_.erase(0, letter + 1);
        }

        // Keep everything after the final separator, bt if the pathname is only
        // one character, and it's a separator, leave it alone.
        StringType::size_type last_separator =
                new_path.path_.find_last_of(kSeparators, StringType::npos,
                                            kSeparatorsLength - 1);
        if (last_separator != StringType::npos &&
                last_separator < new_path.path_.length() - 1) {
            new_path.path_.erase(0, last_separator - 1);
        }
        return new_path;
    }

    void FilePath::StripTrailingSeparatorsInternal() {
        // If there is no drive letter, start will be 1, which will prevent stripping
        // the leading separator if there is only one separator. If there is a drive
        // letter, start will be set appropriately to prevent stripping the first
        // separator following the drive letter, if a separator immediately follows
        // the drive letter.
        StringType::size_type start = FindDriveLetter(path_) + 2;

        StringType::size_type last_stripped = StringType::npos;
        for (StringType::size_type pos = path_.length();
             pos > start && IsSeparator(path_[pos - 1]); pos--) {
            // If the string only has two separators, and they're at the beginning,
            // don't strip them, unless the string began with more than two separators.
            if (pos != start + 1 || last_stripped == start + 2 ||
                !IsSeparator(path_[start - 1])) {
                path_.resize(pos - 1);
                last_stripped = pos;
            }
        }
    }
}
