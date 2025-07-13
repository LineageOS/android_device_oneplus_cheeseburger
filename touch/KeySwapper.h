/*
 * SPDX-FileCopyrightText: 2019-2025 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <aidl/vendor/lineage/touch/BnKeySwapper.h>

namespace aidl {
namespace vendor {
namespace lineage {
namespace touch {

class KeySwapper : public BnKeySwapper {
  public:
    KeySwapper();

    ndk::ScopedAStatus getEnabled(bool* _aidl_return) override;
    ndk::ScopedAStatus setEnabled(bool enabled) override;

  private:
    const bool has_key_swapper_;
};

}  // namespace touch
}  // namespace lineage
}  // namespace vendor
}  // namespace aidl
