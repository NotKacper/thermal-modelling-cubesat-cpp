//
// Created by sudo on 11/8/23.
//

#ifndef CUBESATCPP_THERMALSIMULATION_H
#define CUBESATCPP_THERMALSIMULATION_H


#include <string>
#include <unordered_map>
#include "ViewFactorMatrix.h"
#include "HeatFluxMatrix.h"
#include "TemperatureMatrix.h"
#include <cmath>

class ThermalSimulation {
private:
    ViewFactorMatrix viewFactors;
    HeatFluxMatrix heatFlux;
    TemperatureMatrix temperatures;
    double areas[3];
    double absorption[3][2];
    double emissivity[3][2];
    double deltaTime;
    double mass;
    std::unordered_map<std::string, double> variables;
public:
    ThermalSimulation(std::unordered_map<std::string, double> constants) {
        for (int i = 0; i < 3; i++) {
            absorption[i][0] = absorption[i][1] = constants["absorption"];
            emissivity[i][0] = emissivity[i][1] = constants["emissivity"];
            areas[i] = constants["area"];
        }
        deltaTime = constants["deltaTime"];
        mass = constants["mass"];
        constants["criticalBeta"] = asin(constants["radiusEarth"] / (constants["radiusEarth"] + constants["altitude"]));
        constants["albedo"] = constants["time"] = constants["heatFluxIR"] = 0;
    }

private:
    void updateHeatFluxIRAlbedo() {
        if (variables["betaAngle"] < M_PI_2 / 6) {
            variables["heaFluxIR"] = 228;
            variables["albedo"] = 0.14;
        } else {
            variables["heaFluxIR"] = 218;
            variables["albedo"] = 0.19;
        }
    }

    std::unordered_map<std::string, double[]> update() {

    }

public:
    std::unordered_map<std::string, double[]> simulate(int iterations) {
        std::unordered_map<std::string, double[]> dataPoints;

        for (int i=0; i < iterations; i++) {

        }
    }

};


#endif //CUBESATCPP_THERMALSIMULATION_H
