//
// Created by sudo on 11/8/23.
//

#ifndef CUBESATCPP_HEATFLUXMATRIX_H
#define CUBESATCPP_HEATFLUXMATRIX_H

#include <string>
#include <unordered_map>
#include <cmath>
#include "TemperatureMatrix.h"
#include "ViewFactorMatrix.h"

class HeatFluxMatrix : public Matrix {
private:

    static double degreesToRadians(double angleInDegrees) {
        return angleInDegrees * (M_PI / 180);
    }

    static double findHeatFluxGeneral(std::unordered_map<std::string, double> variables, TemperatureMatrix temperatures,
                                      ViewFactorMatrix viewFactors, Matrix Area) {
        if () {
            return 0;
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


public:
    void update(std::unordered_map<std::string, double> variables, TemperatureMatrix temperatures, ViewFactorMatrix viewFactors, Matrix areas, Matrix emissivities, Matrix absorptions) {

    }
};


#endif //CUBESATCPP_HEATFLUXMATRIX_H
