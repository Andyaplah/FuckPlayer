//
// Created by LCX on 2020/11/4.
//

#ifndef FUCKNATIVEPLAYER_FFRESAMPLE_H
#define FUCKNATIVEPLAYER_FFRESAMPLE_H


#include "IResample.h"
struct SwrContext;
class FFResample: public IResample
{
public:
    virtual bool Open(XParameter in, XParameter out=XParameter());
    virtual XData Resample(XData indata);
protected:
    SwrContext *actx = 0;
};


#endif //FUCKNATIVEPLAYER_FFRESAMPLE_H
