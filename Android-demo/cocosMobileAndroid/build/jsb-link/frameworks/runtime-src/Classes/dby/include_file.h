
#ifndef dby_include_file_h
#define dby_include_file_h
#pragma once
#include "base/ccConfig.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#include "cocos/scripting/js-bindings/jswrapper/SeApi.h"
#include "scripting/js-bindings/manual/jsb_conversions.hpp"
#include "scripting/js-bindings/manual/jsb_global.h"
#include "cocos2d.h"
#include "platform/CCApplication.h"
#include "base/CCScheduler.h"
#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include "jsb_cocos2dx_extension_manual.hpp"
#include "cocos/scripting/js-bindings/auto/jsb_cocos2dx_extension_auto.hpp"
#include <vector>
#include <string.h>

#define AGORA_TAG "duobeiyun_cocos"
#define AGORA_VIDEO_FRAME agora::media::IVideoFrameObserver::VideoFrame
#define AGORA_STATIC_BOOL static bool
#define AGORA_EXPORT_C extern "C"
#define COCOS_TEXTURE cocos2d::Texture2D
#define UINT32 unsigned int
#endif
#endif /* include_file_h */
