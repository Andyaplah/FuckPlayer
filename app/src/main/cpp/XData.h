//
// Created by LCX on 2020/11/3.
//

#ifndef FUCKNATIVEPLAYER_XDATA_H
#define FUCKNATIVEPLAYER_XDATA_H
enum XDataType
{
    AVPACKET_TYPE = 0,
    UCHAR_TYPE = 1
};

struct XData {
    int type = 0;
    unsigned char *data = 0;
    unsigned char *datas[8] = {0};
    int size = 0;
    bool  isAudio = false;
    int width = 0;
    int height = 0;
    bool Alloc(int size, const char *d = 0);
    void Drop();//清理
};

#endif //FUCKNATIVEPLAYER_XDATA_H
