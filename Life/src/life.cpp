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
 *- All changes take place SIMULTANEOUSLY
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

/* Function prototypes */

void printWelcomeMessage();
void parseGridFile(Grid<bool> &currentGrid, string gridFileName);
void printGrid(Grid<bool> &currentGrid);
void advanceGeneration(Grid<bool> &currentGrid);

/* Constants */

const char LIVE_CELL = 'X';
const char DEAD_CELL = '-';

/* Main Program */

int main() {
    setConsoleSize(700, 400);
    printWelcomeMessage();

    // initialise boolean Grid, 1 is a living cell, 0 is a dead cell
    Grid<bool> currentGrid;

    // grab input file from user
    string gridFileName = getLine("Grid input file name? ");

    parseGridFile(currentGrid, gridFileName);
    printGrid(currentGrid);
    advanceGeneration(currentGrid);

    cout << "Have a nice Life!" << endl;
    return 0;
}

/*
 *Function printWelcomeMessage();
 *-------------------------------
 *Prints a short message explaing the application and its rules to
 *the user
 */
void printWelcomeMessage() {
    cout << "Welcome to Sam's implementation of the CS106B Game of Life,"
         << endl << "a simulation of the lifecycle of a bacteria colony."
         << endl << "Cells (X) live and die by the following rules:"
         << endl << "- A cell with 1 or fewer neighbours dies."
         << endl << "- Locations with 2 neighbours remain stable."
         << endl << "- Locations with 3 neighbours will create life"
         << endl << "- A cell with 4 or more neighbours dies." << endl
         << endl;

}

/*
 *Function parseGridFile();
 *------------------------------
 *Takes an input filename for a life grid data file and parses it to
 *the specified Grid
 *
 *@param &currentGrid - reference to main currentGrid
 *@param gridFileName - the location of the grid file as a string
 */
void parseGridFile(Grid<bool> &currentGrid, string gridFileName) {
    ifstream input;
    input.open(gridFileName.c_str());
    string line;

    // (re)size grid to match input file
    getline(input, line);
    int rows = atoi(line.c_str());
    getline(input, line);
    int columns = atoi(line.c_str());
    currentGrid.resize(rows, columns);

    //DEBUG
    cerr << "rows = " << rows << endl;
    cerr << "cols = " << columns << endl;

    // populate grid with file content
    for (int i = 0; i < rows; i++) {
        getline(input, line);
        for (int j = 0; j < line.length(); j++) {
            if (line[j] == DEAD_CELL) {
                currentGrid[i][j] = false;
            } else if (line[j] == LIVE_CELL) {
                currentGrid[i][j] = true;
            }
        }
    }
    input.close();
}

/*
 *Function printGrid();
 *---------------------
 *Outputs contents of specified grid to console
 */
void printGrid(Grid<bool> &currentGrid) {
    for (int i = 0; i < currentGrid.numRows(); i++) {
        for (int j = 0; j < currentGrid.numCols(); j++) {
            if (currentGrid[i][j]) {
                cout << LIVE_CELL;
            } else {
                cout << DEAD_CELL;
            }
        }
        cout << endl;
    }
}

/*
 *Function advanceGeneration();
 *-----------------------------
 *Advances current grid one step to the next generation
 *
 *Quick rule reminder:
 *- A location's neighbours are any of the surrounding 8 cells
 *- In the next generation:
 *---> cell with 0 or 1 neighbours will be empty
 *---> cell with 2 neighbours is stable and contents will not change
 *---> cell with 3 neighbours will always contain a cell
 *---> cell with 4 or more neighbours will be empty
 *- All changes take place SIMULTANEOUSLY
 */

void advanceGeneration(Grid<bool> &currentGrid) {
    // create temporary duplicate grid to hold next step
    Grid<bool> nextGrid(currentGrid.numRows(), currentGrid.numCols());

    // iterate through currentGrid and update relevant cell in nextGrid
    // based on condition of neighbouring cells
    for (int i = 0; i < currentGrid.numRows(); i++) {
        for (int j = 0; j < currentGrid.numCols(); j++) {
            int neighbours;
            bool leftEdge = false;
            bool topEdge = false;
            bool rightEdge = false;
            bool bottomEdge = false;

            // set relevant boolean variables if we are on an edge/corner
            if (i == 0) topEdge == true;
            if (i == currentGrid.numRows() - 1) bottomEdge = true;
            if (j == 0) leftEdge == true;
            if (j == currentGrid.numCols() - 1) rightEdge = true;


            // Check neighbours of cell in currentGrid.
            // We rely on logic short-circuiting to avoid out
            // of bounds exceptions in edge cases

            // left neighbour
            if (!leftEdge && currentGrid[i][j-1]) neighbours++;
            // upper left neighbour
            if (!(leftEdge || topEdge) && currentGrid[i-1][j-1]) neighbours++;
            // upper neighbour
            if (!topEdge && currentGrid[i-1][j]) neighbours++;
            // upper right neighbour
            if (!(rightEdge || topEdge) && currentGrid[i-1][j+1]) neighbours++;
            // right neighbour
            if (!rightEdge && currentGrid[i][j+1]) neighbours++;
            // lower right neighbour
            if (!(rightEdge || bottomEdge) && currentGrid[i+1][j+1]) neighbours++;
            // lower neighbour
            if (!bottomEdge && currentGrid[i+1][j]) neighbours++;
            // lower left neighbour
            if (!(bottomEdge | leftEdge) && currentGrid[i+1][j-1]) neighbours++;

            // Update relevant cells in nextGrid
            if (neighbours == 0 || neighbours == 1 || neighbours >= 4) {
                // empty
                nextGrid[i][j] = false;
            } else if (neighbours == 2) {
                // stable
                nextGrid[i][j] = currentGrid[i][j];
            } else if (neighbours == 3) {
                // always contains a cell
                nextGrid[i][j] = true;
            }
        }
    }

    // dump contents of nextGrid into currentGrid
    currentGrid = nextGrid;
}
