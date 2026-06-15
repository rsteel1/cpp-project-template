# cmake/sanitizers.cmake
# Usage: apply_sanitizers(your_target)
# Configure at cmake time with -DENABLE_ASAN=ON or -DENABLE_TSAN=ON
# Never enable both at once — they are incompatible.

function(apply_sanitizers target)
    if(ENABLE_ASAN AND ENABLE_TSAN)
        message(FATAL_ERROR "ENABLE_ASAN and ENABLE_TSAN cannot both be ON — they are incompatible.")
    endif()

    if(ENABLE_ASAN)
        message(STATUS "AddressSanitizer + UBSanitizer enabled for ${target}")
        target_compile_options(${target} PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
        target_link_options(${target} PRIVATE -fsanitize=address,undefined)
    endif()

    if(ENABLE_TSAN)
        message(STATUS "ThreadSanitizer enabled for ${target}")
        target_compile_options(${target} PRIVATE -fsanitize=thread -fno-omit-frame-pointer)
        target_link_options(${target} PRIVATE -fsanitize=thread)
    endif()
endfunction()
