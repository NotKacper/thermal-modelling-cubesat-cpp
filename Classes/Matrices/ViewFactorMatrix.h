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
    double matrix[3][2]{};

    static double degreesToRadians(double angleInDegrees) {
        return angleInDegrees*(M_PI/180);
    }

    static double findEclipseFraction(std::unordered_map<std::string, double> variables, double cosBeta) {
        if (std::abs(variables["betaAngle"]) < variables["criticalBeta"] ) {
            return (1/M_PI) * acos(sqrt(pow(variables["altitude"], 2)+2*variables["radiusEarth"]*variables["altitude"])/(variables["radiusEarth"]+variables["altitude"]*cosBeta));
        }
        else if (std::abs(variables["betaAngle"])>=variables["criticalBeta"]) {
            return 0;
        }
    }

    double findViewFactorNorthSouth(double eclipseFraction, std::unordered_map<std::string, double> variables) {
        if (variables["orbital"])
    }

public:
    ViewFactorMatrix() {
        for (auto & i : matrix) {
            i[0] = i[1] = 0;
        }
    }

    void update(std::unordered_map<std::string, double> variables) {
        double cosBeta = cos(degreesToRadians(variables["betaAngle"]));
        double eclipseFraction = findEclipseFraction(variables, cosBeta);
        double sinValue = sin((2*M_PI)/(variables["orbitalPeriod"]) * variables["time"]);
        double cosValue = cos((2*M_PI)/(variables["orbitalPeriod"]) * variables["time"]);
        matrix[0][0] = matrix[0][1] = findViewFactorNorthSouth(eclipseFraction, variables);
    }

};


#endif //CUBESATCPP_VIEWFACTORMATRIX_H
