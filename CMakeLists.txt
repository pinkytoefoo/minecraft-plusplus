cmake_minimum_required(VERSION 3.10)

project(MC-Clone CXX C)

set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")

file(GLOB_RECURSE
    SOURCE_FILES
    src/*.cpp
    src/*.hpp
)


add_executable(MC-Clone ${SOURCE_FILES})

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

target_link_libraries(MC-Clone glad glfw imgui opengl32 glm gdi32)