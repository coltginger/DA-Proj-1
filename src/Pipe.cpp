#include "Pipe.h"

Pipe::Pipe() {
    _pointA = "";
    _pointB = "";
    _capacity = 0;
    _direction = 0;
}

Pipe::Pipe(std::string pointA, std::string pointB, int capacity, int direction) {
    _pointA = pointA;
    _pointB = pointB;
    _capacity = capacity;
    _direction = direction;
}

void Pipe::setPointA(std::string pointA) {
    _pointA = pointA;
}

void Pipe::setPointB(std::string pointB) {
    _pointB = pointB;
}

void Pipe::setCapacity(int capacity) {
    _capacity = capacity;
}

void Pipe::setDirection(int direction) {
    _direction = direction;
}

string Pipe::getPointA() {
    return _pointA;
}

string Pipe::getPointB() {
    return _pointB;
}

int Pipe::getCapacity() {
    return _capacity;
}

int Pipe::getDirection() {
    return _direction;
}