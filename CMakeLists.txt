cmake_minimum_required(VERSION 3.20)
project(raytracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose build type" FORCE)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -flto -march=native")
set(CMAKE_CXX_FLAGS_DEBUG "-g")

include_directories(inc)

file(GLOB_RECURSE SOURCES
    src/*.cpp
)

add_executable(raytracer ${SOURCES})
target_compile_options(raytracer PRIVATE -Wall -Wextra -Werror)

add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
add_subdirectory(vendored/SDL_image EXCLUDE_FROM_ALL)

target_link_libraries(raytracer PRIVATE SDL3_image::SDL3_image SDL3::SDL3)

target_include_directories(raytracer PRIVATE vendored/SDL/include)

option(ENABLE_SANITIZER "Enable Address Sanitizer" OFF)
option(ENABLE_GPROF "Enable GProf Profiling" OFF)

if(ENABLE_SANITIZER)
    message(STATUS "Enabling AddressSanitizer")
    target_compile_options(raytracer PRIVATE -g -fsanitize=address)
    target_link_options(raytracer PRIVATE -fsanitize=address)
endif()

if(ENABLE_GPROF)
    message(STATUS "Enabling GProf Profiling")
    target_compile_options(raytracer PRIVATE -pg)
    target_link_options(raytracer PRIVATE -pg)
endif()

install(TARGETS raytracer DESTINATION bin)
