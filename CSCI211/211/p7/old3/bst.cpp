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
  remove_nodes(m_root);
}

void BST::rebalance()
{
  vector<string> temp;
  dft(temp, m_root);

  //delete all nodes in tree
  remove_nodes(m_root);
  m_root = NULL;

  insert_from_vector(temp, 0, temp.size() - 1);
}

void BST::insert_from_vector(vector <string> &elements, int start_index, int end_index)
{
  if(end_index  == -1)        //no elements
  {
    return;
  }
  if(end_index == 0 || start_index == end_index)     //one element
  {
    insert(elements[start_index], m_root);
    return;
  }

  int middle_index = (start_index + end_index)/2;    //will round down
  insert(elements[middle_index], m_root);

  insert_from_vector(elements, middle_index + 1, end_index);
  insert_from_vector(elements, start_index, end_index - 1);
}

void BST::remove_nodes(Node* &cur)
{
  if(cur == NULL)
  {
    return;
  }

  remove_nodes(cur->m_right);
  remove_nodes(cur->m_left);

  delete cur;
  return;
}

int BST::balanced()
{
  return r_balanced(m_root); 
}

int BST::r_balanced(Node* &cur)
{
  int left = 0;
  int right = 0;

  if(cur == NULL)
  {
    return 0;       //balanced at 0
  }

  left = r_balanced(cur->m_left);
  right = r_balanced(cur->m_right);

  if((left == -1) || (right == -1) || ((left - right) > 1) || ((left - right) < -1)) 
  {
    return -1;      //unbalanced
  }
  else
  {
    if(left > right)
    {
      return left + 1; 
    }
    else
    {
      return right + 1;
    }
  }
  return -1;
}

double BST::distance()
{
  return (double)dft_distance(0, m_root)/(double)size();
}

int BST::dft_distance(int level, Node* &cur)
{
  if(cur == NULL)
  {
    return 0;
  }

  return level + dft_distance(level+1, cur->m_left) + dft_distance(level+1, cur->m_right);
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











