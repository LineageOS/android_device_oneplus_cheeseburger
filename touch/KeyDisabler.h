/*
 * SPDX-FileCopyrightText: 2021 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <aidl/vendor/lineage/touch/BnKeyDisabler.h>

namespace aidl {
namespace vendor {
namespace lineage {
namespace touch {

class KeyDisabler : public BnKeyDisabler {
  public:
    KeyDisabler();

    ndk::ScopedAStatus getEnabled(bool* _aidl_return) override;
    ndk::ScopedAStatus setEnabled(bool enabled) override;

  private:
    const bool has_key_disabler_;
};

}  // namespace touch
}  // namespace lineage
}  // namespace vendor
}  // namespace aidl
