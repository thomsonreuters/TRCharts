BASE_PATH := $(call my-dir)

include $(BASE_PATH)/TRChartsJNI/Android.mk
 
include $(BASE_PATH)/../../TRCharts/Android.mk

include $(BASE_PATH)/../../../CodegenSupport/TRCodegenSupport/Android.mk

include $(BASE_PATH)/../../../TR3DUtils/Android.mk