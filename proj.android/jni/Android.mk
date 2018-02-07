LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/Scenes/Menu/SplashScene.cpp \
                   ../../Classes/Global/Localization/LocalizedStrings.cpp \
                   ../../Classes/Global/Variables.cpp \
                   ../../Classes/Scenes/Menu/MainScene.cpp \
                   ../../Classes/Scenes/Menu/MainMenu.cpp \
                   ../../Classes/Scenes/Menu/Settings.cpp \
                   ../../Classes/Scenes/Game/GameScene.cpp \
                   ../../Classes/Global/Utils.cpp \
                   ../../Classes/Objects/MenuBlock.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
