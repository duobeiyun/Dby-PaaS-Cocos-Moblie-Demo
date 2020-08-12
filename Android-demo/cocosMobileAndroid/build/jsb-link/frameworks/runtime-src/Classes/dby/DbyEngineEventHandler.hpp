
#ifndef AGRtcEngineEventHandler_hpp
#define AGRtcEngineEventHandler_hpp

#include "include_file.h"
#include "DBYContext.hpp"
#include "include/dby/DBYEngineExtension.h"
#include "CacheVideoFrame.h"

namespace duobeiyun {
    namespace cocos {
        class DbyEngineEventHandler : public duobeiyun::DbyEngineEventHandler {


        public:
            DBYContext *_context;
            DbyEngineEventHandler(DBYContext *context);

            ~DbyEngineEventHandler();

            virtual void onJoinChannelSuccess(const char *channel, const char *uid,
                                              const char *userName);

            virtual void onUserJoined(const char *uid, const char *userName);

            virtual void onPlayVideoData(const char *uid, VideoFrame &videoFrame);


        };
    }
}
#endif /* AGRtcEngineEventHandler_hpp */

