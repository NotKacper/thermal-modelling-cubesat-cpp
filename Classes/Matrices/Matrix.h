//
// Created by sudo on 11/14/23.
//

#ifndef CUBESATCPP_MATRIX_H
#define CUBESATCPP_MATRIX_H


class Matrix {
public:
    double matrix[3][2]{};

    Matrix() {
        for (auto &i: matrix) {
            i[0] = i[1] = 0;
        }
    }
};


#endif //CUBESATCPP_MATRIX_H
