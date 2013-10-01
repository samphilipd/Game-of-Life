/*
 *Sam Philip's implementation of:
 *
 *CONWAY'S GAME OF LIFE
 *
 *in c++ for the Stanford CS106B course.
 *
 *--------------------------------------
 *
 *Steps:
 *
 *1) Prompt user for file name
 *2) Use the file contrants to set intial state of bacteria colony
 *3) User input options:
 *'t' for tick advances one frame,
 *'a' animates a user-specified number of frames, one every 100ms.
 *'q' quits the program
 *4) Rules:
 *
 *- Each grid location is either empty or occupied by a single living cell
 *- A location's neighbours are any of the surrounding 8 cells
 *- In the next generation:
 *---> cell with 0 or 1 neighbours will be empty
 *---> cell with 2 neighbours is stable and contents will not change
 *---> cell with 3 neighbours will always contain a cell
 *---> cell with 4 or more neighbours will be empty
 *- All changes take place SIMULATANEOUSLY
 */

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
using namespace std;

int main() {
    setConsoleSize(700, 400);


    // TODO: Finish the program!


    cout << "Have a nice Life!" << endl;
    return 0;
}
