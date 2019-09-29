//
// Created by nni on 16.01.19.
//

#include <android/log.h>
#include "opus_decoder_wrapper.h"

void OpusDecoderWrapper::safeDestroyDecoderState()
{
    if(_decoder_state != nullptr)
    {
        opus_decoder_destroy(_decoder_state);

        _decoder_state = nullptr;
    }
}

bool OpusDecoderWrapper::initialize()
{
    int error_code;

    if(_decoder_state == nullptr) {

        // creating encoder structure

        _decoder_state = opus_decoder_create(_sampleing_rate, _channels, &error_code);

        if (error_code != OPUS_OK) {
            safeDestroyDecoderState();
            __android_log_print(ANDROID_LOG_ERROR, "OpusDecoder",
                                "Opus failed to create decoder, returned opus error code %d",
                                error_code);

            return false;
        }
    }

    return true;
}

opus_int32 OpusDecoderWrapper::decodeFloatData(const unsigned char * compressed_audio, opus_int32 compressed_size_in_bytes,
                           float * uncompressed_audio, int number_of_frames, int decode_with_fec)
{
    return opus_decode_float(_decoder_state, compressed_audio, compressed_size_in_bytes, uncompressed_audio, number_of_frames, decode_with_fec);
}

OpusDecoderWrapper::OpusDecoderWrapper()
{
    initialize();
}

OpusDecoderWrapper::~OpusDecoderWrapper()
{
    safeDestroyDecoderState();
}

bool OpusDecoderWrapper::resetState()
{
    int error_code = opus_decoder_ctl(_decoder_state, OPUS_RESET_STATE);

    if(error_code != OPUS_OK)
    {
        __android_log_print(ANDROID_LOG_ERROR, "OpusDecoder", "Opus failed to reset state, returned opus error code %d", error_code);

        return false;
    }

    return true;
}