#ifndef LOCATION_H
#define LOCATION_H

#include <iostream>
using namespace std;

// Stores the latitude and Longitude of a location on the Earth
// Since this class is so small, it does not have a .cpp file
class Location
{
  public:
    Location(double latitude, double longitude)
    {
      m_url = "http://www.google.com/maps/@" + to_string(latitude) + "," + to_string(longitude) + ",18z";
    }

    // if you want to print to cout, pass cout to print()
    void print(ostream &os) {os << m_url;}

  private:
    string m_url;
};

#endif
