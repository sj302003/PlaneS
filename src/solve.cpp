#include "solve.h"
#include "constraints.h"
#include "objectfunc.h"
#include <nlopt.hpp>
#include <iostream>
#include <fstream>
#include <cmath>
#include <omp.h>

Solve::Solve() {}

void Solve::Solver()
{

	std::vector<double> d;
	for (const auto &vec : d0)
	{
		d.insert(d.end(), vec.begin(), vec.end());
	}

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
	for (unsigned i = 0; i < n; ++i)
	{
		for (unsigned j = 0; j < n; ++j)
		{
			for (unsigned k = 0; k < Amat.size(); ++k)
			{
				intmat[i][j] += Amat[k][i] * Amat[k][j];
			}
		}
	}

	constraint_data.Amat = Amat;
	constraint_data.Fvec = Fvector;
	constraint_data.rows = row;
	constraint_data.intmat = intmat;
	const double toler = 1e-14;
	unsigned m = row;

	double *tol = new double[m];
	for (int i = 0; i < m; i++)
	{
		tol[i] = toler;
	}
	nlopt_opt opt;
	opt = nlopt_create(NLOPT_LD_SLSQP, n);
	nlopt_set_min_objective(opt, myfunc, &obj_data);
	nlopt_add_equality_mconstraint(opt, m, myconstraint, &constraint_data, tol);
	nlopt_set_xtol_rel(opt, toler);
	nlopt_set_ftol_rel(opt, toler);
	nlopt_set_ftol_abs(opt, toler / 10000);

	double x[n];
	for (int i = 0; i < 2 * numnode; i++)
	{
		x[i] = 1;
	}
	for (int i = 2 * numnode; i < (8 * numnode + count_dc); i++)
	{
		x[i] = 20;
	}

	double minf;
	double *xreq;
	xreq = x;
	double start = omp_get_wtime();
	int answer = nlopt_optimize(opt, xreq, &minf);
	double end = omp_get_wtime();

	cout << "Time taken : " << end - start << endl;
	if (answer < 0)
	{
		cout << "Optimization did not converge. Exit code: " << answer << endl;
	}
	else
	{
		cout << "Optimization converged" << endl
				 << "minf = " << minf << "exit flag = " << answer << endl;
	}
	cout << "Overall time taken by objective function : " << obj_exec_time << endl;
	ofstream outoptfile;
	outoptfile.open("With_Temp_Matrix_6.csv");
	for (int i = 0; i < (8 * numnode + count_dc); i++)
	{
		outoptfile << x[i] << endl;
	}
	outoptfile.close();
	nlopt_destroy(opt);
}
