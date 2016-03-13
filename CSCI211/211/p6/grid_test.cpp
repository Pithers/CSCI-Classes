#include "grid.h"
#include "square.h"
#include "shape.h"
#include "point.h"
#include "circle.h"
#include "triangle.h"
#include <iostream>
using namespace std;

int main()
{
  Grid my_grid;

  Point mypoint(15, 3, '?');
  mypoint.draw(my_grid);

  Triangle mytriangle(10, 10);
  mytriangle.draw(my_grid);

  Square my_square(0, 0, 24);
  my_square.draw(my_grid);

  Square my_square2(2, 5, 4);
  my_square2.draw(my_grid);

  Circle mycircle(5, 16);
  mycircle.draw(my_grid);

  my_grid.print();

  return 0;
}
