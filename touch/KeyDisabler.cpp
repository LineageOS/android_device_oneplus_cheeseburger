/*
 * SPDX-FileCopyrightText: 2019 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#include <android-base/file.h>
#include <android-base/logging.h>
#include <android-base/strings.h>

#include "KeyDisabler.h"

namespace {
constexpr const char kControlPath[] = "/proc/touchpanel/key_disable";
constexpr const char kFpcPath[] =
    "/sys/module/fpc1020_tee/parameters/ignor_home_for_ESD";
};  // anonymous namespace

namespace aidl {
namespace vendor {
namespace lineage {
namespace touch {

KeyDisabler::KeyDisabler() : has_key_disabler_(!access(kControlPath, R_OK | W_OK)) {}

ndk::ScopedAStatus KeyDisabler::getEnabled(bool* _aidl_return) {
    if (!has_key_disabler_) {
        *_aidl_return = false;
        return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
    }

    std::string controlBuf, fpcBuf;
    if (!android::base::ReadFileToString(kControlPath, &controlBuf) ||
        !android::base::ReadFileToString(kFpcPath, &fpcBuf)) {
        LOG(ERROR) << "Failed to read key disabler state files";
        *_aidl_return = false;
        return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
    }

    *_aidl_return = android::base::Trim(controlBuf) == "0" && android::base::Trim(fpcBuf) == "0";
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus KeyDisabler::setEnabled(bool enabled) {
    if (!has_key_disabler_) {
        return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
    }

    if (!android::base::WriteStringToFile(std::to_string(enabled), kControlPath)) {
        LOG(ERROR) << "Failed to write " << kControlPath;
        return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
    }

    if (!android::base::WriteStringToFile((enabled ? "1" : "0"), kFpcPath)) {
        LOG(ERROR) << "Failed to write " << kFpcPath;
        return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
    }

    return ndk::ScopedAStatus::ok();
}

}  // namespace touch
}  // namespace lineage
}  // namespace vendor
}  // namespace aidl
