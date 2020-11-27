//
// Created by nni on 14.01.19.
//

#pragma once

#ifdef __ANDROID__
#include <opus.h>
#else
#include <opus/opus.h>
#endif
#include "opus_base_wrapper.h"
#include <cstdint>

class OpusEncoderWrapper : public OpusBaseWrapper {

private:



    OpusEncoder * _encoder_state = nullptr;

    void safeDestrustryEncoderState();

    bool initialize();

public:

    static constexpr size_t _sample_size = sizeof(int16_t);
    static constexpr int _sampleing_rate = 16000;
    static constexpr int _number_of_frames = _sampling_period * static_cast<float>(_sampleing_rate);//480*4;
    static constexpr size_t _compession_ratio = _sampleing_rate*_channels* _sample_size*8/_compressed_bit_rate;
    static constexpr size_t _chunck_size = _number_of_frames*_channels*_sample_size;

    OpusEncoderWrapper();
    ~OpusEncoderWrapper();

    //encode data, 1: returns (positive) size of compressed data if success else negative error code
    opus_int32 encodeFloatData(const float * uncompressed_audio, size_t number_of_frames, unsigned char * compressed_audio, opus_int32 max_compression_size_in_bytes);
    opus_int32 encodeData(const int16_t * uncompressed_audio, size_t number_of_frames, unsigned char * compressed_audio, opus_int32 max_compression_size_in_bytes);

    bool resetState();
};


