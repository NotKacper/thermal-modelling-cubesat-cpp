//
// Created by sudo on 11/8/23.
//

#ifndef CUBESATCPP_TEMPERATUREMATRIX_H
#define CUBESATCPP_TEMPERATUREMATRIX_H


#include "Matrix.h"
#include "HeatFluxMatrix.h"

class TemperatureMatrix : public Matrix {
public:
    void updateTemperature(double mass, double specificHeatCapacity, HeatFluxMatrix heatFluxMatrix, double deltaTime) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 2; j++) {
                matrix[i][j] += deltaTime * heatFluxMatrix.matrix[i][j] / (mass * specificHeatCapacity);
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
