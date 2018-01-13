//Brandon Smith
//CSCI 580
//Fall 2016
//Project 2
//ann.h

#ifndef ANN_H
#define ANN_H

//Includes
#include<vector>
#include<iomanip>
#include<iostream>
#include<math.h>
using namespace std;

//Artificial Neural Network Class
class Ann
{
  public:
    //Constructor
    Ann(vector<vector<long double> >&,
        vector<vector<long double> >&,
        vector<vector<long double> >&,
        vector<long double>&,
        vector<long double>&,
        vector<int> &,
        int&, int&);

    //Functions
    void run();

  private:
    //Member data
    vector<vector<long double> > weights;
    vector<vector<long double> > input;
    vector<vector<long double> > c_in;
    vector<vector<long double> > output;
    vector<vector<long double> > out_train;
    vector<long double> c_out;
    vector<long double> output_class;
    vector<long double> a;
    vector<long double> inp;
    vector<long double> error;
    vector<long double> y;
    vector<int> structure;
    vector<int> digits;
    long double alpha;
    int iter;
    int layers;
    int num_nodes;

    //Functions
    void output_classification();
    void calculate_accuracy();
    void input_classification();
    void update_weights();
    void display_weights();
};

#endif
