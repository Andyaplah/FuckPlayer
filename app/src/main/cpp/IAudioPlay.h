//
// Created by LCX on 2020/11/4.
//

#ifndef FUCKNATIVEPLAYER_IAUDIOPLAY_H
#define FUCKNATIVEPLAYER_IAUDIOPLAY_H


#include "IObserver.h"
#include "XParameter.h"

class IAudioPlay: public IObserver {
public:
    virtual void Update(XData data);
    virtual bool StartPlay(XParameter out) = 0;

};


#endif //FUCKNATIVEPLAYER_IAUDIOPLAY_H
