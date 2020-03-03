cmake_minimum_required(VERSION 3.12)
project(btut3)

set(CMAKE_CXX_STANDARD 11)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)

file(GLOB_RECURSE btut3_SOURCES 'src/*.cpp')

add_executable(btut3 ${btut3_SOURCES} src/main.cpp)
target_include_directories(btut3 PRIVATE ${GSTREAMER_INCLUDE_DIRS})
target_link_libraries(btut3 ${GSTREAMER_LIBRARIES})
target_compile_options(btut3 PUBLIC ${GSTREAMER_CFLAGS_OTHER})

