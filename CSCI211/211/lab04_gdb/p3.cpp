#include <iostream>
using namespace std;

// Normally the class declaration (class List) is put into a 
// separtate file (.h) from the class implementation (the functions)
// Everything is in one file so it is easier to learn about gdb/ddd

class List
{
    public:
        void insert(int i);
        void print();
        List();
    private:
        class Node
        {
            public:
                Node(int value, Node *next) 
                {m_value = value; m_next = next;}
                int m_value;
                Node *m_next;
        };
        Node *m_head;
};

List::List() 
{
    m_head = (Node *) 1;
}

void List::insert(int i)
{
    m_head = new Node(i, m_head);
}

void List::print()
{
    Node *cur = m_head;
    while (cur != NULL)
    {
        cout << cur->m_value << endl;
        cur = cur->m_next;
    }
}

int main()
{
    List list;

    list.insert(1);
    list.insert(2);
    list.insert(3);

    list.print();

    return 0;
}
