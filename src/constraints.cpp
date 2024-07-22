#include "constraints.h"

#include<iostream>
#include<vector>

vector<Oceane::Nodeptr> m_nodes;
vector<Oceane::Elementptr> m_elements;
vector<Oceane::Nodeptr> m_boundaryElements;
vector<vector<double>> m_loads;
vector<vector<double>> m_fixity;
vector<vector<double>> L;
vector<vector<double>>  A;
vector<vector<double>> F;
vector<vector<double>> Breq;
vector<vector<double>> BC;
vector<vector<double>> S;
vector<vector<double>> deltasupp;
vector<vector<double>> parameters;
vector<vector<string>> funcname;
int nnode;
int nmemb;
double Fm;
double avgforce;
vector<int> nodenum;
vector<int> xyz;
int ns;
vector<vector<double>> Br;
vector<int> qs;
vector<int> nodepos,reactpos;
vector<vector<double>> f,deltacheck;
double multiplier;
vector<double> d,Fr;
vector<vector<double>> d0;
double fval;
vector<int> sb(2);
int sz;
// struct ConstraintData {
//     vector<vector<double>> BC;
//     vector<vector<double>> F;
// };

// struct ObjectiveData {
//     vector<vector<double>> L;
//     vector<vector<double>> A;
//     vector<vector<double>> parameters;
//     vector<vector<string>> funcname;
//     int nmemb;
// };

int colm;
int row;
int count_dc = 0;
int thereflg;
double tempmatpar;
vector<int> rest_dispdof;
int dof, numnode=0;
double obj_exec_time = 0;
int order;
double TOL = 1e-10;
vector<double> weights;
vector<double> values;
// struct BB {
// 	double x = 0;
// 	double y = 0;
// 	double detJ;
// 	vector<vector<double> > Jmat;
// 	vector<vector<double> > Bd;
// 	vector<vector<double> > Bsmat;
// };

// struct RetBC {
// 	vector<vector<double>> Kmat;
// 	vector<vector<double>> Fmat;
// };

// struct node {
// 	int id;
// 	double x_cord;
// 	double y_cord;
// };

// typedef struct boundry_condition {
// 	int node1, node2, ele, dc_x1, dc_x2, dc_y1, dc_y2;
// 	double tractvec[4]; 
// 	double dispvec[4];
// }bc;

// struct element {
// 	int node1, node2, node3, node4, ele, mattype, nummatpar;
// 	vector<double> matpar;
// };

vector<bc> bc_arr;
vector<node> nodes;
vector<element> elements;

// struct constdata {
// 	vector<vector<double>> Amat, intmat;
// 	vector<double> Fvec;
// 	int rows;
// };
// struct objdata {
// 	vector<element> elemdat;
// 	vector<node> nodecord;
// 	double dispscalefac;
// 	int numnode;
// 	int numele;
// 	int lnpos;
// };

constdata constraint_data;
objdata obj_data;

// struct Errret {
// 	double errv;
// 	vector<double> grdval;
// };

// struct Cnstrelret {
// 	vector<double> delval;
// 	vector<vector<double>> dfdstrain;
// 	vector<vector<double>> dfdstress;
// };


double myfunc(unsigned, const double*, double*, void*);
void myconstraint(unsigned, double*, unsigned, const double*, double*, void* );
// double myconstraint(unsigned, const double*, double*, void* );
// struct GQVandW {
// 	vector<double> value;
// 	vector<double> weight;
// };
vector<double> knwndisp;