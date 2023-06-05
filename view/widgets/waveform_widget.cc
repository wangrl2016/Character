//
// Created by wangrl2016 on 2023/6/2.
//

#include <QPainter>
#include <glog/logging.h>
#include "view/widgets/waveform_widget.h"
#include "media/filters/ffmpeg_audio_decoder.h"

namespace view {
    WaveformWidget::WaveformWidget(QWidget* parent) : QWidget(parent) {

    }

    void WaveformWidget::paintEvent(QPaintEvent* event) {
        QPainter painter(this);
        painter.setBrush(QBrush(0xFF3A3A));
        painter.drawRect(rect());
    }

    void WaveformWidget::LoadAudio(const QString& file_path) {
        std::shared_ptr<media::FFmpegAudioDecoder> decoder =
                std::make_shared<media::FFmpegAudioDecoder>();
        if (!decoder->OpenFromFile(file_path.toStdString()))
            return;

        audio_bus_ = decoder->ReadFrames();

        if (!audio_bus_)
            return;

        LOG(INFO) << audio_bus_->frames();

        update();
    }
}