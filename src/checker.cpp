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

#define SRC 0
#define DEST 1
#define DIR_X 0
#define DIR_Y 1

using namespace std;

void Checker::printSummary() const
{

    return;
}

void Checker::check()
{
    _coordinateTable[SRC][N] = Point(1, 3);
    _coordinateTable[DEST][N] = Point(2, 3);
    _coordinateTable[SRC][E] = Point(3, 2);
    _coordinateTable[DEST][E] = Point(3, 1);
    _coordinateTable[SRC][S] = Point(2, 0);
    _coordinateTable[DEST][S] = Point(1, 0);
    _coordinateTable[SRC][W] = Point(0, 1);
    _coordinateTable[DEST][W] = Point(0, 2);

    _dirTable[N] = DIR_Y;
    _dirTable[E] = DIR_X;
    _dirTable[S] = DIR_Y;
    _dirTable[W] = DIR_X;

    int timeCount = 0;

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

bool Checker::checkConflicts(const vector<pair<int, int> >& commands) {
  bool grid[4][4] = {};

  for (const auto& c : commands) {
    const Point src = _coordinateTable[SRC][c.first];
    const Point dest = _coordinateTable[DEST][c.second];
    const int dir = _dirTable[c.first];

    bool hasConflict = false;
    int x = src.first;
    int y = src.second;
    if (dir == DIR_X) {
      while (x != dest.first) {
        (x < dest.first) ? ++x : --x;

        if (grid[x][y]) {
          hasConflict = true;
          break;
        }

        grid[x][y] = true;
      }

      if (hasConflict) {
        return true;
      }

      while (y != dest.second) {
        (y < dest.second) ? ++y : --y;

        if (grid[x][y]) {
          hasConflict = true;
          break;
        }

        grid[x][y] = true;
      }

      if (hasConflict) {
        return true;
      }
    } else {
      while (y != dest.second) {
        (y < dest.second) ? ++y : --y;

        if (grid[x][y]) {
          hasConflict = true;
          break;
        }

        grid[x][y] = true;
      }

      if (hasConflict) {
        return true;
      }

      while (x != dest.first) {
        (x < dest.first) ? ++x : --x;

        if (grid[x][y]) {
          hasConflict = true;
          break;
        }

        grid[x][y] = true;
      }

      if (hasConflict) {
        return true;
      }
    }

    if (hasConflict) {
      return true;
    }
  }

  return false;
}
