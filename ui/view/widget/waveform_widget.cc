//
// Created by wangrl2016 on 2023/6/2.
//

#include <QPainter>
#include <glog/logging.h>
#include "waveform_widget.h"

namespace ui {
    WaveformWidget::WaveformWidget(QWidget* parent) : QWidget(parent) {

    }

    void WaveformWidget::paintEvent(QPaintEvent* event) {
        QPainter painter(this);
        // painter.setBrush(QBrush(0xFF3A3A));
        // painter.drawRect(rect());

        if (decoder_) {
            int channel_count = decoder_->SourceChannelCount();
            int frames_size = decoder_->GetNumberOfFrames();
            double duration = decoder_->GetDuration().InSecondsF();

            int width = rect().width();
            int height = rect().height();
            int middle = int(height / 2);

            int total_frames = audio_bus_->frames();
            int gap =  total_frames / width;

            if (rect().width() != current_rect_.width() ||
                    rect().height() != current_rect_.height()) {
                current_rect_ = rect();

                new_image_ = std::make_unique<QImage>(current_rect_.width(),
                                                      current_rect_.height(),
                                                      QImage::Format_ARGB32);
                for (int i = 0; i < height; i++) {
                    new_image_->setPixel(0, i, 0);
                    new_image_->setPixel(width - 1, i, 0);
                }

                for (int i = 1; i < width; i++) {
                    // 找到每个点的最大值和最小值
                    int current = total_frames * i / width;
                    float min_val = std::numeric_limits<float>::max();
                    float max_val = std::numeric_limits<float>::min();
                    for (int j = current - gap / 2; j < current + gap / 2; j++) {
                        for (int k = 0; k < channel_count; k++) {
                            float value = audio_bus_->channel(k)[j];
                            // LOG(INFO) << "Value " << value;
                            if (min_val > value)
                                min_val = value;
                            if (max_val < value)
                                max_val = value;
                        }
                    }

                    // LOG(INFO) << "Max val " << max_val << ", min val " << min_val;

                    // 向上绘制
                    int map_value = int(std::round(std::abs(max_val) * float(middle) / 2.0f));
                    for (int j = middle / 2; j >= 0; j--) {
                        if (j > middle / 2 - map_value)
                            new_image_->setPixel(i, j, 0xFF3A3A);
                        else
                            new_image_->setPixel(i, j, 0);
                    }

                    // 向下绘制
                    map_value = int(std::round(std::abs(min_val) * float(middle) / 2.0f));
                    for (int j = middle / 2; j < middle; j++) {
                        if (j < middle / 2 + map_value)
                            new_image_->setPixel(i, j, 0xFF3A3A);
                        else
                            new_image_->setPixel(i, j, 0);
                    }
                }

                current_image_ = std::move(new_image_);
            }

            painter.drawImage(current_rect_, *current_image_);
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