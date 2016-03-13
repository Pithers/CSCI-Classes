//Brandon Smith
//CSCI 211
//Project 5
//point.cpp

#include "point.h"

Point::Point(int x, int y, char character)
      : Shape(x, y)
{
  m_character = character;
}

void Point::draw(Grid &grid)
{
    grid.set(m_x, m_y, m_character);
}





