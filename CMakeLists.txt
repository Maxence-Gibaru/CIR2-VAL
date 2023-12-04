cmake_minimum_required(VERSION 3.26)
project(CIR2_VAL)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

link_directories(lib)

add_executable(CIR2_VAL main.cpp
        src/Train.cpp
        src/Terminus.cpp
        src/Station.cpp
        src/TrainControlFunction.cpp
        src/TrainGraphics.cpp
        include/TrainGraphics.h
)

#find_package(SFML REQUIRED COMPONENTS graphics window system)
#if(SFML_FOUND)
#    target_link_libraries(CIR2_VAL PRIVATE sfml-graphics sfml-window sfml-system)
#endif()


