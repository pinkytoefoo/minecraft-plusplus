cmake_minimum_required(VERSION 3.24)
project(mc LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

add_subdirectory(thirdparty/glfw)
add_subdirectory(thirdparty/glm)
add_subdirectory(thirdparty/imgui)
add_subdirectory(thirdparty/glad)

add_library(stb INTERFACE)
target_include_directories(stb SYSTEM INTERFACE thirdparty/stbi)

add_library(mc_warnings INTERFACE)
if(MSVC)
    target_compile_options(mc_warnings INTERFACE /W4 /permissive-)
else()
    target_compile_options(mc_warnings INTERFACE -Wall -Wextra -Wshadow -Wconversion)
endif()

file(GLOB_RECURSE MC_SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_executable(mc ${MC_SOURCES})

target_include_directories(mc PRIVATE
    thirdparty/glfw/include
    thirdparty/glad/include
    thirdparty/glm/glm
    thirdparty/imgui
    thirdparty/imgui/backends
    thirdparty/stbi
    src
)

target_compile_definitions(mc PRIVATE GLFW_INCLUDE_NONE)
target_link_libraries(mc PRIVATE mc_warnings glad glfw imgui glm stb)
if(WIN32)
    target_link_libraries(mc PRIVATE dwmapi)
endif()

add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:mc>/assets)
add_dependencies(mc copy_assets)