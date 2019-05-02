cmake_minimum_required(VERSION 3.6)
project(BigInteger)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES biginteger.h)
add_executable(BigInteger ${SOURCE_FILES})
