//
// Created by sudo on 11/8/23.
//

#ifndef CUBESATCPP_HEATFLUXMATRIX_H
#define CUBESATCPP_HEATFLUXMATRIX_H

#include <string>
#include <unordered_map>
#include <cmath>
#include "TemperatureMatrix.h"

class HeatFluxMatrix {
private:

    static double degreesToRadians(double angleInDegrees) {
        return angleInDegrees * (M_PI / 180);
    }

    static double findHeatFluxNorthSouth(double eclipseFraction, std::unordered_map<std::string, double> variables) {
        if (variables["orbitalPeriod"] * (1 - eclipseFraction) > 2 * variables["time"] &&
            2 * variables["time"] > variables["orbitalPeriod"] * (1 + eclipseFraction)) {
            return sin(variables["betaAngle"]);
        }
        return 0;
    }

    static double
    findHeatFluxPositiveV(double eclipseFraction, std::unordered_map<std::string, double> variables, double cosBeta,
                          double sinValue) {
        if (variables["time"] * 2 > variables["orbitalPeriod"] * (1 + eclipseFraction)) {
            return -sinValue * cosBeta;
        }
        return 0;
    }

    static double
    findHeatFluxNegativeV(double eclipseFraction, std::unordered_map<std::string, double> variables, double cosBeta,
                          double sinValue) {
        if (2 * variables["time"] < (1 - eclipseFraction) * variables["orbitalPeriod"]) {
            return sinValue * cosBeta;
        }
        return 0;
    }

    static double
    findHeatFluxNadir(double eclipseFraction, std::unordered_map<std::string, double> variables, double cosBeta,
                      double cosValue) {
        if ((variables["orbitalPeriod"] < 4 * variables["time"] &&
             4 * variables["time"] < 2 * (1 - eclipseFraction) *
                                     variables["orbitalPeriod"]) ||
            (variables["orbitalPeriod"] * (1 + eclipseFraction) < variables["time"] * 2 &&
             variables["time"] * 2 < M_PI_2 * 3)) {
            return -cosValue * cosBeta;
        }
        return 0;
    }

    static double
    findHeatFluxZenith(std::unordered_map<std::string, double> variables, double cosBeta,
                       double cosValue) {
        if (M_PI_4 > variables["time"] && variables["time"] > M_PI_2 * 3) {
            return cosValue * cosBeta;
        }
        return 0;
    }


public:

    double matrix[3][2]{};

    HeatFluxMatrix() {
        for (auto &i: matrix) {
            i[0] = i[1] = 0;
        }
    }


    void update(std::unordered_map<std::string, double> variables, TemperatureMatrix temperatures) {

    }
};


#endif //CUBESATCPP_HEATFLUXMATRIX_H
