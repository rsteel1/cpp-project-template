#ifndef MYPROJECT_MYPROJECT_H_
#define MYPROJECT_MYPROJECT_H_

// myproject.h — replace with your actual header
//
// For header-only projects (e.g. a units library, TypeList):
//   - Put all implementation here
//   - Delete src/myproject/myproject.cpp
//   - In src/myproject/BUILD remove srcs and change to cc_library with hdrs only

#include <string_view>

namespace myproject {

// Returns a greeting string. Replace with your actual API.
[[nodiscard]] std::string_view hello() noexcept;

}  // namespace myproject

#endif  // MYPROJECT_MYPROJECT_H_
