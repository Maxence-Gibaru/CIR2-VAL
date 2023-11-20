cmake_minimum_required(VERSION 3.26)
project(CIR2_VAL)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(CIR2_VAL main.cpp
        src/Train.cpp
        src/Terminus.cpp
        src/Station.cpp
        src/TrainControlFunction.cpp
)
