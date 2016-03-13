//Brandon Smith
//CSCI 211
//triangle.h

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.h"

class Triangle : public Shape
{

  public:
    Triangle(int, int);
    void draw(Grid &grid);
};

#endif
