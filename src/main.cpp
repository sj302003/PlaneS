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
    Constructor constructor;
    constructor.assembleAmat();
    Solve solver1;
    solver1.Solver();
    Display display;
    display.startdisplay();


    return 0;
}
