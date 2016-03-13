//Brandon Smith
//CSCI 211
//Project 3 Linked List
//vlist.cpp

#include "vlist.h"
#include <iostream>
using namespace std;

//Constructor
Vlist::Vlist()
{
  cout << "Calling constructor" << endl;
  vlist_phead = NULL;                   //initialize head pointer to null
}

//Destructor
Vlist::~Vlist()
{
  cout << "Calling destructor" << endl;
  Node *ptr = vlist_phead;              //create temporary pointer that starts at the head
  while(ptr != NULL)                    //as long as the head pointer isn't null there are still nodes
  {
    Node *ptemp;                        //create second temp pointer each time since temp is deleted
    ptemp = ptr;                        //equate the two pointers
    ptr = ptr->vlist_pnext;             //grab the next pointer from the list
    delete ptemp;                       //delete the object the current pointer points to
  }
}

void Vlist::insert(Video *pvideo)
{
  vlist_phead = new Node(pvideo, vlist_phead);    //create a new node with pointer to a Video object place this new node after head pointer
}

void Vlist::print()
{
  Node *pnode = vlist_phead;            //create temporary pointer set to the list's head
  Video *pvideo;                        //create temporary pointer set to the corresponding video at the node
  while(pnode != NULL)                  //as long as the temporary pointer isn't null
  {
    pvideo = pnode->vlist_pvideo;       //get the video at current node
    pvideo->print();                    //access the print function from the video at the current node
    pnode = pnode->vlist_pnext;         //increment pointer to the next node
  }
}








