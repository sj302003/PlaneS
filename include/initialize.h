#ifndef INITIALIZE_H
#define INITIALIZE_H

#include "constraints.h"

#include <vector>
#include <string>

class Initialize {
public:
    Initialize();
    GQVandW getWeightAndValues(int order);
    BB Bsigma_Bd(double *xcoord, double *ycoord, double s, double t);
    vector<BB> get_BB_results_mat(int k, int order, double *xcoord, double *ycoord, vector<double> values);
    bool cmp_for_desc(int x, int y);
    int compute_rank(vector<vector<double>> A);
    RetBC boundry_condition_fun(bc boundry, GQVandW GQdat, int order);
    void startInitializing();
    

private:
    std::string filename;
    //RetBC boundry_condition_fun(bc boundry, GQVandW GQdat, int order);
};

#endif 
