//
// Created by LCX on 2020/11/3.
//

#ifndef FUCKNATIVEPLAYER_FFDEMUX_H
#define FUCKNATIVEPLAYER_FFDEMUX_H


#include "IDemux.h"
struct AVFormatContext;

class FFDemux: public IDemux{
public:
    //打开文件 或者流媒体 rmtp http rtsp
    virtual bool Open(const char *url);

    //获取视频参数
    virtual XParameter GetVPara();

    //获取音频参数
    virtual XParameter GetAPara();

    //读取一帧数据 数据由调用者清理 防止内存泄露  涉及空间调用 一定要说清楚
    virtual XData Read();

    FFDemux();

private:
    AVFormatContext *ic = 0;
    int audioStream = 1;
    int videoStream = 0;
};


#endif //FUCKNATIVEPLAYER_FFDEMUX_H
