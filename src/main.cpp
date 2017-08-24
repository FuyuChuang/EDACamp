/****************************************************************************
  FileName  [ main.cpp ]
  Synopsis  [ Main function for EDACamp competition checker. ]
  Author    [ Fu-Yu Chuang ]
  Date      [ 2017.8.23 ]
****************************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include "checker.h"
using namespace std;

const char* usageStr = "Usage: ./FM_Partitioner <input file> <output file>";

int main(int argc, char** argv)
{
    fstream input, output;

    if (argc == 3) {
        input.open(argv[1], ios::in);
        output.open(argv[2], ios::in);
        if (!input) {
            cerr << "Cannot open the input file \"" << argv[1]
                 << "\". The program will be terminated..." << endl;
            exit(1);
        }
        if (!output) {
            cerr << "Cannot open the output file \"" << argv[2]
                 << "\". The program will be terminated..." << endl;
            exit(1);
        }
    }
    else {
        cerr << usageStr << endl;
        exit(1);
    }

    Checker* checker = new Checker(input, output);
    checker->check();
    checker->printSummary();

    return 0;
}
