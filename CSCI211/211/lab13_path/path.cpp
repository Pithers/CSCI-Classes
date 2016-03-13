//Brandon Smith
//CSCI 211
//Main

#include "location.h"
#include <iostream>
#include <vector>
using namespace std;

int main()
{
  double lon;
  double lat;
  vector<Location*> gps;

  while(cin >> lon && cin >> lat)
  {
    gps.push_back(new Location(lon, lat));
  }

  for(int i = 0; i < (int)gps.size(); i++)
  {
    gps.at(i)->print(cout);
    cout << endl;
  }

  return 0;
}
