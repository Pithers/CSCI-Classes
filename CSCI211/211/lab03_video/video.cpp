//Brandon Smith
//CSCI 211
//Lab 3 Excercise 5
//video.cpp

#include<iostream>
#include"video.h"
using namespace std;

//Constructor
Video::Video(string title, string url, string comment, float length, int rating)
{
  video_title = title;
  video_url = url;
  video_comment = comment;
  video_length = length;
  video_rating = rating;
}

//Print function
void Video::print()
{
  cout << video_title << ", " << video_url << ", " << video_comment << ", " << video_length << ", ";
  for(int i = 0; i < video_rating; i++)
  {
    cout << "*";
  }
  cout << "\n";
}
