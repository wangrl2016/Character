//
// Created by wangrl2016 on 2023/6/18.
//

#include <QMessageBox>
#include "ui/plugin/import_filter.h"

namespace ui {
    bool ImportFilter::OpenFile() {
        if (!file_.open(QFile::ReadOnly)) {
            QMessageBox::critical(
                    nullptr,
                    tr("Could not open file"),
                    tr("Could not open file %1 for reading.\n"
                       "Please make sure you have read permission "
                       " to the file and the directory containing "
                       "the file and try again!").arg(file_.fileName()),
                    QMessageBox::Ok,
                    QMessageBox::NoButton);
            return false;
        }
        return true;
    }
}
