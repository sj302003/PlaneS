#include "objectfunc.h"
#include <vector>
#include <cmath>

double constraint_eqn(const std::vector<double> &x, std::vector<double> &grad, void *data1) {
    ConstraintData* consData = static_cast<ConstraintData*>(data1);
    double result = 0.0;

    for (size_t i = 0; i < consData->BC.size(); i++) {
        for (size_t j = 0; j < consData->BC[i].size(); j++) {
            result += consData->BC[i][j] * x[i];
        }
    }
    for (const auto& val : consData->F[0]) {
        result -= val; 
    }

    if (!grad.empty()) {
        for (size_t i = 0; i < consData->BC.size(); i++) {
            for (size_t j = 0; j < consData->BC[i].size(); j++) {
                grad[i] = consData->BC[i][j];
            }
        }
    }

    return result;
}

double objectfunc(const std::vector<double> &d, std::vector<double> &grad, void *data1) {
    ObjectiveData* objData = static_cast<ObjectiveData*>(data1);
    double result = 0.0;

    for (size_t i = 0; i < objData->L.size(); i++) {
        for (size_t j = 0; j < objData->L[i].size(); j++) {
            result += objData->L[i][j] * d[i];
        }
    }

    if (!grad.empty()) {
        for (size_t i = 0; i < objData->L.size(); i++) {
            for (size_t j = 0; j < objData->L[i].size(); j++) {
                grad[i] = objData->L[i][j];
            }
        }
    }

    return result;
}
