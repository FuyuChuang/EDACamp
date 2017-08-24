/****************************************************************************
  FileName  [ car.h ]
  Synopsis  [ Car in checker. ]
  Author    [ Fu-Yu Chuang ]
  Date      [ 2017.8.24 ]
****************************************************************************/
#ifndef CAR_H
#define CAR_H

#include <fstream>
#include <vector>
using namespace std;


class Car
{
public:
    // constructor and destructor
    Car(size_t dest, size_t arrTime) :
        _dest(dest), _arrTime(arrTime), _depTime(0) {
    }
    ~Car() { }

    int     _dest;
    size_t  _arrTime;
    size_t  _depTime;
};

#endif  // CHECKER_H
