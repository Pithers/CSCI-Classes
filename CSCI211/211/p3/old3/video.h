//Brandon Smith
//CSCI 211
//Project 3 Linked List
//video.h

#ifndef VIDEO_H
#define VIDEO_H

#include<string>

class Video
{
  public:
    Video(std::string, std::string, std::string, float, int); //Constructor
    void print();
    bool compare_rating(Video *);
    bool compare_length(Video *);
    bool compare_title(Video *);
  private:
    std::string video_title;
    std::string video_url;
    std::string video_comment;
    float video_length;
    int video_rating;
};

#endif
