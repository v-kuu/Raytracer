cmake_minimum_required(VERSION 3.20)
project(raytracer LANGUAGES CXX)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose build type" FORCE)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -flto -march=native")
set(CMAKE_CXX_FLAGS_DEBUG "-g")

include_directories(inc)

include(FetchContent)

FetchContent_Declare(SDL3
	GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
	GIT_TAG release-3.2.26
	GIT_SHALLOW ON
)

FetchContent_Declare(SDL3_image
	GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
	GIT_TAG release-3.2.4
	GIT_SHALLOW ON
)

FetchContent_MakeAvailable(SDL3 SDL3_image)

file(GLOB_RECURSE SOURCES
    src/*.cpp
)

add_executable(raytracer ${SOURCES})

target_link_libraries(raytracer PRIVATE SDL3_image::SDL3_image SDL3::SDL3)

option(ENABLE_SANITIZER "Enable Address Sanitizer" OFF)
option(ENABLE_GPROF "Enable GProf Profiling" OFF)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
	target_compile_options(raytracer PRIVATE -Wall -Wextra -Werror)
elseif (CMAKE_CXX_COMPILER_ID STREQUEL "MSVC")
	target_compile_options(raytracer PRIVATE /W4)
endif()

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
