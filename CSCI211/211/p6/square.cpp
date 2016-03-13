//Brandon Smith
//CSCI 211
//Project 5
//square.cpp

#include "square.h"

Square::Square(int x, int y, int size)
       : Shape(x, y)
{
  m_size = size;
}

void Square::draw(Grid &grid)
{
  for(int i = 0; i < m_size; i++)           //draw a solid square
  {
    for(int j = 0; j < m_size; j++)
    {
      if(i == 0 || i == m_size-1 || j == 0 || j == m_size-1)
      {
        grid.set(m_x + i, m_y + j , '*');
      }
    }
  }
}





