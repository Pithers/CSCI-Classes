//Brandon Smith
//CSCI 211
//dstack.h

#ifndef DSTACK_H
#define DSTACK_H

class Dstack
{

  public:
    Dstack();
    ~Dstack();
    void push(double number);
    bool pop(double &number);
    bool empty();
    int size();

  private:

    class Node
    {
      public:
        Node(double value, Node* next)
        {
          m_next = next;
          m_value = value;
        }

        Node* m_next;
        double m_value;
    };

    Node* m_head;

};

#endif
