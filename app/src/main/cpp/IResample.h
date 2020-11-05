//
// Created by LCX on 2020/11/4.
//

#ifndef FUCKNATIVEPLAYER_IRESAMPLE_H
#define FUCKNATIVEPLAYER_IRESAMPLE_H


#include "IObserver.h"
#include "XParameter.h"

class IResample : public IObserver
{
public:
    virtual bool Open(XParameter in, XParameter out=XParameter()) = 0;
    virtual XData Resample(XData indata) = 0;
    virtual void Update(XData data);
    int outChannals = 2;
    int outFormat =1;
};


#endif //FUCKNATIVEPLAYER_IRESAMPLE_H
