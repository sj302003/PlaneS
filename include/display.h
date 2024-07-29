#ifndef DISPLAY_H
#define DISPLAY_H

#include "initialize.h"
#include <vector>

void displayResults(const std::vector<BB>& BB_results_k2, const std::vector<BB>& BB_results_k4, const std::vector<BB>& BB_results_k3, const std::vector<BB>& BB_results_k1, int rank);

#endif // DISPLAY_H
