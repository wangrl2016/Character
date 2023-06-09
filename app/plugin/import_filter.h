//
// Created by wangrl2016 on 2023/6/18.
//

#ifndef CHARACTER_IMPORT_FILTER_H
#define CHARACTER_IMPORT_FILTER_H

#include <QFile>
#include "app/plugin/plugin.h"

namespace app {
    class ImportFilter : public Plugin {
    public:
        ImportFilter(const QString& file_name,
                     const Descriptor* descriptor);

        ~ImportFilter() override = default;

        // Tries to import given file to given track-container by having all
        // available import-filters to try to import the file.
        static void Import(const QString& file_to_import);

    protected:
        virtual bool TryImport() = 0;

        [[nodiscard]] const QFile& file() const { return file_; }

        bool OpenFile();

        inline void CloseFile() { file_.close(); }

        inline int ReadByte() {
            unsigned char c;
            if (file_.getChar((char*)&c)) {
                return static_cast<int>(c);
            }
            return -1;
        }

        inline int ReadBlock(char* data, int len) {
            return int(file_.read(data, len));
        }

        inline QByteArray ReadAllData() {
            file_.seek(0);
            return file_.readAll();
        }
    private:
        QFile file_;
    };
}

#endif //CHARACTER_IMPORT_FILTER_H
