//
// Created by LCX on 2020/11/4.
//

#ifndef FUCKNATIVEPLAYER_XTEXTURE_H
#define FUCKNATIVEPLAYER_XTEXTURE_H


class XTexture {
public:
    static XTexture *Create();
    virtual bool Init(void *win) = 0;
    virtual void Draw(unsigned char *data[],int width,int height) = 0;
};


#endif //FUCKNATIVEPLAYER_XTEXTURE_H
