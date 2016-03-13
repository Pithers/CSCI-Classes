//Course.cpp
//Brandon Smith
//Lab 3 Excercise 4
//CSCI 211

#include<iostream>
#include"course.h"
#include<string>
using namespace std;

//Constructor
Course::Course(string name, int num, int room)
{
  course_name = name; //set up private variables
  course_num = num; 
  course_room = room;
}

//Print function
void Course::print()
{
  cout << course_name << " " << course_num << " at " << course_room << "\n";
}
