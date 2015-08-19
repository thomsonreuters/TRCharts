LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
 
LOCAL_MODULE := TRCharts

rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

LOCAL_SRC_FILES += $(subst $(LOCAL_PATH)/,, $(call rwildcard,$(LOCAL_PATH)/TRCharts,*.cpp))

LOCAL_C_INCLUDES += $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../CodegenSupport/TRCodegenSupport
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../TR3DUtils
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../include

LOCAL_CFLAGS += -std=c++11 -fexceptions -g -ggdb -gdwarf-2 -frtti

include $(BUILD_STATIC_LIBRARY)
