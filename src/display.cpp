#include "initialize.h"
#include "constraints.h"
#include "constructor.h"
#include "display.h"
#include <iostream>
#include <vector>

using namespace std;

extern vector<BB> BB_results_k2;
extern vector<BB> BB_results_k4;
extern vector<BB> BB_results_k3;
extern vector<BB> BB_results_k1;
extern int rank;

Display::Display() {}

void Display::displayResults(const vector<BB>& BB_results_k2, const vector<BB>& BB_results_k4, const vector<BB>& BB_results_k3, const vector<BB>& BB_results_k1, int rank) {
    cout << "Rank of matrix A: " << rank << endl;

    // Output BB results for verification
    cout << "BB Results for k=2:" << endl;
    for (const BB& bb : BB_results_k2) {
        cout << "x: " << bb.x << ", y: " << bb.y << endl;
    }

    cout << "BB Results for k=4:" << endl;
    for (const BB& bb : BB_results_k4) {
        cout << "x: " << bb.x << ", y: " << bb.y << endl;
    }

    cout << "BB Results for k=3:" << endl;
    for (const BB& bb : BB_results_k3) {
        cout << "x: " << bb.x << ", y: " << bb.y << endl;
    }

    cout << "BB Results for k=1:" << endl;
    for (const BB& bb : BB_results_k1) {
        cout << "x: " << bb.x << ", y: " << bb.y << endl;
    }
}

void Display::startdisplay() {
    display.displayResults(BB_results_k2, BB_results_k4, BB_results_k3, BB_results_k1, rank);
}
