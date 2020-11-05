//
// Created by LCX on 2020/11/3.
//

#ifndef FUCKNATIVEPLAYER_XTHREAD_H
#define FUCKNATIVEPLAYER_XTHREAD_H


//通用的sleep
void XSleep(int mis);

//C++ 11线程库  直接使用 每次都要维系线程句柄
//自己封装 代码简洁点
class XThread
{
public:
    //启动线程
    virtual void Start();
    //通过控制isExit安全停止线程(不一定成)
    virtual void Stop();
    //入口主函数  纯虚函数=0 要求继承者必须继承main   {}这是默认实现
    virtual void Main() {};
protected:
    bool isExit = false;
    bool isRunning = false;
private:
    void ThreadMain();
};


#endif //FUCKNATIVEPLAYER_XTHREAD_H
