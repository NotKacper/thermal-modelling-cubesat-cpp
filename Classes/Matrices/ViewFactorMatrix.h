//
// Created by sudo on 11/8/23.
//

#ifndef CUBESATCPP_VIEWFACTORMATRIX_H
#define CUBESATCPP_VIEWFACTORMATRIX_H


#include <string>
#include <unordered_map>
#include <cmath>

class ViewFactorMatrix {
private:


    static double degreesToRadians(double angleInDegrees) {
        return angleInDegrees * (M_PI / 180);
    }

    static double findEclipseFraction(std::unordered_map<std::string, double> variables, double cosBeta) {
        if (std::abs(variables["betaAngle"]) < variables["criticalBeta"]) {
            return (M_1_PI) *
                   acos(sqrt(pow(variables["altitude"], 2) + 2 * variables["radiusEarth"] * variables["altitude"]) /
                        (variables["radiusEarth"] + variables["altitude"] * cosBeta));
        } else if (std::abs(variables["betaAngle"]) >= variables["criticalBeta"]) {
            return 0;
        }
    }

    static double findViewFactorNorthSouth(double eclipseFraction, std::unordered_map<std::string, double> variables) {
        if (variables["orbitalPeriod"] * (1 - eclipseFraction) > 2 * variables["time"] &&
            2 * variables["time"] > variables["orbitalPeriod"] * (1 + eclipseFraction)) {
            return sin(variables["betaAngle"]);
        }
        return 0;
    }

    static double
    findViewFactorPositiveV(double eclipseFraction, std::unordered_map<std::string, double> variables, double cosBeta,
                            double sinValue) {
        if (variables["time"] * 2 > variables["orbitalPeriod"] * (1 + eclipseFraction)) {
            return -sinValue * cosBeta;
        }
        return 0;
    }

    static double
    findViewFactorNegativeV(double eclipseFraction, std::unordered_map<std::string, double> variables, double cosBeta,
                            double sinValue) {
        if (2 * variables["time"] < (1 - eclipseFraction) * variables["orbitalPeriod"]) {
            return sinValue * cosBeta;
        }
        return 0;
    }

    static double
    findViewFactorNadir(double eclipseFraction, std::unordered_map<std::string, double> variables, double cosBeta,
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
    findViewFactorZenith(std::unordered_map<std::string, double> variables, double cosBeta,
                         double cosValue) {
        if (M_PI_4 > variables["time"] && variables["time"] > M_PI_2 * 3) {
            return cosValue * cosBeta;
        }
        return 0;
    }


public:

    double matrix[3][2]{};

    ViewFactorMatrix() {
        for (auto &i: matrix) {
            i[0] = i[1] = 0;
        }
    }


    void update(std::unordered_map<std::string, double> variables) {
        double cosBeta = cos(degreesToRadians(variables["betaAngle"]));
        double eclipseFraction = findEclipseFraction(variables, cosBeta);
        double sinValue = sin((2 * M_PI) / (variables["orbitalPeriod"]) * variables["time"]);
        double cosValue = cos((2 * M_PI) / (variables["orbitalPeriod"]) * variables["time"]);
        matrix[0][0] = matrix[0][1] = findViewFactorNorthSouth(eclipseFraction, variables);
        matrix[1][0] = findViewFactorPositiveV(eclipseFraction, variables, cosBeta, sinValue);
        matrix[1][1] = findViewFactorNegativeV(eclipseFraction, variables, cosBeta, sinValue);
        matrix[2][0] = findViewFactorNadir(eclipseFraction, variables, cosBeta, cosValue);
        matrix[2][1] = findViewFactorZenith(variables, cosBeta, cosValue);
    }

};


#endif //CUBESATCPP_VIEWFACTORMATRIX_H
