//
// Created by sudo on 11/8/23.
//

#ifndef CUBESATCPP_HEATRATEMATRIX_H
#define CUBESATCPP_HEATRATEMATRIX_H

#include <string>
#include <unordered_map>
#include <cmath>
#include "Matrix.h"

class HeatRateMatrix : public Matrix {
private:

    static double calculateConductionBetweenSides(int row, int column, Matrix areas, Matrix temperatures) {
        double sum = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 2; j++) {
                if (row != i) {
                    sum += areas.matrix[i][j] * (temperatures.matrix[i][j] - temperatures.matrix[row][column]);
                }
            }
        }
        return sum;
    }

    static double findHeatRateGeneral(int row, int column, std::unordered_map<std::string, double> variables,
                                      Matrix temperatures,
                                      Matrix viewFactors, Matrix areas, Matrix emissivities,
                                      Matrix absorptions) {
        double part1 = viewFactors.matrix[row][column] * areas.matrix[row][column] * variables["heatFluxSun"] *
                       absorptions.matrix[row][column];
        double part2 = variables["contactConductanceCoefficient"] *
                       calculateConductionBetweenSides(row, column, areas, temperatures);
        double part3 = variables["stefanBoltzmann"] * emissivities.matrix[row][column] * areas.matrix[row][column] *
                       pow(temperatures.matrix[row][column], 4);
        return part1 + part2 - part3;
    }


    static double
    findHeatRateNadir(int row, int column, std::unordered_map<std::string, double> variables,
                      Matrix temperatures,
                      Matrix viewFactors, Matrix areas, Matrix emissivities,
                      Matrix absorptions) {
        double part1 = (viewFactors.matrix[row][column] + variables["albedo"]) * areas.matrix[row][column] *
                       variables["heatFluxSun"] *
                       absorptions.matrix[row][column];
        double part2 = variables["contactConductanceCoefficient"] *
                       calculateConductionBetweenSides(row, column, areas, temperatures);
        double part3 = variables["heatFluxIR"] * areas.matrix[row][column];
        double part4 = variables["stefanBoltzmann"] * emissivities.matrix[row][column] * areas.matrix[row][column] *
                       pow(temperatures.matrix[row][column], 4);
        return part1 + part2 + part3 - part4;
    }

    static double
    findHeatRateSouth(int row, int column, std::unordered_map<std::string, double> variables,
                      Matrix temperatures, Matrix areas, Matrix emissivities) {
        double part1 = variables["contactConductanceCoefficient"] *
                       calculateConductionBetweenSides(row, column, areas, temperatures);
        double part2 = variables["stefanBoltzmann"] * emissivities.matrix[row][column] * areas.matrix[row][column] *
                       pow(temperatures.matrix[row][column], 4);
        return part1 - part2;

    }

    static double
    getInputHeatRate(int row, int column, std::unordered_map<std::string, double> variables, Matrix areas) {
        double positionOfSource[3] = {variables["x_0"], variables["height"] / 2, variables["width"] / 2};
        double distances[3][2] = {
                {variables["height"] - positionOfSource[1], positionOfSource[1]},
                {positionOfSource[0],                       variables["length"] - positionOfSource[0]},
                {positionOfSource[2],                       variables["width"] - positionOfSource[2]}
        };
        double distance = distances[row][column];
        double heatRateAtSide =
                variables["internalHeatRate"] * M_1_PI * 0.25 * 1 / (pow(distance, 2)) * areas.matrix[row][column];
        return heatRateAtSide;
    }

public:
    void update(const std::unordered_map<std::string, double> &variables, Matrix temperatures,
                Matrix viewFactors, Matrix areas, Matrix emissivities, Matrix absorptions) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 2; j++) {
                if (!(i == 0 && j == 1) && !(i == 2 && j == 0)) {
                    matrix[i][j] = findHeatRateGeneral(i, j, variables, temperatures, viewFactors, areas, emissivities,
                                                       absorptions);
                    matrix[i][j] += getInputHeatRate(i, j, variables, areas);
                }
            }
        }
        matrix[0][1] = findHeatRateSouth(0, 1, variables, temperatures, areas, emissivities) +
                       getInputHeatRate(0, 1, variables, areas);
        matrix[2][0] = findHeatRateNadir(2, 0, variables, temperatures, viewFactors, areas, emissivities, absorptions) +
                       getInputHeatRate(2, 0, variables, areas);
    }
};


#endif //CUBESATCPP_HEATRATEMATRIX_H
