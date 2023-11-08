cmake_minimum_required(VERSION 3.26)
project(CubeSatCPP)

set(CMAKE_CXX_STANDARD 17)

add_executable(CubeSatCPP main.cpp
        ThermalSimulation.cpp
        ThermalSimulation.h
        ViewFactorMatrix.cpp
        ViewFactorMatrix.h
        HeatFluxMatrix.cpp
        HeatFluxMatrix.h
        TemperatureMatrix.cpp
        TemperatureMatrix.h)
