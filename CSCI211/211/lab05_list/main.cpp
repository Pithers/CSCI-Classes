//Brandon Smith
//lab 5
//main.cpp

#include <iostream>
#include <string>
using namespace std;
#include "list.h"

int main()
{
    // instantiate a List class (the constructor takes NO arguments)
    List list;
    int temp;

    // NOTE:
    // List list();  is incorrect, when there are no arguments don't use ()

    // insert numbers into the list

    while(cin >> temp)
    {
      list.insert_at_end(temp);
    }

    list.print();
    cout << "sum = " << list.sum() << endl;
    return 0;
}
