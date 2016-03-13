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

void Cust::print_finish_shop(ostream &os, int clock)
{
  //anything here? 
  os << clock << ": " << m_name << " done shopping" << endl;
}

void Cust::print_start_cs(ostream &os, int clock)
{
  os << clock << ": " << m_name;

  if(!m_alignment)
  {
    os << " started checkout" << endl;
  }
  else
  {
    os << " stole" << endl; 
  }
}

void Cust::print_finish_cs(ostream &os, int clock)
{
  os << clock << ": " << m_name;

  if(!m_alignment)
  {
    os << " finished checkout" << endl;
  }
  else
  {
    os << " finished stealing" << endl; 
  }
}













