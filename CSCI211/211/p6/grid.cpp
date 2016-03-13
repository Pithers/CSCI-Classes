//Brandon Smith
//CSCI 211
//Project 5
//grid.cpp

#include "grid.h"
#include <cstddef>
#include <string>
#include <fstream>
#include <assert.h>
#include <iostream>
using namespace std;

Grid::Grid()
{
  m_grid_height = 24;
  m_grid_width = 60;

  for(int i = 0; i < m_grid_height; i++)        //24 high
  {
    for(int j = 0; j < m_grid_width; j++)       //60 wide
    {
      m_grid_array[i][j] = ' ';
    }
  }
}


void Grid::set(int x, int y, char c)
{
  if(x >= 0 && x < m_grid_width && y >= 0 && y < m_grid_height)   //if coordinates are inside of the grid
  {
    m_grid_array[y][x] = c;
  }
}


void Grid::print()
{
  for(int i = 0; i < m_grid_height; i++)       //24 high
  {
    for(int j = 0; j < m_grid_width; j++)     //60 wide
    {
      cout <<  m_grid_array[i][j];            //print out array
    }
    cout << endl;
  }
}






