/*
 * Copyright (C) 2019 The LineageOS Project
 *
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

namespace vendor {
namespace lineage {
namespace touch {
namespace V1_0 {
namespace implementation {

KeyDisabler::KeyDisabler() : has_key_disabler_(!access(kControlPath, R_OK | W_OK)) {}

// Methods from ::vendor::lineage::touch::V1_0::IKeyDisabler follow.
Return<bool> KeyDisabler::isEnabled() {
    if (!has_key_disabler_) return false;

    std::string buf;
    if (!android::base::ReadFileToString(kControlPath, &buf)) {
        LOG(ERROR) << "Failed to read " << kControlPath;
        return false;
    }

    if (!android::base::ReadFileToString(kFpcPath, &buf)) {
        LOG(ERROR) << "Failed to read " << kFpcPath;
        return false;
    }

    return std::stoi(android::base::Trim(buf)) == 0;
}

Return<bool> KeyDisabler::setEnabled(bool enabled) {
    if (!has_key_disabler_) return false;

    if (!android::base::WriteStringToFile(std::to_string(enabled), kControlPath)) {
        LOG(ERROR) << "Failed to write " << kControlPath;
        return false;
    }

    if (!android::base::WriteStringToFile((enabled ? "1" : "0"), kFpcPath)) {
        LOG(ERROR) << "Failed to write " << kFpcPath;
        return false;
    }

    return true;
}

}  // namespace implementation
}  // namespace V1_0
}  // namespace touch
}  // namespace lineage
}  // namespace vendor

