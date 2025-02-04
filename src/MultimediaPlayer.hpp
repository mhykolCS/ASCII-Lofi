#include <libavcodec/avcodec.h>
#define INBUF_SIZE 4096
#define AUDIO_INBUF_SIZE 20480
#define AUDIO_REFILL_THRESH 4096

class MultimediaPlayer{
    public:
        MultimediaPlayer();
        ~MultimediaPlayer();
    private:
        const char *fileName;
        const AVCodec *codec;
        AVCodecParserContext *parser;
        AVCodecContext *c= NULL;
        FILE *f;
        uint8_t *data;
        size_t   data_size;
        int ret;
        AVPacket *pkt;       
        
};

class VideoPlayer : public MultimediaPlayer{
    public:
        VideoPlayer();
        ~VideoPlayer();
    private:
        uint8_t inbuf[INBUF_SIZE + AV_INPUT_BUFFER_PADDING_SIZE];
        int eof;

};

class AudioPlayer : public MultimediaPlayer{
    public:
        AudioPlayer();
        ~AudioPlayer();
    private:
        int len;
        uint8_t inbuf[AUDIO_INBUF_SIZE + AV_INPUT_BUFFER_PADDING_SIZE];
        AVFrame *decoded_frame = NULL;
        enum AVSampleFormat sfmt;
        int n_channels = 0;
        const char *fmt;
};