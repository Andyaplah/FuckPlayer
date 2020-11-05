//
// Created by LCX on 2020/11/3.
//

#include "IDecode.h"

#include "IDecode.h"
#include "XLog.h"


void IDecode::Update(XData pkt)
{
    if(pkt.isAudio != isAudio)
    {
        return;
    }
    while (!isExit)
    {
        packsMutex.lock();
        //会造成内存耗尽 所以定义一个最大值
        //阻塞
        if(packs.size() < maxList)
        {
            packs.push_back(pkt);
            packsMutex.unlock();
            break;
        }
        packsMutex.unlock();
        XSleep(1);
    }


}


void IDecode::Main()
{
    while (!isExit)
    {
        packsMutex.lock();
        if(packs.empty())
        {
            packsMutex.unlock();
            XSleep(1);  //释放cpu资源
            continue;
        }

        //取出packet
        XData pack = packs.front();
        packs.pop_front();

        //发送数据到解码线程   一个数据包可能解码多个结果
        if(this->SendPacket(pack))
        {
            while (!isExit)
            {
                //获取解码数据
                XData frame = RecvFrame();
                if(!frame.data)
                    break;
                //XLOGE("RecvFrame %d",frame.size);
                //发送数据给观察者
                this->Notify(frame);
            }

        }
        pack.Drop();//不能省  否则会导致内存泄露
        packsMutex.unlock();
    }

}