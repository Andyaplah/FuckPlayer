//
// Created by LCX on 2020/11/3.
//

#ifndef FUCKNATIVEPLAYER_XEGL_H
#define FUCKNATIVEPLAYER_XEGL_H


class XEGL
{
public:
    virtual bool Init(void *win) = 0;
    virtual void Draw() = 0;
    static XEGL *Get();

protected:
    XEGL(){}
};


#endif //FUCKNATIVEPLAYER_XEGL_H
