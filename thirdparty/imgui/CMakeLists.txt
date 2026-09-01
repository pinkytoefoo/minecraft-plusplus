cmake_minimum_required(VERSION 3.10)

project(imgui CXX)

set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

include_directories(../glfw/include)

add_library(
    imgui STATIC
    imconfig.h
	imgui.h
	imgui.cpp
	imgui_draw.cpp
	imgui_internal.h
	imgui_tables.cpp
	imgui_widgets.cpp
	imstb_rectpack.h
	imstb_textedit.h
	imstb_truetype.h
	imgui_demo.cpp
    backends/imgui_impl_glfw.h
    backends/imgui_impl_glfw.cpp
    backends/imgui_impl_opengl3.h
    backends/imgui_impl_opengl3.cpp
)
