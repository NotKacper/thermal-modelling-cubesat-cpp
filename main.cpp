#include <fstream>
#include <iostream>
#include <chrono>
#include "Classes/ThermalSimulation.h"
#include <string>
#include <unordered_map>

//
// Created by sudo on 11/8/23.
//


int main() {
    auto start = std::chrono::steady_clock::now();
    std::unordered_map<std::string, double> constants;
    constants["heatFluxSun"] = 1414;
    constants["contactConductanceCoefficient"] = 400;
    constants["radiusEarth"] = 6371;
    constants["altitude"] = 400;
    constants["deltaTime"] = 1; // in 10^3 seconds
    constants["orbitalPeriod"] = 7.2; // in 10^3 seconds
    constants["specificHeatCapacity"] = 900;
    constants["mass"] = 12;
    constants["width"] = 0.2;
    constants["length"] = 0.3405;
    constants["height"] = 0.1;
    constants["x_0"] = 0.01;
    double t;
    std::cin >> t;
    constants["initialTemperature"] = 273.15;
    constants["internalHeatRate"] = t;
    constants["absorption"] = 0.95;
    constants["emissivity"] = 0.8;
    constants["stefanBoltzmann"] = 5.670374419e-8;
    constants["betaAngle"] = 0;
    constants["time"] = 0;
    ThermalSimulation thermalSimulation = ThermalSimulation(constants);
    DataStorage dataStorage = thermalSimulation.simulate(200000);
    std::ofstream myFile;
    myFile.open("output"+std::to_string(t)+".csv");
    myFile << "time, betaAngle, temperature\n";
    for (int i = 0; i < dataStorage.dataPoints; i++) {
        myFile << dataStorage.getNextLine();
    }
    myFile.close();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start);
    std::cout << "milliseconds since start: " << elapsed.count() << "ms \n";
    return 0;
}