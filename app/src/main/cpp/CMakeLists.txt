
cmake_minimum_required(VERSION 3.4.1)
#添加头文件 相对路径ffmpeg
include_directories(include)
#设置ffmpeg库所在的路径变量
set(FF ${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/${ANDROID_ABI})
add_library(avcodec SHARED IMPORTED)
set_target_properties(avcodec PROPERTIES IMPORTED_LOCATION ${FF}/libavcodec.so)

add_library(avformat SHARED IMPORTED)
set_target_properties(avformat PROPERTIES IMPORTED_LOCATION ${FF}/libavformat.so)

add_library(avutil SHARED IMPORTED)
set_target_properties(avutil PROPERTIES IMPORTED_LOCATION ${FF}/libavutil.so)

add_library(swscale SHARED IMPORTED)
set_target_properties(swscale PROPERTIES IMPORTED_LOCATION ${FF}/libswscale.so)

add_library(sample SHARED IMPORTED)
set_target_properties(sample PROPERTIES IMPORTED_LOCATION ${FF}/libswresample.so)



add_library(
             native-lib
            SHARED
            FFDemux.cpp
            XData.cpp
            XLog.cpp
            XThread.cpp
            IObserver.cpp
            FFDecode.cpp
            IDecode.cpp
            XParameter.cpp
            IDemux.cpp
            XEGL.cpp
            XShader.cpp
            GLVideoView.cpp
            IVideoView.cpp
            XTexture.cpp
        IResample.cpp
        FFResample.cpp
        IAudioPlay.cpp
        SLAudioPlay.cpp
             native-lib.cpp )



find_library(
              log-lib

              log )


target_link_libraries(
                       native-lib
        GLESv2 EGL
        OpenSLES
        android
        avcodec avformat avutil swscale sample

                       ${log-lib} )