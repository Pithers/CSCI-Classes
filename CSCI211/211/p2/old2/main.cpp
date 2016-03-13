//Brandon Smith
//bpsmith
//CSCI 211
//Lab 3 Excercise 5
//Main.cpp

#include <iostream>
#include "video.h"
#include <string>
using namespace std;

#define MAX 100 

int main()
{
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
  Video *video_array[MAX];

  //Get sorting type
  getline(cin,sort);

  while(getline(cin,title)) //user specified videos
  {
    //Read in parameters
    getline(cin,url);
    getline(cin, comment);
    cin >> length;
    cin >> rating;
    cin.ignore();

    if(video_num >= (MAX-1))
    {
      cerr << "Too many videos, giving up.\n";
      return 1;
    }

    //Create Video in array
    video_array[video_num] = new Video(title,url,comment,length,rating);
    video_num++;
  }

  if(sort == "rating")
  {
  }
  else if(sort == "length")
  {
  }
  else if(sort == "title")
  {
  }
  else
  {
    cerr << sort << " is not a legal sorting method, giving up.\n";
    return 1;
  }

  for(int i = 0; i < video_num; i++)
  {
    video_array[i]->print();
    delete video_array[i];
  }

    return 0;
}






