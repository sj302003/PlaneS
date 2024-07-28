#include "solve.h"
#include "objectfunc.h"
#include <nlopt.hpp>
#include <iostream>
#include <fstream>
#include <cmath>
#include <omp.h>

Solve::Solve() {}

void Solve::Solver() {
    
    std::vector<double> d;
    for (const auto& vec : d0) {
        d.insert(d.end(), vec.begin(), vec.end());
    }

    nlopt::opt opt(nlopt::LD_SLSQP, d.size());

    Amat_rows = Amat.size();
    Amat_cols = Amat[0].size();

    obj_data.nodecord = nodes;
    obj_data.elemdat = elements;
    obj_data.dispscalefac = 1;
    obj_data.numnode = numnode;
    obj_data.numele = numele;
    obj_data.lnpos = count_dc;

    nn = numnode;
    nl = count_dc;

    const unsigned n = 8 * numnode + count_dc;

    std::vector<std::vector<double>> intmat(n, std::vector<double>(n, 0));
    for (unsigned i = 0; i < n; ++i) {
        for (unsigned j = 0; j < n; ++j) {
            for (unsigned k = 0; k < Amat.size(); ++k) {
                intmat[i][j] += Amat[k][i] * Amat[k][j];
            }
        }
    }

    constraint_data.Amat = Amat;
    constraint_data.Fvec = Fvector;

    const double toler = 1e-14;
    unsigned m = row;
    std::vector<double> tol(m, toler);

    nlopt::opt opt(nlopt::LD_SLSQP, n);
    opt.set_min_objective(myfunc, &obj_data);
    opt.add_equality_mconstraint(myconstraint, &constraint_data, tol);
    opt.set_xtol_rel(toler);
    opt.set_ftol_rel(toler);
    opt.set_ftol_abs(toler / 10000);

    std::vector<double> x(n, 0);
    for (unsigned i = 2 * numnode; i < (8 * numnode + count_dc); ++i) {
        x[i] = 20;
    }

    double minf;
    double start = omp_get_wtime();
    int answer = opt.optimize(x, minf);
    double end = omp_get_wtime();

    std::cout << "Time taken: " << end - start << std::endl;
    if (answer < 0) {
        std::cout << "Optimization did not converge. Exit code: " << answer << std::endl;
    } else {
        std::cout << "Optimization converged\nminf = " << minf << "\nexit flag = " << answer << std::endl;
    }

    ofstream outoptfile;
    outoptfile.open("With_Temp_Matrix_6.csv");
    for (const auto& xi : x) {
        outoptfile << xi << std::endl;
    }
    outoptfile.close();
}
