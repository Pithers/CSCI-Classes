//Brandon Smith
//CSCI 211
//cust.h

#ifndef CUST_H
#define CUST_H

#include <string>
#include <fstream>
using namespace std;

class Cust 
{

  public:
    Cust(string, bool, int, int);
    ~Cust();
    void print(ostream &os);

  private:

    string m_name;
    bool m_alignment;
    int m_arrival;
    int m_items;

};

#endif
