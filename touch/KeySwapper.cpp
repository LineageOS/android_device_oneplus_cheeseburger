/*
 * SPDX-FileCopyrightText: 2019-2025 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#include <android-base/file.h>
#include <android-base/logging.h>
#include <android-base/strings.h>

#include "KeySwapper.h"

namespace {
constexpr const char kControlPath[] = "/proc/s1302/key_rep";
};  // anonymous namespace

namespace aidl {
namespace vendor {
namespace lineage {
namespace touch {

KeySwapper::KeySwapper() : has_key_swapper_(!access(kControlPath, R_OK | W_OK)) {}

ndk::ScopedAStatus KeySwapper::getEnabled(bool* _aidl_return) {
    if (!has_key_swapper_) {
        *_aidl_return = false;
        return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
    }

    std::string buf;
    if (!android::base::ReadFileToString(kControlPath, &buf)) {
        LOG(ERROR) << "Failed to read " << kControlPath;
        *_aidl_return = false;
        return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
    }

    *_aidl_return = std::stoi(android::base::Trim(buf)) == 1;
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus KeySwapper::setEnabled(bool enabled) {
    if (!has_key_swapper_) {
        return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
    }

    if (!android::base::WriteStringToFile(std::to_string(enabled), kControlPath)) {
        LOG(ERROR) << "Failed to write " << kControlPath;
        return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
    }

    return ndk::ScopedAStatus::ok();
}

}  // namespace touch
}  // namespace lineage
}  // namespace vendor
}  // namespace aidl
