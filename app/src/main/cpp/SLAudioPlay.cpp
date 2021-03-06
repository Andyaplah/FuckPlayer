//
// Created by LCX on 2020/11/4.
//

#include "SLAudioPlay.h"
#include "XLog.h"
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

static SLObjectItf engineSL = NULL;
static SLEngineItf  eng = NULL;
static SLObjectItf mix = NULL;
static SLObjectItf player = NULL;
static SLPlayItf iplayer = NULL;
static SLAndroidSimpleBufferQueueItf pcmQue = NULL;


SLAudioPlay::SLAudioPlay(){
    buf = new unsigned char[1024 * 1024];
}

SLAudioPlay::~SLAudioPlay()
{
    delete buf;
    buf = 0;
}


static SLEngineItf  CreateSL()
{
    SLresult  re;
    SLEngineItf en;
    re = slCreateEngine(&engineSL,0,0,0,0,0);
    if(re!=SL_RESULT_SUCCESS)
        return NULL;
    re = (*engineSL)->Realize(engineSL,SL_BOOLEAN_FALSE);
    if(re != SL_RESULT_SUCCESS)
        return NULL;
    re = (*engineSL)->GetInterface(engineSL,SL_IID_ENGINE,&en);
    if(re != SL_RESULT_SUCCESS)
        return NULL;
    return en;
}

void SLAudioPlay::PlayCall(void *bufq)
{
    if(!bufq)
        return;
    SLAndroidSimpleBufferQueueItf bf = (SLAndroidSimpleBufferQueueItf)bufq;
    XLOGI("SLAudioPlay::PlayCall");
    //阻塞
    XData d = GetData();
    if(d.size <= 0)
    {
        XLOGE("GetData() size is 0");
        return;
    }
    if(!buf)
        return;
    memcpy(buf,d.data,d.size);
    (*bf)->Enqueue(bf,buf,d.size);
    d.Drop();
}


static void PcmCall(SLAndroidSimpleBufferQueueItf bf,void *contex)
{
    SLAudioPlay *ap = (SLAudioPlay *)contex;
    if(!ap)
    {
        XLOGE("PcmCall failed contex is null!");
        return;
    }
    ap->PlayCall((void *)bf);
}


bool SLAudioPlay::StartPlay(XParameter out)
{
    //1创建引擎
    eng = CreateSL();
    if(eng)
    {
        XLOGI("CreateSL success! ");
    }
    else
    {
        XLOGE("CreateSL failed! ");
        return false;
    }

    //2 创建混音器
    SLresult  re = 0;
    re = (*eng)->CreateOutputMix(eng,&mix,0,0,0);
    if(re != SL_RESULT_SUCCESS)
    {
        XLOGE("SL_RESULT_SUCCESS failed!");
        return false;
    }
    re = (*mix)->Realize(mix,SL_BOOLEAN_FALSE);
    if(re != SL_RESULT_SUCCESS)
    {
        XLOGE("(*mix)->Realize failed!");
        return false;
    }
    SLDataLocator_OutputMix outmix = {SL_DATALOCATOR_OUTPUTMIX,mix};
    SLDataSink audioSink = {&outmix,0};  //交给player

    //3 配置音频信息
    //缓冲队列
    SLDataLocator_AndroidBufferQueue que = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE,10};
    //音频格式
    SLDataFormat_PCM pcm = {
            SL_DATAFORMAT_PCM,
            (SLuint32)out.channels,//声道数
            (SLuint32)out.sample_rate*1000,
            SL_PCMSAMPLEFORMAT_FIXED_16,
            SL_PCMSAMPLEFORMAT_FIXED_16,
            SL_SPEAKER_FRONT_LEFT|SL_SPEAKER_FRONT_RIGHT,
            SL_BYTEORDER_LITTLEENDIAN //字节序 小端  网络字节序就会有差异
    };

    SLDataSource ds = {&que,&pcm};

    //4 创建播放器
    const SLInterfaceID ids[] = {SL_IID_BUFFERQUEUE};
    const SLboolean req[] = {SL_BOOLEAN_TRUE};
    //后三个参数传0导致下面获取队列接口失败
    //re =(*eng)->CreateAudioPlayer(eng,&player,&ds,&audioSink,0,0,0);
    re =(*eng)->CreateAudioPlayer(eng,&player,&ds,&audioSink, sizeof(ids)/ sizeof(SLInterfaceID),ids,req);
    if(re != SL_RESULT_SUCCESS)
    {
        XLOGE("CreateAudioPlayer failed!");
        return false;
    }
    else
    {
        XLOGI("CreateAudioPlayer success!");
    }
    (*player)->Realize(player,SL_BOOLEAN_FALSE);
    //获取player接口
    re = (*player)->GetInterface(player,SL_IID_PLAY,&iplayer);
    if(re != SL_RESULT_SUCCESS)
    {
        XLOGE("GetInterface failed!");
        return false;
    }
    else
    {
        XLOGI("GetInterface success!");
    }
    //开始获取队列接口
    re = (*player)->GetInterface(player,SL_IID_BUFFERQUEUE,&pcmQue);
    if(re != SL_RESULT_SUCCESS)
    {
        XLOGE("SL_IID_BUFFERQUEUE failed!");
        return false;
    }
    else
    {
        XLOGI("SL_IID_BUFFERQUEUE success!");
    }

    //设置缓冲接口的回调函数 在播放队列空的时候调用
    (*pcmQue)->RegisterCallback(pcmQue,PcmCall,this);
    //设置为播放状态
    (*iplayer)->SetPlayState(iplayer,SL_PLAYSTATE_PLAYING);

    //启动队列的回调  这一步才会回调pcmCall
    (*pcmQue)->Enqueue(pcmQue,"",1);
    XLOGI("SLAudioPlay::StartPlay success!");
    return true;
}