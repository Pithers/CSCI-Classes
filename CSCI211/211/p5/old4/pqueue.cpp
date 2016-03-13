//Brandon Smith
//CSCI 211
//Project 5
//pqueue.cpp

#include "pqueue.h"
#include "cust.h"
#include <cstddef>
using namespace std;

Pqueue::Pqueue()
{
  m_head = NULL;
}

Pqueue::~Pqueue()
{
  while(m_head != NULL)
  {
    Node* cur = m_head;
    m_head = cur->m_next;
    delete cur; 
  }
}

Cust* Pqueue::dequeue()
{
  if(m_head != NULL)          //remove the head node, make the next node the head, and grab the customer pointer from the head node
  {
    Node* cur = m_head;
    Cust* temp = cur->m_cust;
    m_head = cur->m_next;
    delete cur;
    return temp;
  }
  else
  {
    return NULL;
  }
}

void Pqueue::enqueue(Cust *cust, int priority)
{
  Node* cur = m_head;
  bool insert = 0;

  if(cur == NULL || (priority < cur->m_priority))    //if there are no nodes
  {
    m_head = new Node(cust, m_head, priority);
  }
  else                                              //if there are more than two nodes
  {
    while(!insert && cur->m_next != NULL)
    {
      if(priority < cur->m_next->m_priority)
      {
        cur->m_next = new Node(cust, cur->m_next, priority);
        insert = 1;
      }

      cur = cur->m_next;
    }

    if(!insert && (cur->m_next == NULL))
    {
      cur->m_next = new Node(cust, cur->m_next, priority);
    }
  }
}

bool Pqueue::empty()
{
  return (m_head == NULL);
}

int Pqueue::length()
{
  int length = 0;
  Node* cur = m_head;
  while(cur != NULL)
  {
    length++;
    cur = cur->m_next;
  }

  return length;
}

int Pqueue::get_priority_of_first()
{
  if(m_head != NULL)
  {
    return m_head->m_priority;
  }
  else
  {
    return -1;
  }
}






