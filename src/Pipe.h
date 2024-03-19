#include <string>
using namespace std;

#ifndef DA_PROJ_1_PIPE_H
#define DA_PROJ_1_PIPE_H

class Pipe {
private:
    string _pointA;
    string _pointB;
    int _capacity;
    int _direction;

public:
    Pipe();
    Pipe(string pointA, string pointB, int capacity, int direction);

    void setPointA(string pointA);
    void setPointB(string pointB);
    void setCapacity(int capacity);
    void setDirection(int direction);

    string getPointA();
    string getPointB();
    int getCapacity();
    int getDirection();
};


#endif //DA_PROJ_1_PIPE_H
