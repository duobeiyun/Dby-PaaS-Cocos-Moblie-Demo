
#include "jsb_dbyCreator.hpp"
#include "DbyEngineEventHandler.hpp"
#include "DbyVideoRawDataControl.h"


AGORA_EXPORT_C
{
    #define CHECK_ENGINE()    \
    if (!(_context->_rtcEngine)) \
    {                           \
        CCLOG("%s did not initialize agora rtc engine yet, please initialize it first!", AGORA_TAG);\
        return false;          \
    }
    
    AGORA_STATIC_BOOL js_agoraCreator_finalize(se::State& s){
        CCLOGINFO("%s : js_agoraCreator_finalize", AGORA_TAG);
        if (_context)
        {
        }
        return true;
    }
    SE_BIND_FINALIZE_FUNC(js_agoraCreator_finalize)

    AGORA_STATIC_BOOL js_cocos2dx_extension_agoraCreator_constructor(se::State& s)
    {
        if (_context == NULL)
        {
            _context = new duobeiyun::cocos::DBYContext();
            _context->_videoDataControl=new duobeiyun::cocos::DbyVideoRawDataControl();
//            _context->_rtcEngine = createAgoraRtcEngine();
        }
        se::Object* obj = s.thisObject();
        _context->_refObj = obj;
        if (obj)
        {
            obj->setPrivateData(_context);
            se::Value func;
            if (obj->getProperty("_ctor", &func)) {
                func.toObject()->call(se::EmptyValueArray, obj);
            }
        }
        return true;
    }
    SE_BIND_CTOR(js_cocos2dx_extension_agoraCreator_constructor, js_cocos2dx_dbyCreator_class, js_agoraCreator_finalize)

    AGORA_STATIC_BOOL js_cocos2dx_extension_agoraCreator_joinChannel(se::State& s)
    {
        const auto& args = s.args();
        size_t argc = args.size();
        CC_UNUSED bool ok = true;
        if (argc == 3) {

            std::string channelId;
            ok &= seval_to_std_string(args[0], &channelId);

            std::string uid;
            ok &= seval_to_std_string(args[1], &uid);

            std::string nickname;
            ok &= seval_to_std_string(args[2], &nickname);
            

            joinChannel(channelId.c_str(), uid.c_str(),nickname.c_str());
//            int ret = _context->_rtcEngine->joinChannel(token.c_str(), channelId.c_str(), info.c_str(), uid);
//            int32_to_seval(ret, &s.rval());
//            CCLOG("%s js_cocos2dx_extension_agoraCreator_joinChannel ret = %d", AGORA_TAG, ret);
            return true;
        }
//        SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 4);
        CCLOGERROR("%s error js_cocos2dx_extension_agoraCreator_joinChannel ", AGORA_TAG);
        return false;
    }
    SE_BIND_FUNC(js_cocos2dx_extension_agoraCreator_joinChannel)

    AGORA_STATIC_BOOL js_cocos2dx_extension_agoraCreator_initialize(se::State& s)
    {
        const auto& args = s.args();
        size_t argc = args.size();
        CC_UNUSED bool ok = true;
        if (argc == 2)
        {
            std::string appId;
            std::string appkey;
            ok &= seval_to_std_string(args[0], &appkey);
            SE_PRECONDITION2(ok, false, "js_cocos2dx_extension_agoraCreator_initialize : Error processing arguments");

            ok &= seval_to_std_string(args[1], &appId);
            SE_PRECONDITION2(ok, false, "js_cocos2dx_extension_agoraCreator_initialize : Error processing arguments");

            _context->_dbyEngineEventHandler = new duobeiyun::cocos::DbyEngineEventHandler(_context);
            auto ctx=new duobeiyun::DbyEngineContext;
            ctx.appKey = appId.c_str();
            ctx.appId = appId.c_str();
//            ctx->appKey =
//            ctx->appId =
            ctx->eventHandler = _context->_dbyEngineEventHandler;
            initialize(*ctx);
            CCLOG("%s js_cocos2dx_extension_agoraCreator_initialize appId = %s", AGORA_TAG, appId.c_str());
            return true;
        }
        CCLOGERROR("%s error js_cocos2dx_extension_agoraCreator_initialize please input your appId", AGORA_TAG);
        return false;
    }
    SE_BIND_FUNC(js_cocos2dx_extension_agoraCreator_initialize)

    AGORA_STATIC_BOOL js_cocos2dx_extension_agoraCreator_leaveChannel(se::State& s)
    {
        return false;
    }
    SE_BIND_FUNC(js_cocos2dx_extension_agoraCreator_leaveChannel)

    AGORA_STATIC_BOOL js_cocos2dx_extension_agoraCreator_enableVideoObserver(se::State& s) {
        return true;
    }
    SE_BIND_FUNC(js_cocos2dx_extension_agoraCreator_enableVideoObserver)

    AGORA_STATIC_BOOL js_cocos2dx_extension_agoraCreator_disableVideoObserver(se::State& s) {
        return true;
    }
    SE_BIND_FUNC(js_cocos2dx_extension_agoraCreator_disableVideoObserver)

    AGORA_STATIC_BOOL js_cocos2dx_extension_agoraCreator_setParameters(se::State& s)
    {
        return false;
    }
    SE_BIND_FUNC(js_cocos2dx_extension_agoraCreator_setParameters)

    AGORA_STATIC_BOOL js_cocos2dx_extension_agoraCreator_enableVideo(se::State& s)
    {
        return false;
    }
    SE_BIND_FUNC(js_cocos2dx_extension_agoraCreator_enableVideo)

    AGORA_STATIC_BOOL js_cocos2dx_extension_agoraCreator_disableVideo(se::State& s)
    {
        return false;
    }
    SE_BIND_FUNC(js_cocos2dx_extension_agoraCreator_disableVideo)
    
    AGORA_STATIC_BOOL js_cocos2dx_extension_agoraCreator_updateTexture(se::State& s)
    {
        const auto& args = s.args();
        size_t argc = args.size();
        CC_UNUSED bool ok = true;
        if (!(_context->_dbyEngineEventHandler))
        {
            ok = false;
            return ok;
        }

        if (argc == 1)
        {

            std::string uid;
            ok &= seval_to_std_string(args[0], &uid);
            uid = "1111";
            SE_PRECONDITION2(ok, false, "Error processing arguments");
            COCOS_TEXTURE* ret = _context->_videoDataControl->updateTexture("1111");
            if (ret)
            {
                const char* typeName = typeid(*ret).name();
                ok &= native_ptr_to_seval<COCOS_TEXTURE>(ret, &s.rval());
                SE_PRECONDITION2(ok, false, "js_HomeAgora_getTexture : Error processing arguments");
            }
            return true;
        }
        SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 4);
        return false;
    }
    SE_BIND_FUNC(js_cocos2dx_extension_agoraCreator_updateTexture)

    bool js_register_cocos2dx_extension_dbyCreator(se::Object* obj)
    {
        auto cls = se::Class::create("adbyCreator", obj, nullptr, _SE(js_cocos2dx_extension_agoraCreator_constructor));
        cls->defineFunction("initialize", _SE(js_cocos2dx_extension_agoraCreator_initialize));
        cls->defineFunction("leaveChannel", _SE(js_cocos2dx_extension_agoraCreator_leaveChannel));
        cls->defineFunction("joinChannel", _SE(js_cocos2dx_extension_agoraCreator_joinChannel));
        cls->defineFunction("updateTexture", _SE(js_cocos2dx_extension_agoraCreator_updateTexture));
        cls->defineFinalizeFunction(_SE(js_agoraCreator_finalize));
        cls->install();
        js_cocos2dx_dbyCreator_prototype = cls->getProto();
        js_cocos2dx_dbyCreator_class = cls;
        se::ScriptEngine::getInstance()->clearException();
        return true;
    }

    bool register_jsb_dbyCreator(se::Object* obj)
    {
        return js_register_cocos2dx_extension_dbyCreator(obj);
    }
}
