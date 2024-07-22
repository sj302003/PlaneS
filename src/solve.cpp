#include "solve.h"
#include "objectfunc.h"
#include <nlopt.hpp>
#include <iostream>
#include <cmath>

Solve::Solve() {}

void Solve::Solver() {
    
    std::vector<double> d;
    for (const auto& vec : d0) {
        d.insert(d.end(), vec.begin(), vec.end());
    }

    nlopt::opt opt(nlopt::LD_SLSQP, d.size());

    // Define the objective function data
    ObjectiveData objData;
    objData.L = L;
    objData.A = A;
    objData.parameters = parameters;
    objData.nmemb = nmemb;
    objData.funcname = funcname;

    opt.set_min_objective(objectfunc, &objData);

    // Define the constraint function data
    ConstraintData consData;
    consData.BC = BC;
    consData.F = F;

    opt.add_equality_constraint(constraint_eqn, &consData, 1e-8);

    opt.set_xtol_rel(1e-10);
    opt.set_maxeval(2000);

    double fval;

    nlopt::result res = opt.optimize(d, fval);

    std::cout << "Optimization result: " << res << std::endl;
    std::cout << "Objective function value: " << fval << std::endl;

    for (size_t i = nmemb + 2 * nnode - ns; i < d.size(); i++) {
        Fr.push_back(d[i]);
    }
    int sz = Fr.size();
    std::cout << nmemb << " " << nnode << " " << ns << std::endl;

    std::cout << "Member Forces" << std::endl;
    for (int i = 0; i < nmemb; i++) {
        std::cout << "F" << m_elements[i]->getIndex() << " = " << round(d[i] * 1e6) / 1e6 << std::endl;
    }

    std::vector<int> xyzs, nodenumber;
    for (size_t i = 0; i < BC.size(); i++) {
        for (int j = 1; j < 3; j++) {
            if (BC[i][j] == 1) {
                xyzs.push_back(i);
                nodenumber.push_back(j);
            }
        }
    }

    int k = 0;
    std::string c;
    std::cout << "______________________________________________" << std::endl;
    std::cout << "Node Displacements" << std::endl;
    for (int i = nmemb; i < nmemb + sb[0]; i++) {
        if (nodenumber[k] == 0) {
            c = 'x';
        } else {
            c = 'y';
        }
        std::cout << 'u' << c << xyzs[k] + 1 << " = " << d[i] / multiplier << std::endl;
        k += 1;
    }

    k = 0;
    std::cout << "______________________________________________" << std::endl;
    std::cout << "Support Reactions" << std::endl;
    for (int i = 0; i < sz; i++) {
        if (nodenumber[i] == 0) {
            c = 'x';
        } else {
            c = 'y';
        }

        double reaction = round(Fr[i] * 1e6) / 1e6;
        std::cout << 'F' << c << xyzs[i] + 1 << " = " << reaction << std::endl;
    }
}
