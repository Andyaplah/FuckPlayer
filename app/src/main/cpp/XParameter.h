//
// Created by LCX on 2020/11/3.
//

#ifndef FUCKNATIVEPLAYER_XPARAMETER_H
#define FUCKNATIVEPLAYER_XPARAMETER_H


struct AVCodecParameters;

class XParameter {
public:
    AVCodecParameters *para = 0;
    int channels = 2;
    int sample_rate = 44100;
};



#endif //FUCKNATIVEPLAYER_XPARAMETER_H
