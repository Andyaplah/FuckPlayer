//
// Created by LCX on 2020/11/3.
//

#ifndef FUCKNATIVEPLAYER_IOBSERVER_H
#define FUCKNATIVEPLAYER_IOBSERVER_H


#include "XData.h"
#include "XThread.h"
#include <vector>
#include <mutex>
class IObserver:public XThread
{
public:
    //观察者接收数据的函数
    virtual void Update(XData data){};

    //主体函数  添加观察者  线程安全 因为加了锁
    void AddObs(IObserver *obs);

    //通知所有观察者
    void Notify(XData data);

protected:
    std::vector<IObserver *>obss;
    std::mutex mux;//互斥变量 c++11支持 低版本不支持
};


#endif //FUCKNATIVEPLAYER_IOBSERVER_H
