//
// Created by nni on 14.01.19.
//

#include <cstdlib>
#include <android/log.h>
#include "opus_encoder_wrapper.h"

OpusEncoderWrapper::OpusEncoderWrapper()
{
    initialize();
}

OpusEncoderWrapper::~OpusEncoderWrapper()
{
    safeDestrustryEncoderState();
}

bool OpusEncoderWrapper::initialize()
{
    int error_code;

    if(_encoder_state == nullptr) {

        // creating encoder structure

        //_encoder_state = opus_encoder_create(_sampleing_rate, _channels, OPUS_APPLICATION_VOIP, &error_code);
        _encoder_state = opus_encoder_create(16000, _channels, OPUS_APPLICATION_VOIP, &error_code);

        if(error_code != OPUS_OK)
        {
            safeDestrustryEncoderState();
            __android_log_print(ANDROID_LOG_ERROR, "OpusEncoder", "Opus failed to create encoder, returned opus error code %d", error_code);

            return false;
        }

        // setting bitrate

        error_code = opus_encoder_ctl(_encoder_state, OPUS_SET_BITRATE(_compressed_bit_rate));

        if(error_code != OPUS_OK)
        {
            safeDestrustryEncoderState();
            __android_log_print(ANDROID_LOG_ERROR, "OpusEncoder", "Opus failed to set desired bitrate, returned opus error code %d", error_code);

            return false;
        }

        if(OpusBaseWrapper::_use_fec)
        {
            error_code = opus_encoder_ctl(_encoder_state, OPUS_SET_INBAND_FEC(1));

            if(error_code != OPUS_OK)
            {
                safeDestrustryEncoderState();
                __android_log_print(ANDROID_LOG_ERROR, "OpusEncoder", "Opus failed turn on fec, returned opus error code %d", error_code);

                return false;
            }

            error_code = opus_encoder_ctl(_encoder_state, OPUS_SET_PACKET_LOSS_PERC(OpusBaseWrapper::packet_lost_percantage));

            if(error_code != OPUS_OK)
            {
                safeDestrustryEncoderState();
                __android_log_print(ANDROID_LOG_ERROR, "OpusEncoder", "Opus failed to set packet loss percentage, returned opus error code %d", error_code);

                return false;
            }
        }

    }

    return true;

}

void OpusEncoderWrapper::safeDestrustryEncoderState()
{
    if(_encoder_state != nullptr)
    {
        opus_encoder_destroy(_encoder_state);

        _encoder_state = nullptr;
    }
}

opus_int32 OpusEncoderWrapper::encodeFloatData(const float * uncompressed_audio, size_t number_of_frames,unsigned char * compressed_audio, opus_int32 max_compression_size_in_bytes)
{
    if(number_of_frames != static_cast<size_t >(_number_of_frames))
    {
        __android_log_print(ANDROID_LOG_DEBUG, "OpusEncoder", "Warning: compressing %lu frames when %d is the optimal number of frames", number_of_frames, _number_of_frames);
    }

    return opus_encode_float(_encoder_state, uncompressed_audio, number_of_frames, compressed_audio, max_compression_size_in_bytes);
}

opus_int32 OpusEncoderWrapper::encodeData(const int16_t * uncompressed_audio, size_t number_of_frames, unsigned char * compressed_audio, opus_int32 max_compression_size_in_bytes)
{
    if(number_of_frames != static_cast<size_t >(_number_of_frames))
    {
        __android_log_print(ANDROID_LOG_DEBUG, "OpusEncoder", "Warning: compressing %lu frames when %d is the optimal number of frames", number_of_frames, _number_of_frames);
    }

    return opus_encode(_encoder_state, uncompressed_audio, number_of_frames, compressed_audio, max_compression_size_in_bytes);
}