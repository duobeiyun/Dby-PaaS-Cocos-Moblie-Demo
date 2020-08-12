
#include "DbyVideoRawDataControl.h"

namespace duobeiyun {
    namespace cocos {
        DbyVideoRawDataControl::DbyVideoRawDataControl() {

        }

        DbyVideoRawDataControl::~DbyVideoRawDataControl() {
            _mapMutex.lock();
            clearData();
            _mapMutex.unlock();
        }

        bool DbyVideoRawDataControl::getRotationApplied() {
            return true;
        }

        bool DbyVideoRawDataControl::onCaptureVideoFrame(VideoFrame &videoFrame) {
            _mapMutex.lock();
            cacheVideoFrameForUser(0, videoFrame);
            _mapMutex.unlock();
            return true;
        }

        bool DbyVideoRawDataControl::onRenderVideoFrame(const char *uid, VideoFrame &videoFrame) {
            _mapMutex.lock();
            cacheVideoFrameForUser(uid, videoFrame);
            _mapMutex.unlock();
            return true;
        }

        void
        DbyVideoRawDataControl::cacheVideoFrameForUser(const char *uid, VideoFrame &videoFrame) {
            CCLOGERROR(
                    "%s cacheVideoFrameForUser_cacheVideoFrameForUser---> uid=%s ",AGORA_TAG, uid);
            if (strcmp(uid, "") == 0) {
                return;
            }


           auto it = _cacheVideoFrameMap.find(uid);

            if (it == _cacheVideoFrameMap.end()) {   // cache video frame

                CacheVideoFrame *cacheVideoFrame = new CacheVideoFrame(videoFrame.width,
                                                                       videoFrame.height);

                _cacheVideoFrameMap[uid] = cacheVideoFrame;
                CCLOGERROR("%s cacheVideoFrameForUser uid=%s  _cacheVideoFrameMap.size=%d",
                           AGORA_TAG, uid, _cacheVideoFrameMap.size());
                // convert video frame from I420 to RGBA32
                convertVideoFrameFromI420ToABGR((uint8 *) videoFrame.yBuffer, videoFrame.width,
                                                (uint8 *) videoFrame.uBuffer, videoFrame.width / 2,
                                                (uint8 *) videoFrame.vBuffer, videoFrame.width / 2,
                                                (uint8 *) cacheVideoFrame->_data,
                                                cacheVideoFrame->_width * 4,
                                                cacheVideoFrame->_width, cacheVideoFrame->_height);

                CCLOG("%s videoframe rotation = %d", AGORA_TAG, videoFrame.rotation);
                // check wheather need to rotate video
                if ((videoFrame.rotation % 360) == 180) {
                    rotateVideoFrame((uint8 *) cacheVideoFrame->_data, cacheVideoFrame->_width * 4,
                                     cacheVideoFrame->_width, cacheVideoFrame->_height);
                }

                // cache texture for js
                COCOS_TEXTURE *selfTexture = new COCOS_TEXTURE;
                _cacheTextureMap[uid] = selfTexture;
                CCLOG("%s new Texture for uid %u", AGORA_TAG, uid);
            } else {
                CacheVideoFrame *cacheVideoFrame = _cacheVideoFrameMap[uid];
                /*
                 * if video frame size is changed, we need to reCreate the cacheVideoFrame pointer.
                 */
                if (cacheVideoFrame->_width != videoFrame.width ||
                    cacheVideoFrame->_height != videoFrame.height) {
                    CCLOG("%s size change for uid %s , before width = %d & height = %d , now width = %d & height = %d",
                          AGORA_TAG, uid, cacheVideoFrame->_width, cacheVideoFrame->_height,
                          videoFrame.width, videoFrame.height);
                    delete cacheVideoFrame;
                    cacheVideoFrame = NULL;
                    cacheVideoFrame = new CacheVideoFrame(videoFrame.width, videoFrame.height);
                    _cacheVideoFrameMap[uid] = cacheVideoFrame;

                    COCOS_TEXTURE *texture = _cacheTextureMap[uid];
                    if (texture) {
                        CC_SAFE_RELEASE(texture);
                        texture = NULL;
                        texture = new COCOS_TEXTURE;
                        _cacheTextureMap[uid] = texture;
                        CCLOGERROR("%s cacheVideoFrameForUser uid=%s  _cacheTextureMap.size=%d",
                                   AGORA_TAG, uid, _cacheTextureMap.size());
                    }
                }

                convertVideoFrameFromI420ToABGR((uint8 *) videoFrame.yBuffer, videoFrame.width,
                                                (uint8 *) videoFrame.uBuffer, videoFrame.width / 2,
                                                (uint8 *) videoFrame.vBuffer, videoFrame.width / 2,
                                                (uint8 *) cacheVideoFrame->_data,
                                                cacheVideoFrame->_width * 4,
                                                cacheVideoFrame->_width, cacheVideoFrame->_height);
                if ((videoFrame.rotation % 360) == 180) {
                    rotateVideoFrame((uint8 *) cacheVideoFrame->_data, cacheVideoFrame->_width * 4,
                                     cacheVideoFrame->_width, cacheVideoFrame->_height);
                }
            }
        }

        CacheVideoFrame *DbyVideoRawDataControl::getVideoFrame(const char *uid) {
            auto it = _cacheVideoFrameMap.find(uid);


            if (it == _cacheVideoFrameMap.end()) {
//                for (auto item:_cacheVideoFrameMap) {
//                    CCLOGERROR(
//                            "%s getVideoFrame__cacheVideoFrameMap_foreach   map.key=%s map.value=%p",
//                            AGORA_TAG, item.first, item.second);
//
//                }
                return NULL;
            } else {
                CCLOGERROR(
                        "%s getVideoFrame uid=%s  _cacheTextureMap.size=%d map.key=%s map.value=%p",
                        AGORA_TAG, uid, _cacheVideoFrameMap.size(), it->first.c_str(), it->second);
                return (it->second);
            }
        }

        COCOS_TEXTURE *DbyVideoRawDataControl::getTexture(const char *uid) {
            auto it = _cacheTextureMap.find(uid);


            if (it == _cacheTextureMap.end()) {
//                for (auto item:_cacheTextureMap) {
//                    CCLOGERROR("%s getTexture___cacheTextureMap_foreach   map.key=%s map.value=%p",
//                               AGORA_TAG, item.first, item.second);
//
//                }
                CCLOGERROR("%s No Texture found for user %s  _cacheTextureMap.size=%d", AGORA_TAG,
                           uid, _cacheTextureMap.size());
                return NULL;
            } else {

                return (it->second);
            }
        }

        // For Render video frame by openGLES2 in Cocos Creator 2.0.
        int DbyVideoRawDataControl::updateTexture(const char *glid, const char *uid) {
            _mapMutex.lock();
            CacheVideoFrame *cacheVideoFrame = getVideoFrame(uid);
            int ret = 0;
            _mapMutex.unlock();
            return ret;
        }

        COCOS_TEXTURE *DbyVideoRawDataControl::updateTexture(const char *uid) {
            CCLOGERROR("%s updateTexture uid=%s ", AGORA_TAG, uid);
            _mapMutex.lock();
            COCOS_TEXTURE *texture = getTexture(uid);
            CacheVideoFrame *cacheVideoFrame = getVideoFrame(uid);
            if (texture && cacheVideoFrame) {
                if (texture->getName() == 0) {
                    texture->initWithData(cacheVideoFrame->_data,
                                          cacheVideoFrame->_width * cacheVideoFrame->_height * 4,
                                          COCOS_TEXTURE::PixelFormat::RGBA8888,
                                          cacheVideoFrame->_width, cacheVideoFrame->_height,
                                          cocos2d::Size(cacheVideoFrame->_width,
                                                        cacheVideoFrame->_height));
                } else {
                    texture->updateWithData(cacheVideoFrame->_data, 0, 0, cacheVideoFrame->_width,
                                            cacheVideoFrame->_height);
                }

                _mapMutex.unlock();
                return texture;
            } else {
                _mapMutex.unlock();
                return NULL;
            }
        }

        void DbyVideoRawDataControl::convertVideoFrameFromI420ToABGR(const uint8 *src_y,
                                                                     int src_stride_y,
                                                                     const uint8 *src_u,
                                                                     int src_stride_u,
                                                                     const uint8 *src_v,
                                                                     int src_stride_v,
                                                                     uint8 *dst_argb,
                                                                     int dst_stride_argb,
                                                                     int width, int height) {
            libyuv::I420ToABGR(src_y, src_stride_y,
                               src_u, src_stride_u,
                               src_v, src_stride_v,
                               dst_argb, dst_stride_argb,
                               width, height);

        }

        void
        DbyVideoRawDataControl::rotateVideoFrame(uint8 *data, int stride, int width, int height) {
            libyuv::RotationMode mode = libyuv::kRotate180;
            libyuv::ARGBRotate(data, stride, data, stride, width, height, mode);
        }

        void DbyVideoRawDataControl::clearData() {

            for (auto videoFrameIterator = _cacheVideoFrameMap.begin();
                 videoFrameIterator != _cacheVideoFrameMap.end(); videoFrameIterator++) {
                CacheVideoFrame *cacheVideoFrame = videoFrameIterator->second;
                if (cacheVideoFrame) {
                    delete cacheVideoFrame;
                    cacheVideoFrame = NULL;
                    _cacheVideoFrameMap.erase(videoFrameIterator);
                }
            }

            for (auto textureIterator = _cacheTextureMap.begin();
                 textureIterator != _cacheTextureMap.end(); textureIterator++) {
                COCOS_TEXTURE *cacheTexture = textureIterator->second;
                if (cacheTexture) {
                    CC_SAFE_RELEASE(cacheTexture);
                    cacheTexture = NULL;
                    _cacheTextureMap.erase(textureIterator);
                }
            }
        }
    }
}
