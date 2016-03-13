//Brandon Smith
//bpsmith
//CSCI 211
//Project 3 Linked List
//Main.cpp

#include"video.h"
#include"vlist.h"

#include<iostream>
#include<string>

using namespace std;

#define MAX 100 

int main()
{
  string command;

  //Define variables
  string sort;
  string title;
  string url;
  string comment;
  string temp_string;
  float length;
  int rating;
  int video_num = 0;

  //Object pointer array
  //Video *video_array[MAX];

  //Get and handle commands
  while(getline(cin, command))
  {
    if(command == "insert")
    {
      //Get video parameters
      getline(cin,title);
      getline(cin,url);
      getline(cin,comment);
      cin >> length;
      cin >> rating;
      cin.ignore();

      //1. create video thing
      //video_array[video_num] = new Video(title,url,comment,length,rating);
      
      //2. insert video thing into list

      if(//logic)
      {
        cerr << "Could not insert video <" << title << ">, already in list.\n";
      }
    }
    else if(command == "print")
    {
      //use Video.print or something
    }
    else if(command == "length")
    {
      //get # of things in list
      else
      {
        cerr << 0 << "\n";  //list is empty
      }
    }
    else if(command == "lookup")
    {
      getline(cin,title);
      //check to see if title is in list
      if(//logic)
      {
        cerr << "Title <" << title << "> not in list.\n";
      }
    }
    else if(command == "remove")
    {
      getline(cin,title);
      //check to see if title is in list
      if(//logic)
      {
        cerr << "Title <" << title << "> not in list, could not delete.\n";
      }
    }
    else
    {
      cerr << <<"<" << command << "> is not a legal command, giving up.\n";
      return 1; 
    }
  }

    return 0;
}






