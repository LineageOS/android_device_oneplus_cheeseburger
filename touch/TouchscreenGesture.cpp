/*
 * Copyright (C) 2019 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "TouchscreenGestureService"

#include "TouchscreenGesture.h"
#include <android-base/logging.h>
#include <fstream>

namespace vendor {
namespace lineage {
namespace touch {
namespace V1_0 {
namespace implementation {

const std::map<int32_t, TouchscreenGesture::GestureInfo> TouchscreenGesture::kGestureInfoMap = {
    {0, {251, "Two fingers down swipe", "/proc/touchpanel/double_swipe_enable"}},
    {1, {252, "Down arrow", "/proc/touchpanel/down_arrow_enable"}},
    {2, {253, "Left arrow", "/proc/touchpanel/left_arrow_enable"}},
    {3, {254, "Right arrow", "/proc/touchpanel/right_arrow_enable"}},
    {4, {247, "Letter M", "/proc/touchpanel/letter_m_enable"}},
    {5, {250, "Letter O", "/proc/touchpanel/letter_o_enable"}},
    {6, {248, "Letter S", "/proc/touchpanel/letter_s_enable"}},
    {7, {246, "Letter W", "/proc/touchpanel/letter_w_enable"}},
    {8, {255, "Single Tap", "/proc/touchpanel/single_tap_enable"}},
};

Return<void> TouchscreenGesture::getSupportedGestures(getSupportedGestures_cb resultCb) {
    std::vector<Gesture> gestures;

    for (const auto& entry : kGestureInfoMap) {
        if (access(entry.second.path, F_OK) != -1) {
            gestures.push_back({entry.first, entry.second.name, entry.second.keycode});
        }
    }
    resultCb(gestures);

    return Void();
}

Return<bool> TouchscreenGesture::setGestureEnabled(
    const ::vendor::lineage::touch::V1_0::Gesture& gesture, bool enabled) {
    const auto entry = kGestureInfoMap.find(gesture.id);
    if (entry == kGestureInfoMap.end()) {
        return false;
    }

    std::ofstream file(entry->second.path);
    file << (enabled ? "1" : "0");
    LOG(DEBUG) << "Wrote file " << entry->second.path << " fail " << file.fail();
    return !file.fail();
}

}  // namespace implementation
}  // namespace V1_0
}  // namespace touch
}  // namespace lineage
}  // namespace vendor
