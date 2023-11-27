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
#include "Matrices/DataStorage.h"
#include <cmath>

class ThermalSimulation {
private:
    ViewFactorMatrix viewFactors;
    HeatFluxMatrix heatFlux;
    TemperatureMatrix temperatures = TemperatureMatrix(273.15);
    Matrix areas;
    Matrix absorption;
    Matrix emissivity;
    double deltaTime;
    std::unordered_map<std::string, double> variables;

public:

    explicit ThermalSimulation(std::unordered_map<std::string, double> constants) {
        viewFactors = ViewFactorMatrix();
        heatFlux = HeatFluxMatrix();
        temperatures = TemperatureMatrix(constants["initialTemperature"]);
        areas = Matrix();
        absorption = Matrix();
        emissivity = Matrix();
        for (int i = 0; i < 3; i++) {
            absorption.matrix[i][0] = absorption.matrix[i][1] = constants["absorption"];
            emissivity.matrix[i][0] = emissivity.matrix[i][1] = constants["emissivity"];
        }
        areas.matrix[0][0] = areas.matrix[0][1] = constants["width"] * constants["length"];
        areas.matrix[1][0] = areas.matrix[1][1] = constants["width"] * constants["height"];
        areas.matrix[2][0] = areas.matrix[2][1] = constants["height"] * constants["length"];
        deltaTime = constants["deltaTime"];
        constants["criticalBeta"] = asin(constants["radiusEarth"] / (constants["radiusEarth"] + constants["altitude"]));
        constants["albedo"] = constants["time"] = constants["heatFluxIR"] = 0;
        variables = constants;
    }

private:
    void updateHeatFluxIRAlbedo() {
        if (ViewFactorMatrix::degreesToRadians(variables["betaAngle"]) < M_PI_2 / 6) {
            variables["heatFluxIR"] = 228;
            variables["albedo"] = 0.14;
        } else {
            variables["heatFluxIR"] = 218;
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

    DataStorage simulate(int iterations) {
        DataStorage dataStorage = DataStorage(iterations);
        for (int j = 0; j < 90; j++) {
            variables["betaAngle"]++;
            for (int i = 0; i < iterations; i++) {
                update();
                dataStorage.addTime(variables["time"]);
                dataStorage.addBetaAngle(variables["betaAngle"]);
                dataStorage.addTemperature(temperatures.getAverageTemperature());
            }
        }
        return dataStorage;
    }

};


#endif //CUBESATCPP_THERMALSIMULATION_H
