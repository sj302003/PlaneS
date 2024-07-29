#include "read.h"
#include "initialize.h"
#include "solve.h"
#include "display.h"
#include <iostream>
#include <vector>

int main() 
{
    Read reader;
    reader.startreading();
    Initialize init;
    init.startInitializing();
    Solve solver1;
    solver1.Solver();
    displayResults(init.BB_results_k2, init.BB_results_k4, init.BB_results_k3, init.BB_results_k1, init.rank);


    return 0;
}
