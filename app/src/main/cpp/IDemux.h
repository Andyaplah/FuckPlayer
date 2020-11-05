//
// Created by LCX on 2020/11/3.
//

#ifndef FUCKNATIVEPLAYER_IDEMUX_H
#define FUCKNATIVEPLAYER_IDEMUX_H


#include "XData.h"
#include "XThread.h"
#include "IObserver.h"
#include "XParameter.h"

//解封装接口
class IDemux :public IObserver{
public:
    //打开文件 或者流媒体 rmtp http rtsp
    virtual bool Open(const char *url) = 0;//纯虚函数

    //获取视频参数
    virtual XParameter GetVPara() = 0;
    //获取音频参数
    virtual XParameter GetAPara() = 0;

    //读取一帧数据 数据由调用者清理 防止内存泄露  涉及空间调用 一定要说清楚
    virtual XData Read() = 0;

    //总时长 单位毫秒
    int totalMs = 0;
protected:
    virtual void Main();
};


#endif //FUCKNATIVEPLAYER_IDEMUX_H
