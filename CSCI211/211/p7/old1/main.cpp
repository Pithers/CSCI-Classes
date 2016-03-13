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
      }

      else if(command == "balanced")
      {
      }

      else if(command == "rebalance")
      {
      }

      else
      {
        cerr << "Illegal command <" << command << ">.\n";
      }
  }

  return 0;
}

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









