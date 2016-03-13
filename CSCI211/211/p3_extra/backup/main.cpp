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
  //Declare Variables
  string command;
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
      video_list.print();                                                     //print out all videos in list
    }
    
    else if(command == "length")
    {
      cout << video_list.length() << "\n";                                    //print out length of video list
    }

    else if(command == "lookup")
    {
      getline(cin,title);                                                     //get title to lookup from user
      status = video_list.lookup(title);                                      //print video if the title is in the list
      if(status == 1)
      {
        cerr << "Title <" << title << "> not in list.\n";                     //err is the video is not in the list
      }
    }

    else if(command == "remove")
    {
      getline(cin,title);                                                     //get title to remove from user
      status = video_list.remove(title); 
      if(status == 1)
      {
        cerr << "Title <" << title << "> not in list, could not delete.\n";
      }
    }

    else if(command == "print_by_length")
    {
      video_list.print_by_length();
    }
 
    else if(command == "print_by_rating")
    {
      video_list.print_by_rating();
    }

    else if(command == "lookup_expression")
    {
      getline(cin, temp_string);
      status = video_list.lookup_expression(temp_string);
      if(status == 1)
      {
        cerr << "Regular expression <" << temp_string << "> does not match any titles in list.\n";
      }
    }

    else
    {
      cerr << "<" << command << "> is not a legal command, giving up.\n";     //err if command is not legal
      return 1; 
    }
  }

  return 0;
}






