//Brandon Smith
//CSCI 211
//Project 4
//dstack.cpp

#include "dstack.h"
#include <cstddef>
using namespace std;

Dstack::Dstack()
{
  m_head = NULL;
}

Dstack::~Dstack()
{
  while(m_head != NULL)
  {
    Node* cur = m_head;
    m_head = cur->m_next;
    delete cur; 
  }
}

void Dstack::push(double number)
{
  m_head = new Node(number, m_head);
}

bool Dstack::pop(double &number)
{
  Node* cur = m_head;

  if(m_head != NULL)
  {
    number = cur->m_value;
    m_head = cur->m_next;
    delete cur; 
    return true;
  }
  return false;
}

bool Dstack::empty()
{
  return (m_head == NULL);
}

