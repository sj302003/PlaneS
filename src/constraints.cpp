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
 vector<int> sb;
 int sz;
 vector<int> rset;
		// struct ConstraintData {
		// 	vector<vector<double>> BC;
		// 	vector<vector<double>> F;
		// };

// struct ObjectiveData {
//     vector<vector<double>> L;
//     vector<vector<double>> A;
//     vector<vector<double>> parameters;
//     vector<vector<string>> funcname;
//     int nmemb;
// };

/////
 int k;
 double *xcoord; 
 double *ycoord; 
 double s; 
 double t;
 vector<double> Nis(4);
 vector<double> Nit(4);
 vector<double> N(4);
 double matX = 0;
 double matY = 0;

 vector<vector<double>> Jmat;
 vector<double> Jmatrow(2);
 vector<vector<double>> invJ(2, vector<double>(2, 0));
 double detJ;
 vector<vector<double>> Bd;
 vector<double> Bdrow(8);
 vector<vector<double>> Bs;
 vector<double> Bsrow(24);
 vector<vector<double>> Tmat;
 vector<double> Tmatrow(24);
 vector<vector<double>> T1mat;
 vector<double> T1matrow(6);
 vector<vector<double>> Dmat(3, vector<double>(3, 0));
 vector<vector<double>> Bs1mat(3, vector<double>(24, 0));
 vector<vector<double>> Bsmat(3, vector<double>(24, 0));

 int x;
 int y;

 vector<vector<double>> A;
 int n = A.size();
 int m = A[0].size();
 // int rank;
 vector<bool> row_selected(n, false);

 vector<vector<double>> Amat, intmat;
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
 int numele = 0;
 vector<double> Fvector(row);
 vector<BB> BB_results_mat(order);

 int ele = boundry.ele;
 double xcoord[4];
 double ycoord[4];

 BB BBresult;
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
 
 double *grad2 = (double*) malloc((8*nn+nl) * sizeof(double));
 double* grad1 = (double*) malloc(Amat_rows * Amat_cols * sizeof(double));
//  double myfunc(unsigned, const double*, double*, void*);
//  void myconstraint(unsigned, double*, unsigned, const double*, double*, void* );
int Amat_rows = 0;
int Amat_cols = 0;
int nn = 0;
int nl = 0;
// double myconstraint(unsigned, const double*, double*, void* );
 //GQVandW result;
 //GQVandW GQdata = getWeightAndValues(order);
// struct GQVandW {
// 	vector<double> value;
// 	vector<double> weight;
// };

 // vector<BB> BB_results_mat;
 // vector<BB> BB_results_k2 = get_BB_results_mat(2, order, xcoord, ycoord, GQdata.value);
 // vector<BB> BB_results_k4 = get_BB_results_mat(4, order, xcoord, ycoord, GQdata.value);
 // vector<BB> BB_results_k3 = get_BB_results_mat(3, order, xcoord, ycoord, GQdata.value);
 // vector<BB> BB_results_k1 = get_BB_results_mat(1, order, xcoord, ycoord, GQdata.value);

 vector<vector<double>> A; 

 vector<double> knwndisp;
#endif
