//Brandon Smith
//CSCI 211
//Point.h

#ifndef POINT_H
#define POINT_H

#include "shape.h"

class Point : public Shape
{

  public:
    Point(int, int, char);
    virtual void draw(Grid &grid);

  private:
    char m_character;
};

#endif
