#
# Copyright (C) 2017 The LineageOS Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

#
# This file sets variables that control the way modules are built
# thorughout the system. It should not be used to conditionally
# disable makefiles (the proper mechanism to control what gets
# included in a build is to use PRODUCT_PACKAGES in a product
# definition file).
#

# Inherit from oneplus msm8998-common
-include device/oneplus/msm8998-common/BoardConfigCommon.mk

DEVICE_PATH := device/oneplus/cheeseburger

# Assertions
TARGET_BOARD_INFO_FILE ?= $(DEVICE_PATH)/board-info.txt
TARGET_OTA_ASSERT_DEVICE := cheeseburger,OnePlus5,oneplus5

# SELinux
BOARD_SEPOLICY_DIRS += $(DEVICE_PATH)/sepolicy/vendor
BOARD_PLAT_PUBLIC_SEPOLICY_DIR += $(DEVICE_PATH)/sepolicy/public
BOARD_PLAT_PRIVATE_SEPOLICY_DIR += $(DEVICE_PATH)/sepolicy/private

# inherit from the proprietary version
-include vendor/oneplus/cheeseburger/BoardConfigVendor.mk

DEVICE_MANIFEST_FILE += $(DEVICE_PATH)/manifest.xml
