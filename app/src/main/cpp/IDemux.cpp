//
// Created by LCX on 2020/11/3.
//

#include "IDemux.h"
#include "IDemux.h"
#include "XLog.h"

void IDemux::Main()
{
    while (!isExit)
    {
        //放音频一定需要缓冲
        XData d = Read();
        if(d.size > 0 )
            Notify(d);
        //XLOGI("IDemux Read %d",d.size);
//        if(d.size <= 0)
//            break;
    }
}