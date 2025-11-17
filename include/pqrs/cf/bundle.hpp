#pragma once

// pqrs::cf::bundle v0.0

// (C) Copyright Takayama Fumihiko 2025.
// Distributed under the Boost Software License, Version 1.0.
// (See https://www.boost.org/LICENSE_1_0.txt)

#include <CoreFoundation/CoreFoundation.h>
#include <filesystem>
#include <optional>
#include <pqrs/cf/url.hpp>
#include <string>

namespace pqrs {
namespace cf {
namespace bundle {

std::optional<std::string> get_package_type(const std::filesystem::path& bundle_path) {
  if (auto url = pqrs::cf::make_url(bundle_path.string())) {
    if (auto bundle = pqrs::cf::cf_ptr(CFBundleCreate(nullptr, *url))) {
      if (auto info_dictionary = CFBundleGetInfoDictionary(*bundle)) {
        if (auto type = CFDictionaryGetValue(info_dictionary,
                                             CFSTR("CFBundlePackageType"))) {
          return pqrs::cf::make_string(type);
        }
      }
    }
  }

  return std::nullopt;
}

} // namespace bundle
} // namespace cf
} // namespace pqrs
