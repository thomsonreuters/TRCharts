LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
 
LOCAL_MODULE := TRChartsJNI

rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

LOCAL_SRC_FILES := $(subst $(LOCAL_PATH)/,, $(call rwildcard,$(LOCAL_PATH),*.cpp))

LOCAL_LDLIBS := -lstdc++ -lc -lm -llog -landroid -ldl -lGLESv2 -lEGL

LOCAL_C_INCLUDES += $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../TRCharts
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../CodegenSupport/TRCodegenSupport
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../TR3DUtils
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../include

LOCAL_CFLAGS += -std=c++11 -fexceptions -g -ggdb -gdwarf-2 -frtti

LOCAL_STATIC_LIBRARIES += TRCharts
LOCAL_STATIC_LIBRARIES += TRCodegenSupport
LOCAL_STATIC_LIBRARIES += TR3DUtils

include $(BUILD_SHARED_LIBRARY)
