//Brandon Smith
//CSCI 211
//Lab 2 Excercise 1

#include <iostream>
using namespace std;

int main()
{
  int value;

  // as long as we can read an integer from standard input (cin)
  // when the user enters control-D the "cin >> value" will return false
  while (cin >> value)
  {
    //Switch statement to convert number to string
    switch(value)
    {
      case 0:
        cout << "zero";
        break;
      case 1: 
        cout << "one";
        break;
      case 2: 
        cout << "two";
        break;
      case 3: 
        cout << "three";
        break;
      case 4:
        cout << "four";
        break;
      case 5: 
        cout << "five";
        break;
      case 6:
        cout << "six";
        break;
      case 7:
        cout << "seven";
        break;
      case 8:
        cout << "eight";
        break;
      case 9:
        cout << "nine";
        break;
      default:
        cout << "not an accepted number";
        break;
    }
    cout << "\n";
  }
  // return 0 from main() if there were no errors
  return 0; 
}
