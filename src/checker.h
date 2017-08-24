/****************************************************************************
  FileName  [ checker.h ]
  Synopsis  [ Checker for EDACamp competition. ]
  Author    [ Fu-Yu Chuang ]
  Date      [ 2017.8.24 ]
****************************************************************************/
#ifndef CHECKER_H
#define CHECKER_H

#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include "car.h"
using namespace std;

using Point = pair<int, int>;

#define N 0
#define E 1
#define S 2
#define W 3

class Checker
{
public:
    // constructor and destructor
    Checker(fstream& inFile, fstream& result) :
        _input(4), _result(4), _carCount(0) {
        parseInput(inFile);
        parseResult(result);
    }
    ~Checker() { }

    // modify method
    void check();

    // member functions about reporting
    void printSummary() const;

private:
    vector<queue<Car> >     _input;
    vector<queue<int> >     _result;
    Point                   _coordinateTable[2][4];
    int                     _dirTable[4];
    int                     _carCount;

    // Private member functions
    // parse
    void parseInput(fstream& inFile);
    void parseResult(fstream& result);
    bool checkConflicts(const vector<pair<int, int> >& commands);
};

#endif  // CHECKER_H
