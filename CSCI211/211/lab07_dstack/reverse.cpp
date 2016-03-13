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

  cout << "There are " << stack.size() << " numbers in the stack.\n";

  while(!stack.empty())
  {
    stack.pop(temp);
    cout << temp << endl;
  }

  cout << "There are " << stack.size() << " numbers in the stack.\n";
  
  return 0;
}


