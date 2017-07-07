LOCAL_PATH := $(call my-dir)

ifeq ($(BOARD_PROVIDES_LIBRIL),true)

include $(CLEAR_VARS)
LOCAL_MODULE := libril
LOCAL_SRC_FILES_64 := lib64/libril.so
LOCAL_SRC_FILES_32 := lib/libril.so
LOCAL_MULTILIB := both
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
include $(BUILD_PREBUILT)

endif
