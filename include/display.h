#ifndef DISPLAY_H
#define DISPLAY_H

#include <vector>
#include "constructor.h" 
class Display {
public:
    Display();
    void displayResults(const std::vector<BB>& BB_results_k2, const std::vector<BB>& BB_results_k4, const std::vector<BB>& BB_results_k3, const std::vector<BB>& BB_results_k1, int rank);
    void startdisplay();
};

#endif 
