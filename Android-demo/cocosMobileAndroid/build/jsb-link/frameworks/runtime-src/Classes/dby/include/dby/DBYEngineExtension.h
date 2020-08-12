//
// Created by yangge on 2020/7/31.
//

#ifndef DUOBEIYUNPAASDEMO_DBYENGINEEXTENSION_H
#define DUOBEIYUNPAASDEMO_DBYENGINEEXTENSION_H


#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include <string>

namespace duobeiyun {
    struct VideoFrame {
        int width;  //width of video frame
        int height;  //height of video frame
        void *yBuffer;  //Y data buffer
        void *uBuffer;  //U data buffer
        void *vBuffer;  //V data buffer
        int rotation; // rotation of this frame (0, 90, 180, 270)
    };

    class DbyEngineEventHandler {
    public:
        virtual  ~DbyEngineEventHandler() {}

        virtual void onJoinChannelSuccess(const char *channel, const char *uid,
                                          const char *userName) {
            (void) channel;
            (void) uid;
            (void) userName;
        }

        virtual void onUserJoined(const char *uid, const char *userName) {
            (void) uid;
            (void) userName;
        }

        virtual void onPlayVideoData(const char *uid, VideoFrame &videoFrame) {
            (void) uid;
            (void) videoFrame;
        }
    };

    /**
     * Definition of DbyEngineContext.
     */
    struct DbyEngineContext {
        DbyEngineEventHandler *eventHandler;

        const char *appId;
        const char *appKey;
        // For android, it the context(Activity or Application
        void *context;

        DbyEngineContext()
                : eventHandler(NULL), appId(NULL), appKey(NULL), context(NULL) {}
    };

    struct CameraConfig {
        int width;
        int height;
        int frameRate;
    };
}

__attribute__ ((visibility ("default"))) void initialize(duobeiyun::DbyEngineContext &context);

__attribute__ ((visibility ("default"))) int
joinChannel(const char *channel, const char *uid, const char *userName);

void leaveChannel();

void recoveryActivity();

void pauseActivity();

void destroyEngine();

int setChannelProfile(int profile);

int setClientRole(int role);

int enableDualStreams(bool role);

int setRemoteVideoStreamType(std::string uid, int videoType);

int enableLocalAudio(bool open);

int enableLocalCamera(bool open);

int setCameraConfig(duobeiyun::CameraConfig config);

int switchCamera();

int sendBroadcastMessage(std::string msg);

int muteRemoteVideoStream(std::string uid, bool isMute);

int muteRemoteAudioStream(std::string uid, bool isMute);

#endif //DUOBEIYUNPAASDEMO_DBYENGINEEXTENSION_H
