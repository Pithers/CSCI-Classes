//Brandon Smith
//CSCI 211
//Lab 3 Excercise 5
//video.h

#ifndef VIDEO_H
#define VIDEO_H

#include<string>
using namespace std;

class Video
{
  public:
    Video(string, string, string, float, int);
    void print();
  private:
    string video_title;
    string video_url;
    string video_comment;
    float video_length;
    int video_rating;
};

#endif
