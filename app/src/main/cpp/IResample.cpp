//
// Created by LCX on 2020/11/4.
//

#include "IResample.h"

void IResample::Update(XData data)
{
    XData d = this->Resample(data);
    if(d.size > 0)
    {
        this->Notify(d);
    }
}