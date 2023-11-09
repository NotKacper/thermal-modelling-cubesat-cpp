//
// Created by sudo on 11/8/23.
//

#ifndef CUBESATCPP_VIEWFACTORMATRIX_H
#define CUBESATCPP_VIEWFACTORMATRIX_H


class ViewFactorMatrix {
private:
    double matrix[3][2]{};
public:
    ViewFactorMatrix() {
        for (auto & i : matrix) {
            i[0] = i[1] = 0;
        }
    }

};


#endif //CUBESATCPP_VIEWFACTORMATRIX_H
