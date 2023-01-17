/*
 * Copyright (C) 2019,2021 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <android-base/file.h>
#include <android-base/logging.h>
#include <android-base/strings.h>

#include "KeySwapper.h"

namespace {
constexpr const char kControlPath[] = "/proc/s1302/key_rep";
};  // anonymous namespace

namespace vendor {
namespace lineage {
namespace touch {
namespace V1_0 {
namespace implementation {

KeySwapper::KeySwapper() : has_key_swapper_(!access(kControlPath, R_OK | W_OK)) {}

// Methods from ::vendor::lineage::touch::V1_0::IKeySwapper follow.
Return<bool> KeySwapper::isEnabled() {
    if (!has_key_swapper_) return false;

    std::string buf;
    if (!android::base::ReadFileToString(kControlPath, &buf)) {
        LOG(ERROR) << "Failed to read " << kControlPath;
        return false;
    }

    return std::stoi(android::base::Trim(buf)) == 1;
}

Return<bool> KeySwapper::setEnabled(bool enabled) {
    if (!has_key_swapper_) return false;

    if (!android::base::WriteStringToFile(std::to_string(enabled), kControlPath)) {
        LOG(ERROR) << "Failed to write " << kControlPath;
        return false;
    }

    return true;
}

}  // namespace implementation
}  // namespace V1_0
}  // namespace touch
}  // namespace lineage
}  // namespace vendor
