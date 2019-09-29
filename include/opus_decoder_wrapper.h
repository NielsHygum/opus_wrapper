//
// Created by nni on 16.01.19.
//

#ifndef BINAURALRADIO_OPUS_DECODER_WRAPPER_H
#define BINAURALRADIO_OPUS_DECODER_WRAPPER_H

#include <opus.h>
#include "opus_base_wrapper.h"

class OpusDecoderWrapper : public OpusBaseWrapper {

private:

    OpusDecoder * _decoder_state = nullptr;

    void safeDestroyDecoderState();

    bool initialize();

public:

    opus_int32 decodeFloatData(const unsigned char * compressed_audio, opus_int32 compressed_size_in_bytes,
                               float * uncompressed_audio, int number_of_frames, int decode_with_fec);

    bool resetState();

    OpusDecoderWrapper();
    ~OpusDecoderWrapper();

};


#endif //BINAURALRADIO_OPUS_DECODER_WRAPPER_H
