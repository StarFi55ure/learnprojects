cmake_minimum_required (VERSION 3.5)
project (GstShared)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE TRUE)

find_package(PkgConfig REQUIRED)
find_package(Boost REQUIRED)

pkg_check_modules(GLFW3 REQUIRED glfw3 gl glew)
pkg_check_modules(X11 REQUIRED x11 xrandr xi)
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0 gstreamer-gl-1.0)

set (DEPS_INCLUDE_DIRS ${GLFW3_INCLUDE_DIRS}, ${X11_INCLUDE_DIRS} ${GSTREAMER_INCLUDE_DIRS})
set (DEPS_LIBRARIES ${GLFW3_LIBRARIES} ${X11_LIBRARIES} ${GSTREAMER_LIBRARIES} -ldl -lpthread)
set (DEPS_CFLAGS_OTHER ${GLFW3_CFLAGS_OTHER} ${X11_CFLAGS_OTHER} ${GSTREAMER_CFLAGS_OTHER})

# collect include directories
list (APPEND DEPS_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/src/include)

set (GstShared_SOURCES
        src/main.cpp
        #src/glad.c
        src/Shader.cpp
        src/Shader.h
        src/TextureLoader.cpp
        src/TextureLoader.h
        src/VideoSurface.cpp
        src/VideoSurface.h
        src/glfwrender.cpp
        src/glfwrender.h
        src/GstPlayer.cpp
        src/GstPlayer.h)

add_executable(GstShared ${GstShared_SOURCES})

add_custom_command(OUTPUT copy.out
        DEPENDS GstShared
        COMMAND ${CMAKE_COMMAND} -E touch copy.out
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/shaders ${PROJECT_BINARY_DIR}/shaders
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/images ${PROJECT_BINARY_DIR}/images
        COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/vid.mp4 ${PROJECT_BINARY_DIR}/vid.mp4)

target_include_directories(GstShared PRIVATE ${DEPS_INCLUDE_DIRS})
target_link_libraries(GstShared ${DEPS_LIBRARIES})
target_compile_options(GstShared PUBLIC ${DEPS_CFLAGS_OTHER})

add_custom_target(run ALL
        ${CMAKE_COMMAND} -E echo "copying dependant folders"
        DEPENDS copy.out)
