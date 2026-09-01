#pragma once

#define ASSERT_INIT(initFunc) \
if(!(initFunc)) { \
    std::cerr << "failed to initialize function " << #initFunc << " at\nFile: " << __FILE__ << "\nLine: " << __LINE__ << "\n"; \
}
