//
// Created by LCX on 2020/11/4.
//

#include "IAudioPlay.h"
#include "XLog.h"


XData IAudioPlay::GetData()
{
    XData d;
    while (!isExit)
    {
        frameMutex.lock();
        if(!frames.empty())
        {
            d = frames.front();
            frames.pop_front();
            frameMutex.unlock();
            return d;
        }
        frameMutex.unlock();
        XSleep(1);
    }
    return d;
}

void IAudioPlay::Update(XData data)
{
    XLOGE("IAudioPlay::Update %d",data.size);
    //压入缓冲队列
    if(data.size <=0 || !data.data)
        return;
    while (!isExit)
    {
        frameMutex.lock();
        if(frames.size() > maxFrame)    //<画面不动 声音没有
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