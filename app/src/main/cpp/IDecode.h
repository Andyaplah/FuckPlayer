//
// Created by LCX on 2020/11/3.
//

#ifndef FUCKNATIVEPLAYER_IDECODE_H
#define FUCKNATIVEPLAYER_IDECODE_H


#include "XParameter.h"
#include "IObserver.h"
#include <list>

//解码接口 支持硬解码
class IDecode :public IObserver
{
public:
    //打开解码器
    virtual bool Open(XParameter  para) = 0;

    //future模型 多线程并发处理的模型
    virtual bool SendPacket(XData pkt) = 0;

    //从线程中获取解码结果  再次调用会复用上次空间 线程不安全
    virtual XData RecvFrame() = 0;

    //由主体notfiy的数据
    virtual void Update(XData pkt);

    bool isAudio = false;

    //最大队列缓冲
    int maxList = 100;

protected:
    virtual void Main();

    //读取缓冲
    std::list<XData> packs;
    std::mutex packsMutex;
};

#endif //FUCKNATIVEPLAYER_IDECODE_H
