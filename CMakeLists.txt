cmake_minimum_required(VERSION 3.16)

project(pro)

aux_source_directory(. DIR_SRCS)


SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

add_executable(pro ${DIR_SRCS})