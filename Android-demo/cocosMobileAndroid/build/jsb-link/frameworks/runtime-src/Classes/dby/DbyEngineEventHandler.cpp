
#include "DbyEngineEventHandler.hpp"
#include "DBYContext.hpp"

namespace duobeiyun {
    namespace cocos {
        DbyEngineEventHandler::DbyEngineEventHandler(DBYContext *context) {
            _context = context;
        }

        DbyEngineEventHandler::~DbyEngineEventHandler() {
            _context = NULL;
        }

        void DbyEngineEventHandler::onJoinChannelSuccess(const char *channel, const char *uid,
                                                         const char *userName) {
            CCLOG("%s, dby_ygs_onJoinChannelSuccess", AGORA_TAG);
            cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]() {
                se::Value func;
                if (_context->_refObj->getProperty("onJoinChannelSuccess", &func)) {
                    se::ScriptEngine::getInstance()->clearException();
                    se::AutoHandleScope hs;
                    se::ValueArray args;
                    args.push_back(se::Value(uid));
                    args.push_back(se::Value(userName));
                    func.toObject()->call(args, _context->_refObj);
                }
            });
        }

        void DbyEngineEventHandler::onUserJoined(const char *uid, const char *userName) {
            cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]() {
                se::Value func;
                if (_context->_refObj->getProperty("onUserJoined", &func)) {
                    se::ScriptEngine::getInstance()->clearException();
                    se::AutoHandleScope hs;
                    se::ValueArray args;
                    args.push_back(se::Value(userName));
                    args.push_back(se::Value(userName));
                    func.toObject()->call(args, _context->_refObj);
                }
            });
        }

        void DbyEngineEventHandler::onPlayVideoData(const char *uid, VideoFrame &videoFrame) {
            if (_context) {
                if (_context->_videoDataControl) {
                    _context->_videoDataControl->onRenderVideoFrame(uid, videoFrame);
                }
            }

        }


    }
}
