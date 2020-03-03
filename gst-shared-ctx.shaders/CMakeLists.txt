cmake_minimum_required (VERSION 3.5)
project (GstShared)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE TRUE)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GLFW3 REQUIRED glfw3 gl)
pkg_check_modules(X11 REQUIRED x11 xrandr xi)

set (DEPS_INCLUDE_DIRS ${GLFW3_INCLUDE_DIRS}, ${X11_INCLUDE_DIRS})
set (DEPS_LIBRARIES ${GLFW3_LIBRARIES} ${X11_LIBRARIES} -ldl)
set (DEPS_CFLAGS_OTHER ${GLFW3_CFLAGS_OTHER} ${X11_CFLAGS_OTHER})

list (APPEND DEPS_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/src/include)

set (GstShared_SOURCES
        src/main.cpp
        src/glad.c)

add_executable(GstShared ${GstShared_SOURCES})
target_include_directories(GstShared PRIVATE ${DEPS_INCLUDE_DIRS})
target_link_libraries(GstShared ${DEPS_LIBRARIES})
target_compile_options(GstShared PUBLIC ${DEPS_CFLAGS_OTHER})
