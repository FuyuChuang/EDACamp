/****************************************************************************
  FileName  [ checker.cpp ]
  Synopsis  [ Implementation of the EDACamp competition checker. ]
  Author    [ Fu-Yu Chuang, Yu-Hsuan Chang ]
  Date      [ 2017.8.24 ]
****************************************************************************/

#include "checker.hpp"

#include <cassert>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

#define N 0
#define E 1
#define S 2
#define W 3

#define SRC 0
#define DST 1

void Checker::printSummary() const
{
    cout << endl;
    cout << "==================== Summary ====================" << endl;
    cout << " Total car number: " << _carCount << endl;
    cout << " Total rounds spent: " << _totalRound << endl;
    cout << " Average waiting rounds: " << double(_totalRound) / _carCount
         << endl;
    cout << "=================================================" << endl;
    cout << endl;

    return;
}

bool Checker::check()
{
    int timeCount = 0;

    while (!_result[0].empty()) {
        vector<pair<int, int>> commands;
        size_t lineCount = 0;

        // set up commands
        for (auto& q : _result) {
            int dst = q.front();
            q.pop();
            commands.push_back(make_pair(lineCount, dst));
            ++lineCount;
        }

        // check right cars
        for (auto& c : commands) {
            int src = c.first, dst = c.second;

            // check if there are U-turns
            if (src == dst) {
                cout << "U-turn at time = " << timeCount << endl;
                return false;
            }

            // check if the cars scheduled are legal
            if (dst != -1) {
                Car& car = _input[src].front();
                _input[src].pop();
                if (car._dst != dst) {
                    cout << "Illegal car at time = " << timeCount
                         << ". Non-existent." << endl;
                    return false;
                }

                car._depTime = timeCount;
                if (car._arrTime > car._depTime) {
                    cout << "Illegal car at time = " << timeCount
                         << ". Depart before Arrival." << endl;
                    return false;
                }
                _output[src].push(car);
            }
        }

        // check conflicts
        if (checkConflicts(commands)) {
            cout << "Conflicts occur at time = " << timeCount << endl;
            return false;
        }

        ++timeCount;
    }

    // check if scheduled all traffics
    const string   dir[4] = {"north", "east", "south", "west"};
    bool           clear  = true;
    vector<size_t> flag;
    for (size_t i = 0, end = _input.size(); i < end; ++i) {
        if (!_input[i].empty()) {
            clear = false;
            flag.push_back(i);
        }
    }
    if (!clear) {
        cout << "Not all cars are scheduled." << endl;
        cout << "Cars left at ";
        for (size_t i = 0, end = flag.size(); i < end; ++i) {
            cout << dir[flag[i]];
            cout << ((i == end - 1) ? "." : ", ");
        }
        cout << endl;
        return false;
    }

    // calculate total rounds
    for (size_t i = 0, end = _output.size(); i < end; ++i) {
        while (!_output[i].empty()) {
            const Car& car = _output[i].front();
            _output[i].pop();
            int waitRound = (car._depTime - car._arrTime);
            assert(waitRound >= 0);
            _totalRound += waitRound;
        }
    }

    return true;
}

// private member functions
void Checker::parseInput(fstream& inFile)
{
    string str, token;
    size_t lineCount = 0;

    while (getline(inFile, str)) {
        stringstream ss(str);
        int          timeCount = -1;

        while (ss >> token) {
            if (timeCount == -1) {
                ++timeCount;
                continue;
            }

            switch (token[1]) {
                case 'N': {
                    _input[lineCount].push(Car(N, timeCount));
                    ++_carCount;
                    break;
                }
                case 'E': {
                    _input[lineCount].push(Car(E, timeCount));
                    ++_carCount;
                    break;
                }
                case 'S': {
                    _input[lineCount].push(Car(S, timeCount));
                    ++_carCount;
                    break;
                }
                case 'W': {
                    _input[lineCount].push(Car(W, timeCount));
                    ++_carCount;
                    break;
                }
                default: {
                    break;
                }
            }
            ++timeCount;
        }
        ++lineCount;
    }

    return;
}

void Checker::parseResult(fstream& result)
{
    string str, token;
    size_t lineCount = 0;

    while (getline(result, str)) {
        stringstream ss(str);
        int          timeCount = -1;

        while (ss >> token) {
            if (timeCount == -1) {
                if (!(token == "N:" || token == "E:" || token == "S:" ||
                      token == "W:")) {
                    cerr << "Wrong output format." << endl;
                    exit(1);
                }
                ++timeCount;
                continue;
            }

            switch (token[1]) {
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

    return;
}

void Checker::buildTables()
{
    /*  Left-hand drive (right-hand traffic)
             0           1          2          3
        ---------------------------------------------
      3 |          | (SRC, N) | (DST, N) |          |
        ---------------------------------------------
      2 | (DST, W) |          |          | (SRC, E) |
        ---------------------------------------------
      1 | (SRC, W) |          |          | (DST, E) |
        ---------------------------------------------
      0 |          | (DST, S) | (SRC, S) |          |
        ---------------------------------------------  */
    _coordinateTable[SRC][N] = Point(1, 3);
    _coordinateTable[DST][N] = Point(2, 3);
    _coordinateTable[SRC][E] = Point(3, 2);
    _coordinateTable[DST][E] = Point(3, 1);
    _coordinateTable[SRC][S] = Point(2, 0);
    _coordinateTable[DST][S] = Point(1, 0);
    _coordinateTable[SRC][W] = Point(0, 1);
    _coordinateTable[DST][W] = Point(0, 2);

    _initDirTable[N] = S;
    _initDirTable[E] = W;
    _initDirTable[S] = N;
    _initDirTable[W] = E;

    return;
}

bool Checker::checkConflicts(const vector<pair<int, int>>& commands)
{
    const auto distance = [](const Point& p1, const Point& p2) -> int {
        return abs(p1.first - p2.first) + abs(p1.second - p2.second);
    };
    const auto nextPos = [](const Point& src, int dir) -> Point {
        switch (dir) {
            case N: {
                return Point(src.first, src.second + 1);
            }
            case E: {
                return Point(src.first + 1, src.second);
            }
            case S: {
                return Point(src.first, src.second - 1);
            }
            case W: {
                return Point(src.first - 1, src.second);
            }
            default: {
                return src;
            }
        }

        return src;
    };
    const auto nextDir = [&](const Point& src, const Point& dst,
                             int preferredDir) -> int {
        const int numDirs = 4;

        for (int i = preferredDir; i < preferredDir + numDirs; ++i) {
            const int dir = i % numDirs;

            if (distance(nextPos(src, dir), dst) < distance(src, dst)) {
                return dir;
            }
        }

        return preferredDir;
    };
    const auto move = [&](const Point& src, const Point& dst,
                          int preferredDir) -> Point {
        return nextPos(src, nextDir(src, dst, preferredDir));
    };
    const int gridWidth = 4;

    bool grid[gridWidth][gridWidth] = {};
    for (const auto& c : commands) {
        // Skip NULL cars.
        if (c.second == -1) {
            continue;
        }

        const Point src     = _coordinateTable[SRC][c.first];
        const Point dst     = _coordinateTable[DST][c.second];
        const int   initDir = _initDirTable[c.first];

        Point currPos = src;
        while (currPos != dst) {
            currPos = move(currPos, dst, initDir);

            const int currX = currPos.first;
            const int currY = currPos.second;

            if (grid[currX][currY]) {
                return true;
            }

            grid[currX][currY] = true;
        }
    }

    return false;
}
