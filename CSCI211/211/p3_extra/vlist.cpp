//Brandon Smith
//CSCI 211
//Project 3 Linked List
//vlist.cpp

#include "vlist.h"
#include <iostream>
#include <regex.h>
#include <stdlib.h>
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
  if((pnode == NULL) || (pnode->vlist_pvideo->get_title() > pvideo->get_title()))	//combined null head & title greater than given title
  {
    vlist_phead = new Node(pvideo, vlist_phead);                              		//create new node at head
  }
  else if(pnode->vlist_pvideo->get_title() == pvideo->get_title())            		//if video at the head is the same as the inserting one
  {
    return 1;
  }
  else
  {
    while((pnode->vlist_pnext) && (pnode->vlist_pnext->vlist_pvideo->get_title() < pvideo->get_title())) //if next node is not null and video is less than next video
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

void Vlist::print_by_length()
{
  Node *pnode;
  int length = Vlist::length();		    //call lists' own function to get length

  //bubble sort the list by length
  for(int i = length-1; i > 0 ; i--)      //for the entire length of the list
  {
    pnode = vlist_phead;                  //always iterate starting from the head node
    for(int j = 0; j < i; j++)            //for every unsorted element compare the lengths
    {
      if(pnode->vlist_pvideo->get_length() > pnode->vlist_pnext->vlist_pvideo->get_length())
      {
	      swap(pnode->vlist_pvideo, pnode->vlist_pnext->vlist_pvideo); //swaps the video pointer of the two nodes in question
      }
      pnode = pnode->vlist_pnext;
    }
  }
  Vlist::print();                   //print out the new sorted list
  Vlist::sort_by_title();           //resort the list back to by title
}

void Vlist::print_by_rating()
{
  Node *pnode;
  float length = Vlist::length();		      //call lists' own function to get length

  //bubble sort the list by rating
  for(int i = length-1; i > 0 ; i--)      //for the entire length of the list
  {
    pnode = vlist_phead;                  //always iterate starting from the head node
    for(int j = 0; j < i; j++)            //for every unsorted element compare the ratings
    {
      if(pnode->vlist_pvideo->get_rating() < pnode->vlist_pnext->vlist_pvideo->get_rating())
      {
	      swap(pnode->vlist_pvideo, pnode->vlist_pnext->vlist_pvideo);  //swaps the video pointer of the two nodes in question
      }
      pnode = pnode->vlist_pnext;
    }
  }
  Vlist::print();                   //print out the new sorted list
  Vlist::sort_by_title();           //resort the list back to by title
}

void Vlist::sort_by_title()
{
  //function to alphabetically sort by title
  Node *pnode;
  float length = Vlist::length();		      //call lists' own function to get length

  //bubble sort the list by title
  for(int i = length-1; i > 0 ; i--)      //for the entire length of the list
  {
    pnode = vlist_phead;                  //always iterate starting from the head node
    for(int j = 0; j < i; j++)            //for every unsorted element compare the titles
    {
      if(pnode->vlist_pvideo->get_title() > pnode->vlist_pnext->vlist_pvideo->get_title())
      { 
	      swap(pnode->vlist_pvideo, pnode->vlist_pnext->vlist_pvideo);  //swaps the video pointer of the two nodes in question
      }
      pnode = pnode->vlist_pnext;
    }
  }
}

int Vlist::length()
{
  int length = 0;
  Node *pnode = vlist_phead;
  while(pnode != NULL)					                //while the current node is not null
  {
    length++;						                        //increment number of nodes traversed
    pnode = pnode->vlist_pnext;				          //increment to next node
  }
  return length;					                      //return total number of nodes traversed
}

int Vlist::lookup(string title)
{
  Node *pnode = vlist_phead;
  while(pnode != NULL)							                    //while the current node is not null
  {
    if(pnode->vlist_pvideo->get_title() == title)			  //compare the current node to the input title
    {
      pnode->vlist_pvideo->print();					            //if the titles match, have the associated video print itself out
      return 0;
    }
    pnode = pnode->vlist_pnext;						              //increment to the next node
  }
  return 1;                         					          //return error if title was not found
}

int Vlist::remove(string title)
{
  Node *pnode = vlist_phead;						//create temporary pointer to the current node and set it to the head

  if((pnode != NULL) && (pnode->vlist_pvideo->get_title() == title))	//if the first node is not null and is the title to be removed
  {
    vlist_phead = pnode->vlist_pnext; 					                      //set the new head to the next node
    delete pnode;							                                        //delete the node with the same title
    return 0;								                                          //succesfully deleted title
  }
  else
  {
    Node *temp;
    while(pnode != NULL && pnode->vlist_pnext != NULL) 			        //else iterate through the list as long as the current and next nodes are not null  
    {
      if(pnode->vlist_pnext->vlist_pvideo->get_title() == title)	  //if the next node's object has the same title as the input title
      {
        temp = pnode->vlist_pnext;					                        //set a temporary pointer to the node to be deleted
        pnode->vlist_pnext = pnode->vlist_pnext->vlist_pnext;		    //set the current node's next pointer to the node after the next node
        delete temp;							                                  //delete the node that contains the video with the same title
        return 0;							                                      //succesfully deleted title
      }
      pnode = pnode->vlist_pnext;					                          //increment to next node
    }
  }	
  return 1;                         					                      //if list is empty or title was not found, return error
}

int Vlist::lookup_expression(string temp)
{
  Node * pnode = vlist_phead;     //create temporary pointer
  regex_t reg_expression;         //create variable of regex type
  int result;
  int successful = 1;

  result = regcomp(&reg_expression, temp.c_str(), REG_EXTENDED);     //creat expression (returns 0 if successful)

  if(result)
  {
    return 1; 			                                                 //invalid regular expression
  }

  while(pnode != NULL)
  {
    result = regexec(&reg_expression, pnode->vlist_pvideo->get_title().c_str(),0,0,0); //use expression to search string
    if(!result)
    {
      pnode->vlist_pvideo->print();   //if string is found in the search print video (will already be sorted alphabetically)
      successful = 0;                 //and set return flag to 0
    }
    pnode = pnode->vlist_pnext;
  }
  return successful;                  //return value based on whether or not the search was successful
}

