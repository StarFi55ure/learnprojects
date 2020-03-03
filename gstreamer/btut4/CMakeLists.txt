cmake_minimum_required(VERSION 3.5)
project(btut4)

set(CMAKE_CXX_STANDARD 11)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0 sdl2)

file(GLOB_RECURSE btut4_SOURCES 'src/*.cpp')

add_executable(btut4 ${btut4_SOURCES} src/main.cpp)
target_include_directories(btut4 PRIVATE ${GSTREAMER_INCLUDE_DIRS})
target_link_libraries(btut4 ${GSTREAMER_LIBRARIES})
target_compile_options(btut4 PUBLIC ${GSTREAMER_CFLAGS_OTHER})

