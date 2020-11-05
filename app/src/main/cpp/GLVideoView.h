//
// Created by LCX on 2020/11/4.
//

#ifndef FUCKNATIVEPLAYER_GLVIDEOVIEW_H
#define FUCKNATIVEPLAYER_GLVIDEOVIEW_H


#include "XData.h"
#include "IVideoView.h"

class XTexture;

class GLVideoView : public IVideoView{
public:
    virtual void SetRender(void *win);
    virtual void Render(XData data);

protected:
    void *view = 0;
    XTexture *txt = 0;
};


#endif //FUCKNATIVEPLAYER_GLVIDEOVIEW_H
