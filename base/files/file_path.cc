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
