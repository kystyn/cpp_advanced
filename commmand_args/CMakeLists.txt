cmake_minimum_required(VERSION 3.8)

project(commmand_args LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(commmand_args main.cpp CmdArgsMgr.h Variable.h Variable.cpp)
