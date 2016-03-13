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
  vlist_phead = NULL;                   //initialize head pointer to null
}

//Destructor
Vlist::~Vlist()
{
  while(vlist_phead != NULL)                    //as long as the head pointer isn't null there are still nodes
  {
    Node *ptemp;                                //create a temp pointer each time since temp is deleted
    ptemp = vlist_phead;                        //equate the two pointers
    vlist_phead = vlist_phead->vlist_pnext;     //set the head pointer to the next in list since the previous node is being deleted
    delete ptemp;                               //delete the current node
  }
}

int Vlist::insert(Video *pvideo)
{
  Node *pnode = vlist_phead;
  if((pnode == NULL) || (pnode->vlist_pvideo->get_title() > pvideo->get_title())) //combined null head & title greater that given title
  {
    vlist_phead = new Node(pvideo, vlist_phead);                              //create new node at head
  }
  else if(pnode->vlist_pvideo->get_title() == pvideo->get_title())            //if video at the head is the same as the inserting one
  {
    return 1;
  }
  else
  {
    while((pnode->vlist_pnext) && (pnode->vlist_pnext->vlist_pvideo->get_title() < pvideo->get_title())) //if pnext is not null and video is less than next video
    {
      pnode = pnode->vlist_pnext;              //increment pointer to next node
    }  

    if((pnode->vlist_pnext) && ((pnode->vlist_pnext->vlist_pvideo->get_title()) == (pvideo->get_title()))) //if video already exists
    {
      return 1;                         
    }
    else
    {
      pnode->vlist_pnext = new Node(pvideo, pnode->vlist_pnext);  //when correct place in list is found insert node between pnode and vlist_pnext  
    }
  }
  return 0;
}

void Vlist::print()
{
  Node *pnode = vlist_phead;            //create temporary pointer set to the list's head
  while(pnode != NULL)                  //as long as the temporary pointer isn't null
  {
    pnode->vlist_pvideo->print();       //get the video at current node
    pnode = pnode->vlist_pnext;         //increment pointer to the next node
  }
}

