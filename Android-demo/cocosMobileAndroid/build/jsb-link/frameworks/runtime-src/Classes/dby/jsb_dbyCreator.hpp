

#ifndef jsb_agoraCreator_hpp
#define jsb_agoraCreator_hpp
#pragma once

#include "include_file.h"
#include "DBYContext.hpp"

extern "C"
{
static se::Object *js_cocos2dx_dbyCreator_prototype = NULL;
static se::Class *js_cocos2dx_dbyCreator_class = NULL;
static duobeiyun::cocos::DBYContext *_context =NULL;
bool js_register_cocos2dx_extension_dbyCreator(se::Object *obj);
bool register_jsb_dbyCreator(se::Object *obj);
}
#endif /* jsb_agoraCreator_hpp */
