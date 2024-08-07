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
 std::vector<int> rset;
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
//  double *xcoord; 
//  double *ycoord; 
 double s; 
 double t;
 double matX = 0;
 double matY = 0;

int nn = 0;
int nl = 0;
const double EPS = 1E-13;



 vector<vector<double>> Jmat;
 double detJ;
 vector<vector<double>> Bd;
 vector<vector<double>> Bs;
 vector<vector<double>> Tmat;
 vector<vector<double>> T1mat;
 
 vector<vector<double>> Bsmat;

 int x;
 int y;
 int n;
 int m;
 int rankk;

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
 //const double EPS = 1E-13;

 int ele;
 double xcoord[4];
 double ycoord[4];
 Errret ErrAGrad;
	int u_pos[8];
	int phi_pos[24];
	vector<double> gradval;
	double u_val[8];
	double phi_val[24];
	int elenodes[4];
	int numpar;
	int GQorder = 10;
	double errval=0;
	double ScaleFac = 1e3;
	vector<vector<double>> Cmat;
	vector<vector<double>> Emat;
	vector<double> delvalue;
	vector<double> tempmat(3);
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

int bndsdes = 0 ;

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
 
 double* grad2 = (double*) malloc((8*nn+nl) * sizeof(double));
 double* grad1 = (double*) malloc(Amat_rows * Amat_cols * sizeof(double));
//  double myfunc(unsigned, const double*, double*, void*);
//  void myconstraint(unsigned, double*, unsigned, const double*, double*, void* );
int Amat_rows = 0;
int Amat_cols = 0;
//int nn = 0;
//int nl = 0;
// double myconstraint(unsigned, const double*, double*, void* );
 GQVandW result;
 GQVandW GQdata;
// struct GQVandW {
// 	vector<double> value;
// 	vector<double> weight;
// };

 //vector<BB> BB_results_mat;
 vector<BB> BB_results_k2;
 vector<BB> BB_results_k4;
 vector<BB> BB_results_k3;
 vector<BB> BB_results_k1;
 vector<double> knwndisp;
