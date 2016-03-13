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
  int status;

  //Create list of videos
  Vlist video_list;

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

      //Create a new video and add it to the list. If the title already exists, throw an error
      status = video_list.insert(new Video(title, url, comment, length, rating));

      if(status != 0)
      {
        cerr << "Could not insert video <" << title << ">, already in list.\n";
      }
    }
    else if(command == "print")
    {
      video_list.print();
    }
    else if(command == "length")
    {
      //get # of things in list
      //else
      //{
        cerr << "0\n";  //list is empty
      //}
    }
    else if(command == "lookup")
    {
      getline(cin,title);
      //check to see if title is in list
      if(1 == 1)
      {
        cerr << "Title <" << title << "> not in list.\n";
      }
    }
    else if(command == "remove")
    {
      getline(cin,title);
      //check to see if title is in list
      if(1 == 1)
      {
        cerr << "Title <" << title << "> not in list, could not delete.\n";
      }
    }
    else
    {
      cerr << "<" << command << "> is not a legal command, giving up.\n";
      return 1; 
    }
  }

    return 0;
}






