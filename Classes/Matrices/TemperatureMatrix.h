//
// Created by sudo on 11/8/23.
//

#ifndef CUBESATCPP_TEMPERATUREMATRIX_H
#define CUBESATCPP_TEMPERATUREMATRIX_H


class TemperatureMatrix {
private:
    double matrix[3][2]{};
public:
    TemperatureMatrix() {
        for (auto &i: matrix) {
            i[0] = i[1] = 0;
        }
    }

    void updateTemperature(double mass, double specificHeatCapacity, double heatFlowMatrix[3][2], double deltaTime) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 2; j++) {
                matrix[i][j] += deltaTime * heatFlowMatrix[i][j] / (mass * specificHeatCapacity);
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
