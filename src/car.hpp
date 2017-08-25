/****************************************************************************
  FileName  [ car.h ]
  Synopsis  [ Car in checker. ]
  Author    [ Fu-Yu Chuang ]
  Date      [ 2017.8.24 ]
****************************************************************************/

#ifndef CAR_H
#define CAR_H

class Car
{
  public:
    // constructor and destructor
    Car(int dst, int arrTime) : _dst(dst), _arrTime(arrTime), _depTime(-1) {}
    ~Car() {}

    // data members
    int _dst;     // destination (N:0, E:1, S:2, W:3)
    int _arrTime; // arrival time
    int _depTime; // departure time
};

#endif // CAR_H
