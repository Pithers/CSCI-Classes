//Brandon Smith
//CSCI 211
//shape.h

#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <fstream>
#include "grid.h"
using namespace std;

class Shape 
{

  public:
    Shape(int, int);
    virtual void draw(Grid &grid) = 0;

  protected:
    int m_x;
    int m_y;
};

#endif
