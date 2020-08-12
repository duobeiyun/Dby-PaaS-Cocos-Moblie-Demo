
#ifndef PROJ_ANDROID_STUDIO_MYVIDEOFRAMEOBSERVER_H
#define PROJ_ANDROID_STUDIO_MYVIDEOFRAMEOBSERVER_H

#include "../include/libyuv.h"
#include "include_file.h"
#include "CacheVideoFrame.h"
#include "include/dby/DBYEngineExtension.h"
#include <mutex>
#include <list>
#include <map>

namespace duobeiyun {
    namespace cocos {
        class DbyVideoRawDataControl {
        public:
            DbyVideoRawDataControl();

            ~DbyVideoRawDataControl();

            //其他内部
            virtual bool onCaptureVideoFrame(VideoFrame &videoFrame);

            virtual bool onRenderVideoFrame(const char *uid, VideoFrame &videoFrame);

            virtual bool getRotationApplied();

            void cacheVideoFrameForUser(const char *uid, VideoFrame &videoFrame);

            CacheVideoFrame *getVideoFrame(const char *uid);

            COCOS_TEXTURE *getTexture(const char *uid);

            int updateTexture(const char *glid, const char *uid);

            COCOS_TEXTURE *updateTexture(const char *uid);

            void convertVideoFrameFromI420ToABGR(const uint8 *src_y, int src_stride_y,
                                                 const uint8 *src_u, int src_stride_u,
                                                 const uint8 *src_v, int src_stride_v,
                                                 uint8 *dst_argb, int dst_stride_argb,
                                                 int width, int height);

            void rotateVideoFrame(uint8 *data, int stride, int width, int height);

            void clearData();


        private:
            std::mutex _mapMutex;
            std::map<std::string, CacheVideoFrame *> _cacheVideoFrameMap;
            std::map<std::string, COCOS_TEXTURE *> _cacheTextureMap;

            std::map<std::string , int> testMap;
        };
    };
}

#endif //PROJ_ANDROID_STUDIO_MYVIDEOFRAMEOBSERVER_H
