/*
 * SPDX-FileCopyrightText: 2019-2025 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "vendor.lineage.touch-service.cheeseburger"

#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>
#include <TouchscreenGesture.h>

#include "KeyDisabler.h"
#include "KeySwapper.h"

using aidl::vendor::lineage::touch::KeyDisabler;
using aidl::vendor::lineage::touch::KeySwapper;
using aidl::vendor::lineage::touch::TouchscreenGesture;

int main() {
    binder_status_t status = STATUS_OK;

    ABinderProcess_setThreadPoolMaxThreadCount(0);

    std::shared_ptr<KeyDisabler> keyDisabler = ndk::SharedRefBase::make<KeyDisabler>();
    std::shared_ptr<KeySwapper> keySwapper = ndk::SharedRefBase::make<KeySwapper>();
    std::shared_ptr<TouchscreenGesture> gestureService = ndk::SharedRefBase::make<TouchscreenGesture>();

    const std::string keyDisabler_instance = std::string(KeyDisabler::descriptor) + "/default";
    status = AServiceManager_addService(keyDisabler->asBinder().get(), keyDisabler_instance.c_str());
    CHECK_EQ(status, STATUS_OK) << "Failed to add service " << keyDisabler_instance << " " << status;

    const std::string keySwapper_instance = std::string(KeySwapper::descriptor) + "/default";
    status = AServiceManager_addService(keySwapper->asBinder().get(), keySwapper_instance.c_str());
    CHECK_EQ(status, STATUS_OK) << "Failed to add service " << keySwapper_instance << " " << status;

    const std::string gesture_instance = std::string(TouchscreenGesture::descriptor) + "/default";
    status = AServiceManager_addService(gestureService->asBinder().get(), gesture_instance.c_str());
    CHECK_EQ(status, STATUS_OK) << "Failed to add service " << gesture_instance << " " << status;

    LOG(INFO) << "Touch HAL service is ready.";

    ABinderProcess_joinThreadPool();

    // Should never reach here
    LOG(ERROR) << "Touchscreen HAL service failed to join thread pool.";
    return EXIT_FAILURE;
}
