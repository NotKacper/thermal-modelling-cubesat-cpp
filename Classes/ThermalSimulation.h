//
// Created by sudo on 11/8/23.
//

#ifndef CUBESATCPP_THERMALSIMULATION_H
#define CUBESATCPP_THERMALSIMULATION_H

// all matrices are formatted in the following way: [[NORTH, SOUTH],[V+.V-],[NADIR, ZENITH]]

#include <string>
#include <unordered_map>
#include "Matrices/ViewFactorMatrix.h"
#include "Matrices/HeatFluxMatrix.h"
#include "Matrices/TemperatureMatrix.h"
#include <cmath>

class ThermalSimulation {
private:
    ViewFactorMatrix viewFactors;
    HeatFluxMatrix heatFlux;
    TemperatureMatrix temperatures;
    Matrix areas;
    Matrix absorption;
    Matrix emissivity;
    double deltaTime;
    std::unordered_map<std::string, double> variables;

public:

    explicit ThermalSimulation(std::unordered_map<std::string, double> constants) {
        viewFactors = ViewFactorMatrix();
        heatFlux = HeatFluxMatrix();
        temperatures = TemperatureMatrix();
        areas = Matrix();
        absorption = Matrix();
        emissivity = Matrix();
        for (int i = 0; i < 3; i++) {
            absorption.matrix[i][0] = absorption.matrix[i][1] = constants["absorption"];
            emissivity.matrix[i][0] = emissivity.matrix[i][1] = constants["emissivity"];
            areas.matrix[i][0] = areas.matrix[i][1] = constants["area"];
        }
        deltaTime = constants["deltaTime"];
        constants["criticalBeta"] = asin(constants["radiusEarth"] / (constants["radiusEarth"] + constants["altitude"]));
        constants["albedo"] = constants["time"] = constants["heatFluxIR"] = 0;
        variables = constants;
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

    void update() {
        updateHeatFluxIRAlbedo();
        viewFactors.update(variables);
        heatFlux.update(variables, temperatures, viewFactors, areas, emissivity, absorption);
        temperatures.update(variables, heatFlux, deltaTime);
        variables["time"] += deltaTime;
    }

public:
    std::unordered_map<std::string, double[]> simulate(int iterations) {
        std::unordered_map<std::string, double[]> dataPoints;
        double time[iterations];
        double betaAngle[iterations];
        double temperature[iterations];
        for (int i = 0; i < iterations; i++) {
            update();
            time[i]=variables["time"];
            betaAngle[i] = variables["betaAngle"];
            temperature[i] = temperatures.getAverageTemperature();
        }
        return dataPoints;
    }

};


#endif //CUBESATCPP_THERMALSIMULATION_H
