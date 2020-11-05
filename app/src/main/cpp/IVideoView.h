//
// Created by LCX on 2020/11/4.
//

#ifndef FUCKNATIVEPLAYER_IVIDEOVIEW_H
#define FUCKNATIVEPLAYER_IVIDEOVIEW_H


#include "XData.h"
#include "IObserver.h"

class IVideoView: public IObserver{
public:
    virtual void SetRender(void *win) = 0;
    virtual void Render(XData data) = 0;
    virtual void Update(XData data);
};


#endif //FUCKNATIVEPLAYER_IVIDEOVIEW_H
