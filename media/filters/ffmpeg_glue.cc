//
// Created by wangrl2016 on 2023/8/20.
//

#include <cstdint>
#include "media/filters/ffmpeg_glue.h"

namespace media {
    class FFmpegURLProtocol {
    public:
        // Read the given amount of bytes into data, returns the number of bytes read
        // if successful, kReadError otherwise.
        virtual int Read(int size, uint8_t* data) = 0;

        // Returns true and the current file position for this file, false if the
        // file position could not be retrieved.
        virtual bool GetPosition(int64_t* position_out) = 0;

        // Returns true if the file position could be set, false otherwise.
        virtual bool SetPosition(int64_t position) = 0;

        // Returns true and the file size, false if the file size could not be
        // retrieved.
        virtual bool GetSize(int64_t* size_out) = 0;

        // Returns false if this protocol supports random seeking.
        virtual bool IsStreaming() = 0;
    };

    class FFmpegGlue {
    public:
        // See file documentation for usage.  |protocol| must outlive FFmpegGlue.
        explicit FFmpegGlue(FFmpegURLProtocol* protocol);

        FFmpegGlue(const FFmpegGlue&) = delete;
        FFmpegGlue& operator=(const FFmpegGlue&) = delete;

        ~FFmpegGlue();

        // Opens an AVFormatContext specially prepared to process reads and seeks
        // through the FFmpegURLProtocol provided during construction.
        // |is_local_file| is an optional parameter used for metrics reporting.
        bool OpenContext(bool is_local_file = false);

        // AVFormatContext* format_context() { return format_context_; }

    private:
        bool open_called_ = false;
    };
}
