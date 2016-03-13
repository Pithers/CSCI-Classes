//Schedule.cpp
//Brandon Smith
//CSCI 211
//Lab 3 Excercise 4

#include<iostream>
#include"course.h"
using namespace std;

int main()
{

  Course programming("CSCI",211,1000); //create object
  Course english("ENGL",130,1400); //create object
  Course physics("PHYS",204, 800); //create object

  programming.print();
  english.print();
  physics.print();
   
  return 0;
}

