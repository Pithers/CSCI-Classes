//CSCI 211
//Brandon Smith
//bst.h

#ifndef BST_H
#define BST_H

#include <string>
#include <vector>
using namespace std;

class BST
{
  public:
    BST();
    ~BST();
    bool insert(string str) {return insert(str, m_root);}
    bool find(string);
    vector<string> print();
    vector<string> breadth(); 
    int size();
    int distance();

  private:
    class Node
    {
      public:

        Node(string value)
        {
          m_value = value;
          m_right = NULL;
          m_left = NULL;
        }

        Node* m_right;
        Node* m_left;
        string m_value;
    };

    Node* m_root;

    bool insert(string str, Node* &cur_root);
    bool dft_search(string, Node* &cur);
    int dft_distance(int, Node* &cur);
    void dft(vector<string> &values, Node*);
    void bft(vector<string> &values, Node*);
    

};

#endif
