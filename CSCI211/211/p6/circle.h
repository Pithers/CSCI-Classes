//Brandon Smith
//CSCI 211
//circle.h

#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

class Circle : public Shape
{

  public:
    Circle(int, int);
    virtual void draw(Grid &grid);
};

#endif
