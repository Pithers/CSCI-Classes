//Brandon Smith
//CSCI 211
//Project 5
//triangle.cpp

#include "triangle.h"

Triangle::Triangle(int x, int y)
         : Shape(x, y)
{
}

void Triangle::draw(Grid &grid)
{
  grid.set(m_y + 2, m_x, '+');
  grid.set(m_y + 1, m_x+1, '+');
  grid.set(m_y + 3, m_x+1, '+');

  for(int i = 0; i < 5; i++)
  {
    grid.set(m_y + i, m_x + 2, '+');
  }
}






