#include <iostream>
#include <stdlib.h>
using namespace std;

bool legal_int(char*);

int main(int argc, char *argv[])
{
  int temp = 0;

  if(argc > 1)
  {
    for(int i = 1; i < argc; i++)
    {
      if(legal_int(argv[i]))
      {
        temp = temp + atoi(argv[i]);
      }
      else
      {
        cerr << "Error: illegal integer." << endl;
        return 1;
      }
    }

    cout << temp << endl;
  }

  return 0;
}

bool legal_int(char *str)
{
  for(int i = 0; str[i] != 0; i++)
  {
    if(!isdigit(str[i]))
    {
      return false;
    }
  }
  return true;
}
