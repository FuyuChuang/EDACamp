/****************************************************************************
  FileName  [ checker.cpp ]
  Synopsis  [ Implementation of the EDACamp competition checker. ]
  Author    [ Fu-Yu Chuang ]
  Date      [ 2017.8.24 ]
****************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cassert>
#include <vector>
#include <cmath>
#include <map>
#include "checker.h"
using namespace std;

void Checker::printSummary() const
{

    return;
}

void Checker::check()
{

    return;
}

// private member functions
void Checker::parseInput(fstream& inFile)
{
    string str, token;

    while (getline(inFile, str)) {
        stringstream ss(str);
        while (ss >> token) {
            cout << token[1] << endl;
        }
    }
    return;
}

void Checker::parseOutput(fstream& outFile)
{

    return;
}

void Checker::clear()
{
    return;
}
