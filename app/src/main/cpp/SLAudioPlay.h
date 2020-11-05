//
// Created by LCX on 2020/11/4.
//

#ifndef FUCKNATIVEPLAYER_SLAUDIOPLAY_H
#define FUCKNATIVEPLAYER_SLAUDIOPLAY_H


#include "IAudioPlay.h"

class SLAudioPlay : public IAudioPlay{
public:
    virtual bool StartPlay(XParameter out);
    void PlayCall(void *bufq);
};


#endif //FUCKNATIVEPLAYER_SLAUDIOPLAY_H
