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
    int timeCount = 0;


    for (auto& q : _result) {

    }

    return;
}

// private member functions
void Checker::parseInput(fstream& inFile)
{
    string str, token;
    size_t lineCount = 0;

    while (getline(inFile, str)) {
        stringstream ss(str);
        int timeCount = -1;
        while (ss >> token) {
            if (timeCount == -1) {
                ++timeCount;
                continue;
            }
            if (token[1] != '0') {
                _input[lineCount].push(Car(token[1], timeCount));
            }
            ++timeCount;
        }
        ++lineCount;
    }

    /*
    for (size_t i = 0, end = _input.size(); i < end; ++i) {
        while(!_input[i].empty()) {
            Car car = _input[i].front();
            _input[i].pop();
            cout << char(car._dest) << " ";
        }
        cout << endl;
    }
    */

    return;
}

void Checker::parseResult(fstream& result)
{
    string str, token;
    size_t lineCount = 0;

    while (getline(result, str)) {
        stringstream ss(str);
        int timeCount = -1;
        while (ss >> token) {
            if (timeCount == -1) {
                ++timeCount;
                continue;
            }
            switch(token[1]) {
                case 'N': {
                    _result[lineCount].push(N);
                    break;
                }
                case 'E': {
                    _result[lineCount].push(E);
                    break;
                }
                case 'S': {
                    _result[lineCount].push(S);
                    break;
                }
                case 'W': {
                    _result[lineCount].push(W);
                    break;
                }
                default: {
                    _result[lineCount].push(-1);
                    break;
                }
            }
            ++timeCount;
        }
        ++lineCount;
    }

    /*
    for (size_t i = 0, end = _result.size(); i < end; ++i) {
        while(!_result[i].empty()) {
            int dest = _result[i].front();
            _result[i].pop();
            cout << setw(3) << dest << " ";
        }
        cout << endl;
    }
    */

    return;
}
