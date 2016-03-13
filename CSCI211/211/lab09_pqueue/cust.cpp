//Brandon Smith
//CSCI 211
//Project 5
//cust.cpp

#include "cust.h"
#include <cstddef>
#include <string>
#include <fstream>
using namespace std;

Cust::Cust(string name, bool alignment, int arrival, int items)
{
  m_name = name;
  m_alignment = alignment;
  m_arrival = arrival;
  m_items = items;
}

void Cust::print(ostream &os)
{
  string temp;
  if(!m_alignment)
  {
    temp = "shopper";
  }
  else
  {
    temp = "robber";
  }

  os << m_name << " " << temp << " " << m_arrival << " " << m_items << endl;
}



