cmake_minimum_required(VERSION 3.10)

project(mc CXX C)

set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE
    SOURCE_FILES
    src/*.cpp
    src/*.hpp
)

add_executable(mc ${SOURCE_FILES})

add_subdirectory(thirdparty/glfw)
add_subdirectory(thirdparty/glm)
add_subdirectory(thirdparty/imgui)
add_subdirectory(thirdparty/glad)
include_directories(src)
include_directories(thirdparty/glfw/include)
include_directories(thirdparty/glad/include)
include_directories(thirdparty/glm/glm)
include_directories(thirdparty/imgui)
include_directories(thirdparty/imgui/backends)
include_directories(thirdparty/stbi)

if(WIN32)
    target_link_libraries(MC-Clone dwmapi)
endif()

find_package(OpenGL REQUIRED)

target_link_libraries(mc
    glad 
    glfw 
    imgui 
    glm 
    OpenGL::GL
)
