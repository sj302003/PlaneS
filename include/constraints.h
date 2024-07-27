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
extern vector<vector<double>>  A;
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
extern double TOL;
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
struct BB {
	double x;
	double y;
	// double x = 0;
	// double y = 0;
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
struct GQVandW {
	vector<double> value;
	vector<double> weight;
};
extern vector<double> knwndisp;

#endif