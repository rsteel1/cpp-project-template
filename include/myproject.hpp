#pragma once

// ─────────────────────────────────────────────────────────────
//  myproject.hpp  —  replace with your actual header
// ─────────────────────────────────────────────────────────────
//
//  For header-only projects (e.g. units library, TypeList):
//    - Put all your implementation here
//    - Delete src/myproject.cpp
//    - In CMakeLists.txt change STATIC -> INTERFACE
//
// ─────────────────────────────────────────────────────────────

#include <string_view>

namespace myproject {

/// Returns a greeting string. Replace with your actual API.
[[nodiscard]] std::string_view hello() noexcept;

} // namespace myproject
