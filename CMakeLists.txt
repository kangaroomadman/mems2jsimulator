cmake_minimum_required(VERSION 2.8)
project(mems2jsimulator)

# Set directory variables
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(FTDI_DIR ${CMAKE_SOURCE_DIR}/ftdi)

# Set some compile options
add_compile_options(-std=c++11 -Wall -Werror -pedantic)

# Add application
include_directories(${SOURCE_DIR} ${FTDI_DIR})
add_executable(mems2jsimulator
               ${SOURCE_DIR}/mems2jsimulator.cpp
               ${SOURCE_DIR}/Log.cpp
               ${SOURCE_DIR}/HexValue.cpp
               ${SOURCE_DIR}/Serial.cpp
               ${SOURCE_DIR}/CommandHandler.cpp
               ${SOURCE_DIR}/CommandLineParser.cpp)
target_link_libraries(mems2jsimulator ${FTDI_DIR}/ftd2xx.lib)

# Statically link gcc
set(CMAKE_SHARED_LINKER_FLAGS "-static-libgcc")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc")
