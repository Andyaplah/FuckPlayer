//
// Created by LCX on 2020/11/3.
//

#include "FFDemux.h"



#include "FFDemux.h"
#include "XLog.h"
extern "C"
{
#include <libavformat/avformat.h>
}

//打开文件 或者流媒体 rmtp http rtsp
bool FFDemux::Open(const char *url)
{
    XLOGI("Open file %s begin",url);
    int re = avformat_open_input(&ic,url,0,0);
    if(re != 0)
    {
        char buf[1024] = {0};
        av_strerror(re,buf, sizeof(buf));
        XLOGI("FFDemux open %s failed!",url);
        return false;
    }
    XLOGI("FFDemux open %s success!",url);

    //获取文件信息
    re = avformat_find_stream_info(ic,0);
    if(re != 0)
    {
        char buf[1024] = {0};
        av_strerror(re,buf, sizeof(buf));
        XLOGI("avformat_find_stream_info %s failed!",url);
        return false;
    }

    this->totalMs = ic->duration/(AV_TIME_BASE/1000);  //这个值不一定有 因为要探测
    XLOGI("total ms = %d!",totalMs);
    GetVPara();
    GetAPara();
    return true;
}

//获取视频参数
XParameter FFDemux::GetVPara()
{
    if(!ic)
    {
        XLOGI("GetVPara failed! ic is NULL!");
        return XParameter();
    }
    //获取了视频流的索引
    int re = av_find_best_stream(ic,AVMEDIA_TYPE_VIDEO,-1,-1,0,0);
    if(re < 0)
    {
        XLOGI("av_find_best_stream failed!");
        return XParameter();
    }
    videoStream = re;
    XParameter para;
    para.para = ic->streams[re]->codecpar;

    return para;
}


//获取音频参数
XParameter FFDemux::GetAPara()
{
    if(!ic)
    {
        XLOGI("GetAPara failed! ic is NULL!");
        return XParameter();
    }
    //获取了音频流的索引
    int re = av_find_best_stream(ic,AVMEDIA_TYPE_AUDIO,-1,-1,0,0);
    if(re < 0)
    {
        XLOGI("av_find_best_stream failed!");
        return XParameter();
    }
    audioStream = re;
    XParameter para;
    para.para = ic->streams[re]->codecpar;
    para.channels = ic->streams[re]->codecpar->channels;
    para.sample_rate = ic->streams[re]->codecpar->sample_rate;
    return para;
}


//读取一帧数据 数据由调用者清理 防止内存泄露  涉及空间调用 一定要说清楚
XData FFDemux::Read()
{
    if(!ic)
        return XData();
    XData d;
    AVPacket *pkt = av_packet_alloc();
    int re = av_read_frame(ic,pkt);


    if(re != 0) //等于0是成功
    {
        av_packet_free(&pkt);  //空间需要释放
        return XData();
    }
    //XLOGI("pack size is %d ptss %lld",pkt->size,pkt->pts);
    d.data = (unsigned char*)pkt;
    d.size = pkt->size;
    if(pkt->stream_index == audioStream)
    {
        d.isAudio = true;
    }
    else if(pkt->stream_index == videoStream)
    {
        d.isAudio = false;
    }
    else
    {
        av_packet_free(&pkt);  //空间需要释放
        return XData();
    }

    return d;
}

FFDemux::FFDemux()
{
    static bool isFirst = true;//线程不安全
    if(isFirst)
    {
        isFirst = false;
        //注册所有解封装器
        av_register_all();

        //注册所有的解码器
        avcodec_register_all();

        //初始化网络
        avformat_network_init();
        XLOGI("register ffmpeg");
    }
}