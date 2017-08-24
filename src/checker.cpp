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
    vector<queue<Car> > output;
    output.resize(4);

    while (!_result[0].empty()) {
        vector<pair<int, int> > commands;
        size_t lineCount = 0;

        // set up commands
        for (auto& q : _result) {
            int dest = q.front();
            q.pop();
            commands.push_back(make_pair(lineCount, dest));
            ++lineCount;
        }

        // check right cars
        for (auto& c : commands) {
            // check no U-turns
            if (c.first == c.second) {
                cout << "U-turn at time = " << timeCount << endl;
                return;
            }

            // check right cars in queue
            // cout << c.first << " " << c.second << endl;
            if (c.second != -1) {
                Car car = _input[c.first].front();
                _input[c.first].pop();
                if (car._dest != c.second) {
                    cout << "Illegal car at time = " << timeCount << endl;
                    return;
                }

                car._depTime = timeCount;
                if (car._arrTime > car._depTime) {
                    cout << "Illegal car at time = " << timeCount << ". Depart before Arrival." << endl;
                    return;
                }
                output[c.first].push(car);
            }
        }
        ++timeCount;
    }


    // calculate total rounds
    int totalRound = 0;
    for (size_t i = 0, end = output.size(); i < end; ++i) {
        while (!output[i].empty()) {
            Car car = output[i].front();
            output[i].pop();
            int waitRound = car._depTime - car._arrTime;
            assert(waitRound >= 0);
            totalRound += waitRound;
        }
    }
    cout << "Total waiting rounds = " << totalRound << endl;

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
            switch(token[1]) {
                case 'N': {
                    _input[lineCount].push(Car(0, timeCount));
                    break;
                }
                case 'E': {
                    _input[lineCount].push(Car(1, timeCount));
                    break;
                }
                case 'S': {
                    _input[lineCount].push(Car(2, timeCount));
                    break;
                }
                case 'W': {
                    _input[lineCount].push(Car(3, timeCount));
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
