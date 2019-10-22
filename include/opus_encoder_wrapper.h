//
// Created by nni on 14.01.19.
//

#ifndef BINAURALRADIO_OPUS_ENCODER_WRAPPER_H
#define BINAURALRADIO_OPUS_ENCODER_WRAPPER_H

#include <opus.h>
#include "opus_base_wrapper.h"

class OpusEncoderWrapper : public OpusBaseWrapper {

private:



    OpusEncoder * _encoder_state = nullptr;

    void safeDestrustryEncoderState();

    bool initialize();

public:

    OpusEncoderWrapper();
    ~OpusEncoderWrapper();

    //encode data, 1: returns (positive) size of compressed data if success else negative error code
    opus_int32 encodeFloatData(const float * uncompressed_audio, size_t number_of_frames, unsigned char * compressed_audio, opus_int32 max_compression_size_in_bytes);
    opus_int32 encodeData(const int16_t * uncompressed_audio, size_t number_of_frames, unsigned char * compressed_audio, opus_int32 max_compression_size_in_bytes);
};


#endif //BINAURALRADIO_OPUS_ENCODER_WRAPPER_H
