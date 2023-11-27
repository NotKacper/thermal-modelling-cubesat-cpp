//
// Created by sudo on 11/8/23.
//

#ifndef CUBESATCPP_TEMPERATUREMATRIX_H
#define CUBESATCPP_TEMPERATUREMATRIX_H


#include "Matrix.h"
#include <string>
#include <unordered_map>

class TemperatureMatrix : public Matrix {
public:
    explicit TemperatureMatrix(double initialTemperature) : Matrix() {
        for (auto &i : matrix) {
            i[0]=i[1]=initialTemperature;
        }
    }

    void update(std::unordered_map<std::string, double>variables, Matrix heatFluxMatrix, double deltaTime) {
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
        return sum/6;
    }
};


#endif //CUBESATCPP_TEMPERATUREMATRIX_H
