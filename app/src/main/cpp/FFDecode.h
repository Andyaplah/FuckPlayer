//
// Created by LCX on 2020/11/3.
//

#ifndef FUCKNATIVEPLAYER_FFDECODE_H
#define FUCKNATIVEPLAYER_FFDECODE_H


#include "XParameter.h"
#include "IDecode.h"

struct AVCodecContext;
struct AVFrame;

class FFDecode :public IDecode
{
public:
    virtual bool Open(XParameter para);

    //future模型 多线程并发处理的模型
    virtual bool SendPacket(XData pkt);

    //从线程中获取解码结果  再次调用会复用上次空间 线程不安全
    virtual XData RecvFrame();

private:
    AVCodecContext *codec = 0;
    AVFrame *frame = 0;
};


#endif //FUCKNATIVEPLAYER_FFDECODE_H
