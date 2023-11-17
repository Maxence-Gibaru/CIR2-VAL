cmake_minimum_required(VERSION 3.26)
project(CIR2_VAL)

set(CMAKE_CXX_STANDARD 20)

add_executable(CIR2_VAL main.cpp
        src/Train.cpp
        include/Train.h
        src/Terminus.cpp
        include/Terminus.h
        include/Station.h
        src/Station.cpp
        src/TrainControlFunction.cpp
        include/TrainControlFunction.h
)
