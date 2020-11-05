#include <jni.h>
#include <string>
#include "FFDemux.h"
#include "XLog.h"
#include "IDecode.h"
#include "FFDecode.h"
#include "XEGL.h"
#include "XShader.h"
#include "IVideoView.h"
#include "GLVideoView.h"
#include "FFResample.h"
#include "IAudioPlay.h"
#include "SLAudioPlay.h"
//#include "XEGL.h"
//#include "XShader.h"
#include <android/native_window_jni.h>
class TestObs:public IObserver
{
public:
    void Update(XData d)
    {
        //XLOGI("TestObs update data size is :%d",d.size);
    }
};


IVideoView *view = NULL;
extern "C" JNIEXPORT jstring JNICALL
Java_com_andy_fucknativeplayer_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    ////////////////////////
    ////测试代码
    TestObs *tobs = new TestObs();
    IDemux *de = new FFDemux();
    //de->AddObs(tobs);
    de->Open("/sdcard/1080.mp4");

    IDecode *vdecode = new FFDecode();
    vdecode->Open(de->GetVPara());

    IDecode *adecode = new FFDecode();
    adecode->Open(de->GetAPara());

    de->AddObs(vdecode);
    de->AddObs(adecode);


    view = new GLVideoView();
    vdecode->AddObs(view);

    IResample *resample = new FFResample();
    XParameter outPara = de->GetAPara();

    resample->Open(de->GetAPara(),outPara);
    adecode->AddObs(resample);

    IAudioPlay *audioPlay = new SLAudioPlay();
    audioPlay->StartPlay(outPara);
    resample->AddObs(audioPlay);

    /*for(;;)
    {
        XData d = de->Read();
        XLOGI("Read data size is %d",d.size);

    }*/
    de->Start();
    vdecode->Start();
    adecode->Start();
    //XSleep(3000);
    //de->Stop();


    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_andy_fucknativeplayer_XPlay_initView(JNIEnv *env, jobject thiz, jobject surface) {
    // TODO: implement initView()
    ANativeWindow *win = ANativeWindow_fromSurface(env,surface);
    view->SetRender(win);
   // XEGL::Get()->Init(win);
//    XShader *shader;
//    shader->Init();
    //XShader shader;
    //shader.Init();
}