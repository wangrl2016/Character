//
// Created by wangrl2016 on 2023/6/2.
//

#ifndef CHARACTER_WAVEFORM_WIDGET_H
#define CHARACTER_WAVEFORM_WIDGET_H

#include <QWidget>
#include "media/base/audio_bus.h"
#include "media/filters/ffmpeg_audio_decoder.h"

namespace ui {
    class WaveformWidget : public QWidget {
    public:
        explicit WaveformWidget(QWidget* parent);

        void paintEvent(QPaintEvent *event) override;

        void LoadAudio(const QString& file_path);

    private:
        std::unique_ptr<media::AudioBus> audio_bus_;
        std::shared_ptr<media::FFmpegAudioDecoder> decoder_;

        QRect current_rect_;
        std::unique_ptr<QImage> current_image_;
        std::unique_ptr<QImage> new_image_;
    };
}

#endif //CHARACTER_WAVEFORM_WIDGET_H
