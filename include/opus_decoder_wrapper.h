//
// Created by nni on 16.01.19.
//

#pragma once

#ifdef __ANDROID__
#include <opus.h>
#else
#include <opus/opus.h>
#endif
#include "opus_base_wrapper.h"

class OpusDecoderWrapper : public OpusBaseWrapper {

private:

    OpusDecoder * _decoder_state = nullptr;

    void safeDestroyDecoderState();

    bool initialize();

public:

    static constexpr size_t _sample_size = sizeof(float);
    static constexpr int _sampleing_rate = 48000;
    static constexpr int _number_of_frames = _sampling_period * static_cast<float>(_sampleing_rate);//480*4;
    static constexpr size_t _compession_ratio = _sampleing_rate*_channels* _sample_size*8/_compressed_bit_rate;
    static constexpr size_t _chunck_size = _number_of_frames*_channels*_sample_size;

    opus_int32 decodeFloatData(const unsigned char * compressed_audio, opus_int32 compressed_size_in_bytes,
                               float * uncompressed_audio, int number_of_frames, int decode_with_fec);

    bool resetState();

    OpusDecoderWrapper();
    ~OpusDecoderWrapper();

};


