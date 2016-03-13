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

bool BST::remove(string temp)
{
  return remove_string(temp, m_root);
}

bool BST::remove_string(string temp, Node* cur)
{
  if(!find(temp))     //if string isn't in tree, also covers case where there is no tree
  {
    return false;
  }

  cout << "string is in tree" << endl;

  Node* temp_node = NULL;

  //check if head node is only node, we just remove the head node
  if(m_root->m_right == 0 && m_root->m_left == 0)
  {
    m_root = NULL;
    delete cur;
    return true;
  }

  cout << "head is not only node" << endl;

  //search through tree and find parent of node that has string
  int lr = 2;       //0 for left node, 1 for right node
  find_parent_remove(temp, cur, lr); 
  if(cur == NULL)
  {
    return false;
  }

  if(lr == 2)
  {
    cout << "parent node not found" << endl;
    return false;
  }

  cout << "found parent node of string" << endl;
  cout << "parent is " << cur->m_value << endl;

  //we now have the parent node that contains the string to be removed
  //we need to check if the child has nodes or not
  if(lr == 0)       //left node of parent
  {

    cout << "parent's left node" << endl;

    if(cur->m_left->m_right == NULL && cur->m_left->m_left == NULL)
    {

      cout << "No child nodes" << endl;

      temp_node = cur->m_left;   //grab node
      cur->m_left = NULL;   //remove left node from tree
      delete temp_node;          //delete node
    }
    else if(cur->m_left->m_right == NULL)
    {
      //one child on left 

      cout << "one child on left" << endl;

      temp_node = cur->m_left;
      cur->m_left = cur->m_left->m_left;
      delete temp_node;
    }
    else if(cur->m_left->m_left == NULL)
    {
      //one child on right

      cout << "one child on right" << endl;

      temp_node = cur->m_left;
      cur->m_left = cur->m_left->m_right;
      delete temp_node;
    }
    else
    {
      temp_node = cur;
      cout << "has both children" << endl;
      //contains both children
      //search right tree for smallest value, then swap value with that and remove smallest value node
      find_smallest_value(temp_node);            //get node to smallest value

      cout << "swapping values of smallest node and node with string" << endl;

      cur->m_left->m_value = temp_node->m_value; //replace value in node to be removed
      //recursively call the remove function on the new node to remove
 
      cout << "Node swapped = " << temp_node->m_value << " ";
      
      cout << "recursively calling function" << endl;

      remove_string(temp_node->m_value, temp_node);
    }
    return true;
  }
  else if(lr == 1)  //right node of parent
  {

    cout << "right child of parent" << endl;

    if(cur->m_right->m_right == NULL && cur->m_right->m_left == NULL)
    {

      cout << "No children" << endl;

      temp_node = cur->m_right;   //grab node
      cur->m_right = NULL;   //remove left node from tree
      delete temp_node;          //delete node
    }
    else if(cur->m_right->m_right == NULL)
    {
      //one child on left 
      
      cout << "one child on left" << endl;

      temp_node = cur->m_right;
      cur->m_right = cur->m_right->m_left;
      delete temp_node;
    }
    else if(cur->m_right->m_left == NULL)
    {
      //one child on right

      cout << "one child on right" << endl;

      temp_node = cur->m_right;
      cur->m_right = cur->m_right->m_right;
      delete temp_node;
    }
    else
    {
      temp_node = cur;
      cout << "has both children" << endl;
      //contains both children
      //search right tree for smallest value, then swap value with that and remove smallest value node
      find_smallest_value(temp_node);            //get node to smallest value

      cout << "swapping values of smallest node and node with string" << endl;

      cur->m_right->m_value = temp_node->m_value; //replace value in node to be removed
      //recursively call the remove function on the new node to remove
      
      cout << "Node swapped = " << temp_node->m_value;

      cout << "recursively calling function" << endl;

      remove_string(temp_node->m_value, temp_node);
    }
    return true;
  }
  return false;
}

void BST::find_smallest_value(Node* &cur)
{
  cout << "searching for smallest value node" << endl;

  if(cur == NULL)
  {
    cout << "Error: Given node does not exist" << endl;
  }

  while(cur->m_left != NULL)
  {
    cout << "good" << endl;
    cur = cur->m_left;
  }
  cout << "smallest node found" << endl;
}

void BST::find_parent_remove(string temp, Node* &cur, int& lr)
{

  cout << "finding parent..." << endl;

  if(lr != 2)   //if node has already been found
  {
    return;
  }

  if(cur->m_right == NULL && cur->m_left == NULL)
  {
    cout << "hit end of tree" << endl;
    return;
  }

  if(cur == NULL)
  {
    return;
  }

  cout << "parent exits" << endl;

  if(cur->m_right != NULL && cur->m_right->m_value == temp)
  {
    cout <<"parent is on right" << endl;
    lr = 1;
    cur = cur->m_right;
    return;
  }
  else if(cur->m_left != NULL && cur->m_left->m_value == temp)
  {
    cout << "parent is on left" << endl;
    lr = 0;
    cur = cur->m_left;
    return;
  }
  else
  {
   if(cur->m_left != NULL)
   {
    find_parent_remove(temp, cur->m_left, lr);
   }
   if(cur->m_right != NULL)
   {
    find_parent_remove(temp, cur->m_right, lr);
   }
  }
  return;
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
  if(end_index < start_index)        //no elements
  {
    return;
  }
  if(start_index == end_index)     //one element
  {
    insert(elements[end_index], m_root);
    return;
  }

  int middle_index = (start_index + end_index)/2;    //will round down
  insert(elements[middle_index], m_root);

  insert_from_vector(elements, middle_index + 1, end_index);
  insert_from_vector(elements, start_index, middle_index - 1);
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











