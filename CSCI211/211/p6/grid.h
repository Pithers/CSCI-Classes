//Brandon Smith
//CSCI 211
//grid.h

#ifndef GRID_H
#define GRID_H

#include <string>
#include <fstream>
using namespace std;

class Grid 
{

  public:
    Grid();
    void set(int, int, char);
    void print();

  private:
    //need 2D char array 60 wide 24 high
    char m_grid_array[24][60];
    int m_grid_height;
    int m_grid_width;

};

#endif
