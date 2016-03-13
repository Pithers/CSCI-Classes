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
    void print_entered(ostream &os, int);
    void print_finish_shop(ostream &os, int);
    void print_start_cs(ostream &os, int);
    void print_finish_cs(ostream &os, int);

  private:

    string m_name;
    bool m_alignment;
    int m_arrival;
    int m_items;

};

#endif
