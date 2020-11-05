//
// Created by LCX on 2020/11/3.
//

#include "XThread.h"
#include "XThread.h"
#include "XLog.h"
#include <thread>
using namespace std;

void XSleep(int mis)
{
    chrono::milliseconds du(mis);
    this_thread::sleep_for(du);
}

//启动线程
void XThread::Start()
{
    isExit = false;
    thread th(&XThread::ThreadMain,this);
    th.detach();//放弃对线程的控制  当对象清空  当前线程对创建新线程的控制
}


void XThread::ThreadMain()
{
    isRunning = true;
    XLOGI("线程函数进入");
    Main();
    XLOGI("线程函数退出");
    isRunning = false;
}


//通过控制isExit安全停止线程(不一定成)
void XThread::Stop()
{
    XLOGI("Stop 停止线程begin!");
    isExit = true;
    for (int i = 0; i < 200; i++) {
        if(!isRunning)
        {
            XLOGI("Stop 停止线程成功!");
            return;
        }
        XSleep(1);
    }
    XLOGI("Stop 停止线程超时!");
}