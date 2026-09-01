cmake_minimum_required(VERSION 3.10)

project(glad C)

# file(
#     SOURCE_FILES
#     src/glad.c
#     include/glad/glad.h
#     include/KHR/khrplatform.h
# )

# set(
#     SOURCE_FILES
#     src/glad.c
#     include/glad/glad.h
#     include/KHR/khrplatform.h
# )

include_directories(include)

add_library(glad STATIC src/glad.c include/glad/glad.h include/KHR/khrplatform.h)