//
// Created by LCX on 2020/11/3.
//

#ifndef FUCKNATIVEPLAYER_XSHADER_H
#define FUCKNATIVEPLAYER_XSHADER_H


class XShader
{
public:
    virtual bool Init();

    //获取材质并映射到内存
    virtual void GetTexture(unsigned int index,int width,int height, unsigned char *buf);
    virtual void Draw();

protected:
    unsigned int vsh = 0;
    unsigned int fsh = 0;
    unsigned int program = 0;
    unsigned int texts[100] = {0};  //为了后期清理的工作
};

#endif //FUCKNATIVEPLAYER_XSHADER_H
