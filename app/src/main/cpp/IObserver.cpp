//
// Created by LCX on 2020/11/3.
//

#include "IObserver.h"
//主体函数  添加观察者
void IObserver::AddObs(IObserver *obs)
{
    if (!obs)
        return;
    mux.lock();
    obss.push_back(obs);
    mux.unlock();
}

//通知所有观察者
void IObserver::Notify(XData data)
{
    mux.lock();
    for (int i = 0; i < obss.size(); i++)
    {
        obss[i]->Update(data);//空数据也要通知它
    }
    mux.unlock();
}