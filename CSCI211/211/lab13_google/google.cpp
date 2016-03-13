//Brandon Smith
//CSCI 211
//Main

#include "location.h"
#include <iostream>
#include <map>
using namespace std;

int main()
{
  double lon = 1;
  double lat = 1;
  string name;
  multimap<string,Location*> gps;
  multimap<string,Location*>::iterator iter;

  while(cin >> lon && lon!= 0 && cin >> lat && cin >> name)
  {
    gps.insert(pair<string, Location*>(name, new Location(lon, lat)));
  }

  while(cin >> name)
  {
    iter = gps.find(name);
    if(iter == gps.end())
    {
      cout << name << " not in database" << endl;
    }
    else
    {
      cout << iter->first << " is at ";
      iter->second->print(cout);
      cout << endl;
    }
  }
  return 0;
}
