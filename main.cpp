#include <fstream>
#include <iostream>
#include "Classes/ThermalSimulation.h"
#include "dist\json\json.h"
#include "dist\jsoncpp.cpp"
#include <string>
#include <unordered_map>

//
// Created by sudo on 11/8/23.
//


int main() {
    std::unordered_map<std::string, double> constants;
    constants["heatFluxSun"] = 1414;
    constants["contactConductanceCoefficient"]=400;
    constants["radiusEarth"]=6371;
    constants["altitude"] = 500;
    constants["deltaTime"]=100;
    constants["orbitalPeriod"]=86400;
    constants["specificHeatCapacity"]=900;
    constants["mass"]=12;
    constants["width"]=0.2;
    constants["length"]=0.2;
    constants["height"]=0.1;
    constants["initialTemperature"]=273.15;
    constants["internalHeatFlux"]=15;
    constants["absorption"]=0.95;
    constants["emissivity"]=0.85;
    constants["stefanBoltzmann"]=5.670374419e-8;
    constants["betaAngle"]=90;
    constants["time"]=0;
    ThermalSimulation thermalSimulation = ThermalSimulation(constants);
    thermalSimulation.simulate(100);
    return 0;
};