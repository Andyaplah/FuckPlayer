//
// Created by LCX on 2020/11/4.
//

#ifndef FUCKNATIVEPLAYER_IAUDIOPLAY_H
#define FUCKNATIVEPLAYER_IAUDIOPLAY_H


#include "IObserver.h"
#include "XParameter.h"
#include <list>
class IAudioPlay: public IObserver {
public:
    //缓冲满后阻塞
    virtual void Update(XData data);
    virtual bool StartPlay(XParameter out) = 0;
    //最大缓冲
    int maxFrame = 100;

protected:
    std::list<XData> frames;
    std::mutex frameMutex;
};


#endif //FUCKNATIVEPLAYER_IAUDIOPLAY_H
