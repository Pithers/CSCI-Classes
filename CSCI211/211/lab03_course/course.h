//CSCI 211
//Course.h
//bpsmith
//Lab 3 Excercise 4

#ifndef COURSE_H
#define COURSE_H

#include<string>
using namespace std;

class Course
{
  public:
    void print(); //print function
    Course(string, int, int); //constructor
  private:
    string course_name; //private variables
    int course_num;
    int course_room;
};

#endif

