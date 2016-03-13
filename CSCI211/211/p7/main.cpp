//CSCI 211
//Brandon Smith
//main.cpp

#include "bst.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

void vector_print(vector<string> temp);

int main()
{
  string command;
  string arguments;
  vector<string> temp;
  BST tree;
  int height = 0;

  while(cin >> command)
  {
      if(command ==  "echo") 
      {
        cin.ignore();
        getline(cin, arguments); 
        cout << arguments << endl;
      }

      else if(command == "insert") 
      {
        cin.ignore();
        getline(cin, arguments);
        if(!tree.insert(arguments))
        {
          cerr << "insert <" << arguments << "> failed. String already in tree.\n";
        }
      }

      else if(command == "size") 
      {
        cout << tree.size() << endl;
      }

      else if(command == "find")
      {
        cin.ignore();
        getline(cin, arguments);
        if(tree.find(arguments))
        {
          cout << "<" << arguments << "> is in tree." << endl;
        }
        else
        {
          cout << "<" << arguments << "> is not in tree." << endl;
        }
      }

      else if(command == "print")
      {
        temp = tree.print();
        vector_print(temp);
      }

      else if(command == "breadth")
      {
        temp = tree.breadth();
        vector_print(temp);
      }

      else if(command == "distance")
      {
        cout << "Average distance of nodes to root = " << tree.distance() << endl;
      }

      else if(command == "balanced")
      {
        height = tree.balanced();
        if(height < 0)
        {
          cout << "Tree is not balanced.\n"; 
        }
        else
        {
          cout << "Tree is balanced.\n";
        }
      }

      else if(command == "rebalance")
      {
        tree.rebalance();
      }

      else
      {
        getline(cin, arguments);                            //first word was an error, ignore the rest of the line
        cerr << "Illegal command <" << command << ">.\n";   
      }
  }

  return 0;
}

//function for printing out a vector
void vector_print(vector<string> temp)
{
  cout << "{";
  for(int i = 0; i < (int)temp.size(); i++)
  {
    if(i < ((int)temp.size() - 1))
    {
      cout << temp[i] << ", ";
    }
    else
    {
      cout << temp[i];
    }
  }
  cout << "}\n";
}









