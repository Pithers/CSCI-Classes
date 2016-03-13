//Brandon Smith
//CSCI 211
//pqueue.h

#ifndef PQUEUE_H
#define PQUEUE_H

#include "cust.h"

class Pqueue 
{

  public:
    Pqueue();
    ~Pqueue();

    Cust* dequeue();
    void enqueue(Cust*, int);
    bool empty();
    int length();
    int get_priority_of_first();

  private:

    class Node
    {
      public:
        Node(Cust* cust, Node* next, int priority) 
        {
          m_next = next;
          m_cust = cust;
          m_priority = priority;
        }

        Node* m_next;
        Cust* m_cust;
        int m_priority;
    };

    Node* m_head;

};

#endif
