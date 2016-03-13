//CSCI 211
//Brandon Smith
//bst.cpp


#include "bst.h"
#include <string>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;


BST::BST()
{
  m_root = NULL;
}

BST::~BST()
{
}

int BST::distance()
{
  return dft_distance(0, m_root)/size();
}

int BST::dft_distance(int level, Node* &cur)
{
  if(cur == NULL)
  {
    return 0;
  }

  return level++;// + dft_distance(level++, cur-> ;
}


bool BST::find(string s)
{
  return dft_search(s, m_root);
}

bool BST::dft_search(string s, Node* &cur)
{
  if(cur == NULL)
  {
    return 0;
  }

  if(cur->m_value == s)
  {
    return 1;
  }

  return dft_search(s, cur->m_right) || dft_search(s, cur->m_left);
}

bool BST::insert(string str, Node* &cur_root)
{
  if(cur_root == NULL)
  {
    cur_root = new Node(str);
    return true;
  }
  else
  {
    //Pass to either right or left node
    if(str > cur_root->m_value)
    {
      return insert(str, cur_root->m_right);
    }
    else if(str < cur_root->m_value)
    {
      return insert(str, cur_root->m_left);
    }
    else
    {
      return false;
    }
  }
}

vector<string> BST::print()
{
  vector<string> temp;

  dft(temp, m_root);

  return temp;
}

vector<string> BST::breadth()
{
  vector<string> temp;

  bft(temp, m_root);

  return temp;
}

int BST::size()
{
  vector<string> temp;

  bft(temp, m_root);

  return (int)temp.size();
}


void BST::dft(vector<string> &temp, Node* cur)
{
  if(cur == NULL)
  {
    return;
  }

  dft(temp, cur->m_left);         //go to left node

  temp.push_back(cur->m_value);   //on return from left-most path, record string from node

  dft(temp, cur->m_right);        //go to right node
}

void BST::bft(vector<string> &temp, Node* cur)
{
  if(cur == NULL)
  {
    return;
  }

  queue<Node*> nqueue;
  nqueue.push(cur);         //start with root node

  while(!nqueue.empty())
  {
    cur = nqueue.front();   //get current pointer on stack (will be in order of nodes looked at)
    nqueue.pop();

    temp.push_back(cur->m_value); //record string from current node

    if(cur->m_left != NULL)       //put the left node on the stack
    {
      nqueue.push(cur->m_left);
    }

    if(cur->m_right != NULL)      //put the right node on the stack
    {
      nqueue.push(cur->m_right);
    }
  }
}











