#include "dstack.h"
#include <iostream>
using namespace std;



int main()
{
  double temp = 0;
  Dstack stack;
  
  while(cin >> temp)
  {
    stack.push(temp);
  }

  while(!stack.empty())
  {
    stack.pop(temp);
    cout << temp << endl;
  }
  
  return 0;
}


