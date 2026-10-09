#pragma once

#include <stdexcept>
#include <format>
#include <cstdlib>

#if defined(_MSC_VER)
#  define NO_UNIQUE_ADDRESS [[msvc::no_unique_address]]
#else
#  define NO_UNIQUE_ADDRESS [[no_unique_address]]
#endif

#ifdef MC_DEBUG
// todo: wrap around debug ifdef check
#define ASSERT_INIT(initFunc) \
do { \
    if(!(initFunc)) { \
        throw std::runtime_error{std::format("failed to initialize function {} at\n  file: {}\n  line{}\n", #initFunc, __FILE__, __LINE__)}; \
    } \
} while(0)
#else
#define ASSERT_INIT(initFunc) \
do { \
    (void)(initFunc); \
} while(0)
#warning "ASSERT_INIT not gon work"
#endif
