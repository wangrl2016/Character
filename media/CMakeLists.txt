set(MEDIA_LIBRARY_SOURCES
        media/base/audio_bus.cc
        media/base/audio_bus.h
        media/base/audio_constant.h
        media/base/audio_parameters.cc
        media/base/audio_parameters.h
        media/base/video_parameters.cc
        media/base/video_parameters.h
        media/filters/ffmpeg_audio_decoder.cc
        media/filters/ffmpeg_audio_decoder.h
        media/filters/ffmpeg_audio_encoder.cc
        media/filters/ffmpeg_audio_encoder.h
        media/filters/ffmpeg_video_decoder.cc
        media/filters/ffmpeg_video_decoder.h
        media/filters/ffmpeg_video_encoder.cc
        media/filters/ffmpeg_video_encoder.h
        PARENT_SCOPE
        )

set(MEDIA_LIBRARY_TEST_SOURCES
        media/base/audio_bus_test.cc
        media/filters/ffmpeg_audio_decoder_test.cc
        media/filters/ffmpeg_video_encoder_test.cc

        PARENT_SCOPE
        )
