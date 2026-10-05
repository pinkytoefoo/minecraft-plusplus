cmake_minimum_required(VERSION 3.24)
project(imgui LANGUAGES CXX)

# Track the actual physical directory of the imgui submodule
set(IMGUI_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/../../thirdparty/imgui")

add_library(imgui STATIC
    ${IMGUI_SRC_DIR}/imconfig.h
    ${IMGUI_SRC_DIR}/imgui.h
    ${IMGUI_SRC_DIR}/imgui.cpp
    ${IMGUI_SRC_DIR}/imgui_draw.cpp
    ${IMGUI_SRC_DIR}/imgui_internal.h
    ${IMGUI_SRC_DIR}/imgui_tables.cpp
    ${IMGUI_SRC_DIR}/imgui_widgets.cpp
    ${IMGUI_SRC_DIR}/imstb_rectpack.h
    ${IMGUI_SRC_DIR}/imstb_textedit.h
    ${IMGUI_SRC_DIR}/imstb_truetype.h
    ${IMGUI_SRC_DIR}/imgui_demo.cpp
    ${IMGUI_SRC_DIR}/backends/imgui_impl_glfw.h
    ${IMGUI_SRC_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_SRC_DIR}/backends/imgui_impl_opengl3.h
    ${IMGUI_SRC_DIR}/backends/imgui_impl_opengl3.cpp
)

# Export the include paths cleanly so your main app inherits them automatically
target_include_directories(imgui PUBLIC 
    ${IMGUI_SRC_DIR}
    ${IMGUI_SRC_DIR}/backends
)

# Link GLFW directly to ImGui so the backend headers can find glfw3.h
target_link_libraries(imgui PRIVATE glfw)
