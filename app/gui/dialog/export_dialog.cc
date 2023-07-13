//
// Created by wangrl2016 on 2023/7/13.
//

#include <QDir>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStandardPaths>
#include <glog/logging.h>
#include "app/gui/dialog/export_dialog.h"
#include "media/filters/ffmpeg_video_encoder.h"

namespace app {
    ExportDialog::ExportDialog(QWidget* parent) :
            QDialog(parent) {
        setAttribute(Qt::WA_DeleteOnClose);

        auto* layout = new QVBoxLayout(this);
        export_button_ = new QPushButton(this);
        connect(export_button_, &QPushButton::clicked, this, &ExportDialog::Export);
        layout->addWidget(export_button_);

        setLayout(layout);
    }

    ExportDialog::~ExportDialog() {

    }

    void ExportDialog::Export() {
        LOG(INFO) << __FUNCTION__;

        std::shared_ptr<media::FFmpegVideoEncoder> video_encoder =
                std::make_shared<media::FFmpegVideoEncoder>();

        QString desktop_dir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
        video_encoder->Open(QString(desktop_dir + QDir::separator() + QString("test.mp4")).toStdString());
        video_encoder->Encode();
        video_encoder->Close();
    }
}
