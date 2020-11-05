//
// Created by LCX on 2020/11/4.
//

#include "IAudioPlay.h"
#include "XLog.h"


void IAudioPlay::Update(XData data)
{
    XLOGE("IAudioPlay::Update %d",data.size);
    //压入缓冲队列
    if(data.size <=0 || !data.data)
        return;
    while (!isExit)
    {
        frameMutex.lock();
        if(frames.size() < maxFrame)
        {
            frameMutex.unlock();
            XSleep(1);
            continue;
        }
        frames.push_back(data);
        frameMutex.unlock();
        break;
    }

}