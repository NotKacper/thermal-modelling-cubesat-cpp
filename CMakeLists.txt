cmake_minimum_required(VERSION 3.26)
project(CubeSatCPP)

set(CMAKE_CXX_STANDARD 17)

add_executable(CubeSatCPP
        Classes/ThermalSimulation.cpp
        Classes/ThermalSimulation.h
        Classes/Matrices/ViewFactorMatrix.cpp
        Classes/Matrices/ViewFactorMatrix.h
        Classes/Matrices/HeatFluxMatrix.cpp
        Classes/Matrices/HeatFluxMatrix.h
        Classes/Matrices/TemperatureMatrix.cpp
        Classes/Matrices/TemperatureMatrix.h
        main.cpp)
