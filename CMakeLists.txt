cmake_minimum_required(VERSION 3.24)

project(mc CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE
    SOURCE_FILES
    src/*.cpp
    # need .hpp for single-header files and templated functions inside header files
    src/*.hpp
)

add_executable(mc ${SOURCE_FILES})

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/assets" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

add_subdirectory(thirdparty/glfw)
add_subdirectory(thirdparty/glm)
add_subdirectory(thirdparty/imgui)
add_subdirectory(thirdparty/glad)

target_include_directories(mc PRIVATE src)
target_include_directories(mc PRIVATE thirdparty/glfw/include)
target_include_directories(mc PRIVATE thirdparty/glad/include)
target_include_directories(mc PRIVATE thirdparty/glm/glm)
target_include_directories(mc PRIVATE thirdparty/imgui)
target_include_directories(mc PRIVATE thirdparty/imgui/backends)
target_include_directories(mc PRIVATE thirdparty/stbi)

if(WIN32)
    target_link_libraries(mc PRIVATE dwmapi)
endif()

find_package(OpenGL REQUIRED)

target_link_libraries(mc PRIVATE
    glad 
    glfw 
    imgui 
    glm 
    OpenGL::GL
)