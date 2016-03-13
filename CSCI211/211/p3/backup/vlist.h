//Brandon Smith
//CSCI 211
//Project 3 Linked List
//vlist.h

#ifndef VLIST_H
#define VLIST_H

#include"video.h"
#include<iostream>
#include<string>
using namespace std;

class Vlist
{
  public:
    Vlist();                              //Constructor
    ~Vlist();                             //Destructor
    int insert(Video *pvideo);            //function to insert Video object
    void print();
    int remove(string title);
    int length();
    int lookup(string title);

  private:
    class Node
    {
      public:
        Node(Video *pvideo, Node *pnext)  //node constructor
        {
          vlist_pvideo = pvideo;          //set member variable to input variable
          vlist_pnext = pnext;            //set member variable to input variable
        }

        ~Node()
        {
          delete vlist_pvideo;            //delete the associated video
        }

        Video *vlist_pvideo;              //Node contains pointer to related video
        Node *vlist_pnext;                //Node contains pointer to next node in list
    };

    Node *vlist_phead;                    //Vlist contains pointer to head node
};

#endif
