#pragma once

// Platform detection using predefined macros
#ifdef _WIN32
    // Windows x64/x86
#   ifdef _WIN64
        // Windows x64
#       define ELMT_PLATFORM_WINDOWS
#   else
        // Windows x86
#       error "32-Bit Builds are not supported!"
#   endif
#elif defined(__APPLE__) || defined(__MACH__)
#   include <TargetConditionals.h>
#   if TARGET_IPHONE_SIMULATOR == 1
#       error "IOS simulator is not supported!"
#   elif TARGET_OS_IPHONE == 1
#       define ELMT_PLATFORM_IOS
#       error "IOS is not supported!"
#   elif TARGET_OS_MAC == 1
#       define ELMT_PLATFORM_MACOS
#       error "MacOS is not supported!"
#   else
#       error "Unknown Apple platform!"
#   endif
#elif defined(__ANDROID__)
#   define ELMT_PLATFORM_ANDROID
#   error "Android is not supported!"
#elif defined(__linux__)
#   define ELMT_PLATFORM_LINUX
#   error "Linux is not supported!"
#else
    /* Unknown compiler / platform */
#   error "Unknown platform!"
#endif // End of platform detection


