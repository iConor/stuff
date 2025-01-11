#ifndef CONTEXT_H
#define CONTEXT_H



#if defined(_MSC_VER)
    #define COMPILER_MSVC 1
    #if defined(_M_IX86)
        #define ARCH_X86 1
    #elif defined(_M_AMD64)
        #define ARCH_X64 1
    #else
        #error Architecture not identified.
    #endif
#elif defined(__GNUC__)
    #define COMPILER_GCC 1
    #if defined(__i386__)
        #define ARCH_X86 1
    #elif defined(__amd64__)
        #define ARCH_X64 1
    #else
        #error Architecture not identified.
    #endif
#else
    #error Compiler not identified.
#endif

#if defined(__clang__)
    #define COMPILER_CLANG 1
#endif



#if defined(_WIN32)
    #define OS_WINDOWS 1
#elif defined(__linux__)
    #define OS_LINUX 1
#elif defined(__APPLE__) && defined(__MACH__)
    #define OS_MACOS 1
#else
    #error Operating system not identified.
#endif



#if !defined(COMPILER_MSVC)
    #define COMPILER_MSVC 0
#endif

#if !defined(COMPILER_GCC)
    #define COMPILER_GCC 0
#endif

#if !defined(COMPILER_CLANG)
    #define COMPILER_CLANG 0
#endif


#if !defined(ARCH_X86)
    #define ARCH_X86 0
#endif

#if !defined(ARCH_X64)
    #define ARCH_X64 0
#endif


#if !defined(OS_WINDOWS)
    #define OS_WINDOWS 0
#endif

#if !defined(OS_LINUX)
    #define OS_LINUX 0
#endif

#if !defined(OS_MACOS)
    #define OS_MACOS 0
#endif



#endif /* CONTEXT_H */
