//
// Created by nni on 17.01.19.
//

#ifndef BINAURALRADIO_OPUS_BASE_WRAPPER_H
#define BINAURALRADIO_OPUS_BASE_WRAPPER_H

#include <cstddef>
//#include <audio_packet.h>

class OpusBaseWrapper{
public:

    OpusBaseWrapper()
    {
       // static_assert( _number_of_frames <= AudioPacket::max_number_of_frames, "opus number of frames is larger than AudioPacket max number of frames");
    }

    static constexpr int _channels = 1;
    static constexpr int _compressed_bit_rate = 64000;
    static constexpr float sampling_period = 0.060;//0.040;


    static constexpr bool _use_fec = true;
    static constexpr opus_int32 packet_lost_percantage = 60; //between 0 and 100
    
};

#endif //BINAURALRADIO_OPUS_BASE_WRAPPER_H
