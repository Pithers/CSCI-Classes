#include "dstack.h"
#include <iostream>
#include <string>
#include <cmath>
#include <cerrno>
#include <cstdlib>
#include <stdio.h>
using namespace std;

int main()
{

  double temp = 0;
  double temp2 = 0;
  double temp3 = 0;
  string error = "Error: Invalid expression.\n";
  Dstack stack;

  //**********Account for first number starting with '.'**********************
  if(cin.peek() == '.')                 
  {
    cin.get();
    if(isdigit(cin.peek()))
    {
      cin.putback('.');
      cin.putback('0');
      cin >> temp;
      stack.push(temp);
    }
    else
    {
      cerr << error;
      exit(1);
    }
  }

  while(cin.peek() != EOF)                //until end of file
  {
    //***********Account for Spaces**************
    if(isspace(cin.peek()))              
    {
      cin.ignore();
      if(cin.peek() == '.')               //account for numbers starting with '.'
      {
        cin.get();
        if(isdigit(cin.peek()))
        {
          cin.putback('.');
          cin.putback('0');
          cin >> temp;
          stack.push(temp);
        }
      }
    }

    //***********Account for normal numbers*************
    else if(isdigit(cin.peek()))           
    {
      cin >> temp;
      stack.push(temp);
    }
    
    //***********Account for operators*******************
    else                                    //account for operators
    {
      switch (cin.peek())
      { 
        case '+': 
          cin.ignore();
          if(stack.pop(temp) == 0) {cerr << error; exit(1);}
          if(stack.pop(temp2) == 0) {cerr << error; exit(1);}
          stack.push(temp+temp2);
          break;

        case '-':
          cin.ignore();

           //*************Account for negative numbers*************
           if(isdigit(cin.peek()))
           {
              cin.putback('-');
              cin >> temp;
              stack.push(temp);
           }
           else if(cin.peek() == '.')           //account for numbers such as: -.5
           {
              cin.get();
              if(isdigit(cin.peek())) 
              {
                cin.putback('.');
                cin.putback('0'); 
                cin.putback('-');
                cin >> temp;
                stack.push(temp);
              }
              else                                //account for error such as -. 3
              {
                cerr << error;
                exit(1);
              }
           }
           else
           {
            if(stack.pop(temp) == 0) {cerr << error; exit(1);}
            if(stack.pop(temp2) == 0) {cerr << error; exit(1);}
            stack.push(temp2-temp);
           }
           break;

        case '*':
          cin.ignore();
          if(stack.pop(temp) == 0) {cerr << error; exit(1);}
          if(stack.pop(temp2) == 0) {cerr << error; exit(1);}
          stack.push(temp*temp2);
          break;

        case '/':
          cin.ignore();
          if(stack.pop(temp) == 0) {cerr << error; exit(1);}
          if(stack.pop(temp2) == 0) {cerr << error; exit(1);}
          if(temp == 0) {cerr << error; exit(1);}
          stack.push(temp2/temp);
          break;

        case '^':
          cin.ignore();
          if(stack.pop(temp) == 0) {cerr << error; exit(1);}
          if(stack.pop(temp2) == 0) {cerr << error; exit(1);}

          temp3 = pow(temp2,temp);

          if(errno != 0)                //check error condition for power (pow sets errno if error)
          {
            cerr << error; 
            exit(1);
          }
          else
          {
            stack.push(temp3);          //if no error, we can push the value
          }
          break;

        default : 
          cerr << error;
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
    cerr << error;
    exit(1);
  }
  
  return 0;
}


