/****************************************************************************
  FileName  [ main.cpp ]
  Synopsis  [ Main function for EDACamp competition checker. ]
  Author    [ Fu-Yu Chuang ]
  Date      [ 2017.8.23 ]
****************************************************************************/

#include "checker.hpp"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
    const char* usageStr =
        (string("Usage: ") + argv[0] + "<input file> <result file>").c_str();
    fstream input, result;

    if (argc == 3) {
        input.open(argv[1], ios::in);
        result.open(argv[2], ios::in);
        if (!input) {
            cerr << "Cannot open the input file \"" << argv[1]
                 << "\". The program will be terminated..." << endl;
            exit(1);
        }
        if (!result) {
            cerr << "Cannot open the output file \"" << argv[2]
                 << "\". The program will be terminated..." << endl;
            exit(1);
        }
    } else {
        cerr << usageStr << endl;
        exit(1);
    }

    Checker checker = Checker(input, result);
    if (checker.check()) {
        checker.printSummary();
    }

    return 0;
}
