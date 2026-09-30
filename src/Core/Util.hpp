#pragma once

#include <iostream>
#include <cstdlib>

#if defined(_MSC_VER)
#  define NO_UNIQUE_ADDRESS [[msvc::no_unique_address]]
#else
#  define NO_UNIQUE_ADDRESS [[no_unique_address]]
#endif

// todo: wrap around debug ifdef check
#define ASSERT_INIT(initFunc) \
do { \
    if(!(initFunc)) { \
        std::cerr << "failed to initialize function " << #initFunc << " at\n\tfile: " << __FILE__ << "\n\tline: " << __LINE__ << "\n"; \
        std::exit(1); \
    } \
} while(0)
