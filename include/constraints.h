#ifndef CONSTRAINTS_H
#define CONSTRAINTS_H

#include<iostream>
#include<vector>
#include<map>

#include "element.h"

using namespace std;

extern vector<Oceane::Nodeptr> m_nodes;
extern vector<Oceane::Elementptr> m_elements;
extern vector<Oceane::Nodeptr> m_boundaryElements;
extern vector<vector<double>> m_loads;
extern vector<vector<double>> m_fixity;
extern vector<vector<double>> L;
// extern vector<vector<double>>  A;
extern vector<vector<double>> F;
extern vector<vector<double>> Breq;
extern vector<vector<double>> BC;
extern vector<vector<double>> S;
extern vector<vector<double>> deltasupp;
extern vector<vector<double>> parameters;
extern vector<vector<string>> funcname;
extern int nnode;
extern int nmemb;
extern double Fm;
extern double avgforce;
extern vector<int> nodenum;
extern vector<int> xyz;
extern int ns;
extern vector<vector<double>> Br;
extern vector<int> qs;
extern vector<int> nodepos,reactpos;
extern vector<vector<double>> f,deltacheck;
extern double multiplier;
extern vector<double> d,Fr;
extern vector<vector<double>> d0;
extern double fval;
extern vector<int> sb;
extern int sz;
extern vector<int> rset;
struct ConstraintData {
    vector<vector<double>> BC;
    vector<vector<double>> F;
};

struct ObjectiveData {
    vector<vector<double>> L;
    vector<vector<double>> A;
    vector<vector<double>> parameters;
    vector<vector<string>> funcname;
    int nmemb;
};

/////
extern int k;
extern double *xcoord; 
extern double *ycoord; 
extern double s; 
extern double t;
extern vector<double> Nis(4);
extern vector<double> Nit(4);
extern vector<double> N(4);
extern double matX ;
extern double matY ;

extern vector<vector<double>> Jmat;
extern vector<double> Jmatrow(2);
extern vector<vector<double>> invJ(2, vector<double>(2, 0));
extern double detJ;
extern vector<vector<double>> Bd;
extern vector<double> Bdrow(8);
extern vector<vector<double>> Bs;
extern vector<double> Bsrow(24);
extern vector<vector<double>> Tmat;
extern vector<double> Tmatrow(24);
extern vector<vector<double>> T1mat;
extern vector<double> T1matrow(6);
extern vector<vector<double>> Dmat(3, vector<double>(3, 0));
extern vector<vector<double>> Bs1mat(3, vector<double>(24, 0));
extern vector<vector<double>> Bsmat(3, vector<double>(24, 0));

extern int x;
extern int y;

extern int n;
extern int m;
extern int rank;
extern vector<bool> row_selected(n, false);

extern vector<vector<double>> Amat, intmat;
extern int colm;
extern int row;
extern int count_dc;
extern int thereflg;	
extern double tempmatpar;
extern vector<int> rest_dispdof;
extern int dof, numnode;
extern double obj_exec_time;
extern int order;
extern double TOL ;
extern vector<double> weights;
extern vector<double> values;
extern double *grad2;
extern double* grad1;
extern int Amat_rows;
extern int Amat_cols;
extern int nn;
extern int nl;
extern int numele;
extern vector<double> Fvector(row);
extern vector<BB> BB_results_mat(order);

extern int ele;
extern double xcoord[4];
extern double ycoord[4];

extern BB BBresult;
struct BB {
	double x;
	double y;
	double detJ;
	vector<vector<double> > Jmat;
	vector<vector<double> > Bd;
	vector<vector<double> > Bsmat;
};

struct RetBC {
	vector<vector<double>> Kmat;
	vector<vector<double>> Fmat;
};

struct node {
	int id;
	double x_cord;
	double y_cord;
};

typedef struct boundry_condition {
	int node1, node2, ele, dc_x1, dc_x2, dc_y1, dc_y2;
	double tractvec[4]; 
	double dispvec[4];
}bc;

struct element {
	int node1, node2, node3, node4, ele, mattype, nummatpar;
	vector<double> matpar;
};

extern vector<bc> bc_arr;
extern vector<node> nodes;
extern vector<element> elements;

struct constdata {
	vector<vector<double>> Amat, intmat;
	vector<double> Fvec;
	int rows;
};
struct objdata {
	vector<element> elemdat;
	vector<node> nodecord;
	double dispscalefac;
	int numnode;
	int numele;
	int lnpos;
};

extern constdata constraint_data;
extern objdata obj_data;

struct Errret {
	double errv;
	vector<double> grdval;
};

struct Cnstrelret {
	vector<double> delval;
	vector<vector<double>> dfdstrain;
	vector<vector<double>> dfdstress;
};

extern double myfunc(unsigned, const double*, double*, void*);
extern void myconstraint(unsigned, double*, unsigned, const double*, double*, void* );
// double myconstraint(unsigned, const double*, double*, void* );
extern GQVandW result;
extern GQVandW GQdata = getWeightAndValues(order);
struct GQVandW {
	vector<double> value;
	vector<double> weight;
};

extern vector<BB> BB_results_mat;
extern vector<BB> BB_results_k2;
extern vector<BB> BB_results_k4;
extern vector<BB> BB_results_k3;
extern vector<BB> BB_results_k1;


extern vector<double> knwndisp;
#endif
