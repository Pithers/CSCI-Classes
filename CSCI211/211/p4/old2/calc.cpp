#include "dstack.h"
#include <iostream>
#include <string>
using namespace std;



int main()
{
  double temp = 0;
  double temp2 = 0;
  string error "Error: Invalid expression.\n";
  Dstack stack;
  
  while(cin.peek() != EOF)
  {
    if(isspace(cin.peek()))
    {
      cin.ignore();
    }
    else if(isdigit(cin.peek()))
    {
      cin >> temp;
      stack.push(temp);
    }
    else
    {
      switch (cin.peek())
      { 
        case '+': 
          if(stack.pop(temp) == 1) {cerr << error; exit(1);}
          if(stack.pop(temp2) == 1) {cerr << error; exit(1);}
          stack.push(temp+temp2);
          break;

        case '-':
          if(stack.pop(temp) == 1) {cerr << error; exit(1);}
          if(stack.pop(temp2) == 1) {cerr << error; exit(1);}
          stack.push(temp2-temp);
          break;

        case '*':
          if(stack.pop(temp) == 1) {cerr << error; exit(1);}
          if(stack.pop(temp2) == 1) {cerr << error; exit(1);}
          stack.push(temp*temp2);
          break;

        case '/':
          if(stack.pop(temp) == 1) {cerr << error; exit(1);}
          if(stack.pop(temp2) == 1) {cerr << error; exit(1);}
          stack.push(temp2/temp);
          break;

        case '^':
          if(stack.pop(temp) == 1) {cerr << error; exit(1);}
          if(stack.pop(temp2) == 1) {cerr << error; exit(1);}

          break;

        default : 
          cerr << "Error: Invalid expression.\n";
          exit(1);
      }
    }
  }

  if(stack.size() == 1)
  {
    stack.pop(temp);
    cout << temp << endl;
  }
  else
  {
    cerr << "Error: Invalid expression.\n";
    exit(1);
  }
  
  return 0;
}


