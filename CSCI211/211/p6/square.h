//Brandon Smith
//CSCI 211
//square.h

#ifndef SQUARE_H
#define SQUARE_H

#include "shape.h"

class Square : public Shape
{

  public:
    Square(int, int, int);
    void draw(Grid &grid);

  private:
    int m_size;
};

#endif
