#include <fstream>
#include <iostream>
#include "Classes/ThermalSimulation.h"
#include "dist\json\json.h"
#include "dist\jsoncpp.cpp"

//
// Created by sudo on 11/8/23.
//


int main() {
    Json::Value people;
    std::ifstream people_file("constants.json", std::ifstream::binary);
    people_file >> people;
    return 0;
};