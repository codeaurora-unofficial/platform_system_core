# Copyright 2006 The Android Open Source Project

LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= logcat.cpp

LOCAL_SHARED_LIBRARIES := liblog

ifeq ($(strip $(QC_PROP)),true)
LOCAL_SHARED_LIBRARIES += libdiag
LOCAL_CFLAGS += -DUSE_DIAG
LOCAL_C_INCLUDES := vendor/qcom-opensource/diag
endif # QC_PROP

LOCAL_MODULE:= logcat

include $(BUILD_EXECUTABLE)

########################
include $(CLEAR_VARS)

LOCAL_MODULE := event-log-tags

# This will install the file in /system/etc
#
LOCAL_MODULE_CLASS := ETC

LOCAL_SRC_FILES := $(LOCAL_MODULE)
LOCAL_PREBUILT_STRIP_COMMENTS := 1

include $(BUILD_PREBUILT)
