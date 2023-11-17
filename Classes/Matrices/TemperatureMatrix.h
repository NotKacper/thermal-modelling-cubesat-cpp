//
// Created by sudo on 11/8/23.
//

#ifndef CUBESATCPP_TEMPERATUREMATRIX_H
#define CUBESATCPP_TEMPERATUREMATRIX_H


#include "Matrix.h"
#include "HeatFluxMatrix.h"
#include <string>

class TemperatureMatrix : public Matrix {
public:
    void update(std::unordered_map<std::string, double>variables, HeatFluxMatrix heatFluxMatrix, double deltaTime) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 2; j++) {
                matrix[i][j] += deltaTime * heatFluxMatrix.matrix[i][j] / (variables["mass"] * variables["specificHeatCapacity"]);
            }
        }
    }

    double getAverageTemperature() {
        double sum = 0;
        for (auto &i: matrix) {
            for (double j: i) {
                sum += j;
            }
        }
        return sum;
    }
};


#endif //CUBESATCPP_TEMPERATUREMATRIX_H
