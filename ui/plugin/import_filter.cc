//
// Created by wangrl2016 on 2023/6/18.
//

#include <QMessageBox>
#include <glog/logging.h>
#include "ui/plugin/import_filter.h"

namespace ui {
    ImportFilter::ImportFilter(const QString& file_name,
                               const Descriptor* descriptor) :
                               Plugin(descriptor, nullptr),
                               file_(file_name) {
    }

    void ImportFilter::Import(const QString& file_to_import,
                              TrackContainer* tc) {
        LOG(INFO) << __FUNCTION__;
        bool successful = false;


    }

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
