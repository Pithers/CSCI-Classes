//Brandon Smith
//CSCI 211
//Project 3 Linked List
//video.cpp

#include"video.h"
#include<iostream>
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

string Video::get_title()
{
  return video_title;
}

float Video::get_length()
{
  return video_length;
}

int Video::get_rating()
{
  return video_rating;
}

//Compare two video lengths
bool Video::compare_length(Video *other)
{
  return video_length > other->video_length; //Return 1 if video has a higer length than compared video
}

//Compare two video ratings
bool Video::compare_rating(Video *other)
{
  return video_rating < other->video_rating; //Return 1 if video has lower rating than compared video
}

//Compare two video titles
bool Video::compare_title(Video *other)
{
  return video_title > other->video_title; //Return 1 if video alphabetically comes after compared video
}
