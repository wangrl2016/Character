//
// Created by wangrl2016 on 2023/6/2.
//

#include <QPainter>
#include <glog/logging.h>
#include "view/widgets/waveform_widget.h"

namespace view {
    WaveformWidget::WaveformWidget(QWidget* parent) : QWidget(parent) {

    }

    void WaveformWidget::paintEvent(QPaintEvent* event) {
        QPainter painter(this);
        painter.setBrush(QBrush(0xFF3A3A));
        painter.drawRect(rect());

        if (decoder_) {
            int channel_count = decoder_->SourceChannelCount();
            int frames_size = decoder_->GetNumberOfFrames();
            double duration = decoder_->GetDuration().InSecondsF();

            int width = rect().width();
            int height = rect().height();
            int middle = int(height / 2);

            int gap = audio_bus_->frames() / width;

            for (int i = 1; i < width; i++) {
                // 找到每个点的最大值和最小值
            }

        }
    }

    void WaveformWidget::LoadAudio(const QString& file_path) {
        decoder_ = std::make_shared<media::FFmpegAudioDecoder>();
        if (!decoder_->OpenFromFile(file_path.toStdString()))
            return;

        audio_bus_ = decoder_->ReadFrames();

        if (!audio_bus_)
            return;

        LOG(INFO) << audio_bus_->frames();

        update();
    }
}