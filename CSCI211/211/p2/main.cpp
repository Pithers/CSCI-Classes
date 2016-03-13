//Brandon Smith
//bpsmith
//CSCI 211
//Lab 3 Excercise 5
//Main.cpp

#include"video.h"
#include<iostream>
#include<string>
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

  if((sort != "rating") && (sort != "length") && (sort != "title"))
  {
    cerr << sort << " is not a legal sorting method, giving up." << endl;
    return 1;
  }

  while(getline(cin,title)) //user specified videos
  {
    //Read in parameters
    getline(cin,url);
    getline(cin, comment);
    cin >> length;
    cin >> rating;
    cin.ignore();

    if(video_num >= MAX)
    {
      cerr << "Too many videos, giving up." << endl;
      return 1;
    }

    //Create Video in array
    video_array[video_num] = new Video(title,url,comment,length,rating);
    video_num++;
  }

  if(sort == "rating")
  {
    for(int last = video_num - 1; last > 0; last--)
      for(int cur = 0; cur < last; cur++)
        if(video_array[cur]->compare_rating(video_array[cur+1]))
          swap(video_array[cur], video_array[cur+1]);
  }
  else if(sort == "length")
  {
    for(int last = video_num - 1; last > 0; last--)
      for(int cur = 0; cur < last; cur++)
        if(video_array[cur]->compare_length(video_array[cur+1]))
          swap(video_array[cur], video_array[cur+1]);
  }
  else if(sort == "title")
  {
    for(int last = video_num - 1; last > 0; last--)
      for(int cur = 0; cur < last; cur++)
        if(video_array[cur]->compare_title(video_array[cur+1]))
          swap(video_array[cur], video_array[cur+1]);
  }

  for(int i = 0; i < video_num; i++)
  {
    video_array[i]->print();
    delete video_array[i];
  }

    return 0;
}






