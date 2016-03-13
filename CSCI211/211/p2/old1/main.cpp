//Brandon Smith
//bpsmith
//CSCI 211
//Lab 3 Excercise 5
//Main.cpp

#include <iostream>
#include "video.h"
#include <string>
using namespace std;

#define MAX 5

int main()
{
  //Define variables
  string sort;
  string title;
  string url;
  string comment;
  float length;
  int rating;
  int video_num = 0;

  //Object pointer array
  Video *video_array[MAX];

  //Get sorting type
  getline(cin,sort);
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
    cerr << sort << " is not a legal sorting method, giving up." << "\n";
    return 1;
  }

  while(video_num < MAX) //user specified videos
  {
    //Read in parameters
    getline(cin,title);
    getline(cin,url);
    getline(cin, comment);
    cin >> length;
    cin >> rating;
    cin.ignore();

    //Create Video in array
    video_array[video_num] = new Video(title,url,comment,length,rating);
    video_num++;
  }

  for(int i = 0; i < MAX; i++)
  {
    video_array[i]->print();
  }

    return 0;
}






