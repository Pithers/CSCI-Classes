//Brandon Smith
//CSCI 211
//Lab 2 Excercise 2

#include <iostream>
using namespace std;

int main()
{
  int value;
  int not_even = 0; //flag to tell if a number wasn't even

  // as long as we can read an integer from standard input (cin)
  // when the user enters control-D the "cin >> value" will return false
  while (cin >> value)
  {
    if((value % 2) != 0)
    {
      not_even = 1; //number was not even
    }
  }
  if( not_even == 1)
  {
    cerr << "not all even\n";
    return 1; //there was an error, return 1
  }
  else
  {
    cout << "all even\n";
    return 0; //there were no errors, return 0
  } 
}
