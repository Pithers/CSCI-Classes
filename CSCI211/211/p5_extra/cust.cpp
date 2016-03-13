//Brandon Smith
//CSCI 211
//Project 5
//cust.cpp

#include "cust.h"
#include <cstddef>
#include <string>
#include <fstream>
#include <assert.h>
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

void Cust::print_entered(ostream &os, int clock)
{
  assert(clock == m_arrival);
  os << clock << ": " << m_name << " entered store" << endl; 
}

void Cust::print_finish_shop(ostream &os, int clock, int checker)
{
  //anything here? 
  os << clock << ": " << m_name << " done shopping, waiting for checker " << checker << endl;
}

void Cust::print_start_cs(ostream &os, int clock, int checker)
{
  os << clock << ": " << m_name << " started checkout with checker " << checker <<  endl;
}

void Cust::print_finish_cs(ostream &os, int clock, int checker, int ammount)
{
  os << clock << ": " << m_name;

  if(!m_alignment)
  {
    os << " paid $" << 3*m_items << " for " << m_items;  
    if(m_items > 1)
    {
      os << " items to checker " << checker <<  endl;
    }
    else
    {
      os << " item to checker " << checker << endl;
    }
  }

  else
  {
    os << " stole $" << ammount << " and " << m_items; 
    if(m_items > 1)
    {
      os << " items from checker " << checker << endl;
    }
    else
    {
      os << " item from checker " << checker << endl;
    }
  }
}

int Cust::get_items()
{
  return m_items;
}

bool Cust::get_alignment()
{
  return m_alignment;
}













