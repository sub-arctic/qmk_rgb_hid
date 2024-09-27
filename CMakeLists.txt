cmake_minimum_required(VERSION 3.10)

project(qmk_hid_rgb VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(send_rgb
    src/main.cpp
    src/color_utils.cpp
    src/hid_utils.cpp
)

find_library(HIDAPI_LIB hidapi-hidraw)

if (HIDAPI_LIB)
    message(STATUS "Found HIDAPI library (hidraw): ${HIDAPI_LIB}")
    target_link_libraries(send_rgb PRIVATE ${HIDAPI_LIB})
else()
    message(FATAL_ERROR "hidapi-hidraw library not found. Please install it.")
endif()
