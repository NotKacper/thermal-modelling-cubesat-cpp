//
// Created by sudo on 11/8/23.
//

#ifndef CUBESATCPP_HEATFLUXMATRIX_H
#define CUBESATCPP_HEATFLUXMATRIX_H

#include <string>
#include <unordered_map>
#include <cmath>
#include "Matrix.h"

class HeatFluxMatrix : public Matrix {
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

    static double findHeatFluxGeneral(int row, int column, std::unordered_map<std::string, double> variables,
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
    findHeatFluxNadir(int row, int column, std::unordered_map<std::string, double> variables,
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
    findHeatFluxSouth(int row, int column, std::unordered_map<std::string, double> variables,
                      Matrix temperatures, Matrix areas, Matrix emissivities) {
        double part1 = variables.at("contactConductanceCoefficient") *
                       calculateConductionBetweenSides(row, column, areas, temperatures);
        double part2 = variables["stefanBoltzmann"] * emissivities.matrix[row][column] * areas.matrix[row][column] *
                       pow(temperatures.matrix[row][column], 4);
        return part1 - part2;

    }

    static double
    getInputHeatFlux(int row, int column, std::unordered_map<std::string, double> variables, Matrix areas) {
        double sumAreas = 0;
        for (auto &i: areas.matrix) {
            for (double j: i) {
                sumAreas += j;
            }
        }
        return areas.matrix[row][column] / sumAreas * variables["internalHeatFlux"];
    }

public:
    void update(const std::unordered_map<std::string, double> &variables, Matrix temperatures,
                Matrix viewFactors, Matrix areas, Matrix emissivities, Matrix absorptions) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 2; j++) {
                if (!(i == 0 && j == 1) && !(i == 2 && j == 0)) {
                    matrix[i][j] = findHeatFluxGeneral(i, j, variables, temperatures, viewFactors, areas, emissivities,
                                                       absorptions);
                }
            }
        }
        matrix[0][1] = findHeatFluxSouth(0, 1, variables, temperatures, areas, emissivities);
        matrix[2][0] = findHeatFluxNadir(2, 0, variables, temperatures, viewFactors, areas, emissivities, absorptions);
    }
};


#endif //CUBESATCPP_HEATFLUXMATRIX_H
