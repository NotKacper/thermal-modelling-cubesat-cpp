//
// Created by sudo on 11/27/23.
//

#ifndef CUBESATCPP_DATASTORAGE_H
#define CUBESATCPP_DATASTORAGE_H
#include <list>
#include <string>


class DataStorage {
public:
    std::list<double> time;
    std::list<double> betaAngle;
    std::list<double> temperature;
    int dataPoints;

    DataStorage(int iterations) {
        dataPoints = iterations;
        time = {};
        betaAngle = {};
        temperature = {};
    }

    void addTime(double newTime) {
        time.push_back(newTime);
    }

    void addBetaAngle(double newBetaAngle) {
        betaAngle.push_back(newBetaAngle);
    }

    void addTemperature(double newTemperature) {
        temperature.push_back(newTemperature);
    }

    std::string getNextLine() {
        std::string line = std::to_string(time.front())+","+std::to_string(betaAngle.front())+","+std::to_string(temperature.front())+"\n";
        time.pop_front();
        temperature.pop_front();
        betaAngle.pop_front();
        return line;
    }
};


#endif //CUBESATCPP_DATASTORAGE_H
