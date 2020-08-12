LOCAL_PATH := $(call my-dir)


include $(CLEAR_VARS)
LOCAL_MODULE := dby_engine_capture
LOCAL_SRC_FILES := $(LOCAL_PATH)/dby/$(TARGET_ARCH_ABI)/libdb_capture_utils_lib.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/dby/include
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := dby_engine_audio
LOCAL_SRC_FILES := $(LOCAL_PATH)/dby/$(TARGET_ARCH_ABI)/libdbyAudioUtil.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/dby/include
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := dby_engine_core
LOCAL_SRC_FILES := $(LOCAL_PATH)/dby/$(TARGET_ARCH_ABI)/libDbyEngine.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/dby/include
LOCAL_SHARED_LIBRARIES :=dby_engine_audio  dby_engine_capture
include $(PREBUILT_SHARED_LIBRARY)


##============== agora creator include libyuv so ====================
include $(CLEAR_VARS)
LOCAL_MODULE := libyuv
LOCAL_SRC_FILES := $(LOCAL_PATH)/libyuv/$(TARGET_ARCH_ABI)/libyuv.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/libyuv/include
include $(PREBUILT_SHARED_LIBRARY)
#============== agora creator include libyuv so ====================

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2djs_shared

LOCAL_MODULE_FILENAME := libcocos2djs

ifeq ($(USE_ARM_MODE),1)
LOCAL_ARM_MODE := arm
endif

#============== dby creator js bridge ====================
LOCAL_SRC_FILES = ../../../Classes/dby/jsb_dbyCreator.cpp \
				   ../../../Classes/dby/DBYContext.cpp \
				   ../../../Classes/dby/DbyEngineEventHandler.cpp \
				   ../../../Classes/dby/DbyVideoRawDataControl.cpp \
				   ../../../Classes/dby/CacheVideoFrame.cpp \
LOCAL_C_INCLUDES += $(LOCAL_PATH)/dby/include
#============== dby creator js bridge ====================
LOCAL_SRC_FILES += hellojavascript/main.cpp \
				   ../../../Classes/AppDelegate.cpp \
				   ../../../Classes/jsb_module_register.cpp \

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../Classes

ifeq ($(USE_ANY_SDK),1)
LOCAL_SRC_FILES += ../../../Classes/anysdk/SDKManager.cpp \
				   ../../../Classes/anysdk/jsb_anysdk_basic_conversions.cpp \
				   ../../../Classes/anysdk/manualanysdkbindings.cpp \
				   ../../../Classes/anysdk/jsb_anysdk_protocols_auto.cpp

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../Classes/anysdk

LOCAL_WHOLE_STATIC_LIBRARIES := PluginProtocolStatic
endif

#============== dby creator include shared libraries ====================
LOCAL_SHARED_LIBRARIES := dby_engine_core  dby_engine_audio  libyuv
#============== dby creator include shared libraries ====================

LOCAL_STATIC_LIBRARIES := cocos2d_js_static

LOCAL_EXPORT_CFLAGS := -DCOCOS2D_DEBUG=2 -DCOCOS2D_JAVASCRIPT

include $(BUILD_SHARED_LIBRARY)


$(call import-module, scripting/js-bindings/proj.android)
