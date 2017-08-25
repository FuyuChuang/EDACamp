/****************************************************************************
  FileName  [ checker.h ]
  Synopsis  [ Checker for EDACamp competition. ]
  Author    [ Fu-Yu Chuang, Yu-Hsuan Chang ]
  Date      [ 2017.8.24 ]
****************************************************************************/
#ifndef CHECKER_H
#define CHECKER_H

#include <fstream>
#include <vector>
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
        _carCount(0), _totalRound(0), _input(4), _output(4), _result(4) {
        parseInput(inFile);
        parseResult(result);
        buildTables();
    }
    ~Checker() { }

    // modify methods
    bool check();

    // member functions about reporting
    void printSummary() const;


private:
    int                     _carCount;                  // number of cars in the schedule
    int                     _totalRound;                // total required round number
    int                     _dirTable[4];               // used to check conflicts
    Point                   _coordinateTable[2][4];     // used to check conflicts
    vector<queue<Car> >     _input;                     // input car schedule
    vector<queue<Car> >     _output;                    // the scheduled cars according to _result
    vector<queue<int> >     _result;                    // the result to be checked

    // Private member functions
    // parse
    void parseInput(fstream& inFile);
    void parseResult(fstream& result);

    // check
    void buildTables();
    bool checkConflicts(const vector<pair<int, int> >& commands);
};

#endif  // CHECKER_H
