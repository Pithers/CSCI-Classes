//Brandon Smith
//CSCI 580
//Fall 2016
//Project 2
//main.cpp

#include<fstream>
#include<stdlib.h>
#include<string>
#include<sstream>
#include"ann.h"

int main(int argc, char* argv[])
{
  if(argc != 8)
  {
    cout << "wrong number of arguments" << endl;
    return -1;
  }

  //Variables
  vector<vector<long double> > we;      //weights matrix 
  vector<vector<long double> > in;      //train input vector
  vector<vector<long double> > test_in; //test input vector
  vector<long double> test_out;         //test output vector
  vector<long double> out;              //train output vector
  vector<int> nodes;
  string temp;
  string line;
  long double temp_int;
  int k = strtol(argv[7], NULL, 10);    //iterations 
  int layers = 0;
  int i = 0;
  int j = 0;
  int sum = 0;

  //Input files
  ifstream train_input;
  ifstream train_output;
  ifstream test_input;
  ifstream test_output;
  ifstream structure;
  ifstream weights;

  //Open files
  train_input.open(argv[1]);
  train_output.open(argv[2]);
  test_input.open(argv[3]);
  test_output.open(argv[4]);
  structure.open(argv[5]);
  weights.open(argv[6]);

  //Check to see files were opened
  if(!train_input || !train_output || !test_input ||
     !test_output || !structure || !weights)
  {
    cout << "Error: could not open file" << endl;
    return -1;
  }

  //===============Structure====================
  while(getline(structure, temp))
  {
    nodes.push_back(strtol(temp.c_str(), NULL, 10));
    sum++;
  }
  layers = sum;

  //===============Weights======================
  //Count total possible nodes
  sum = 0;
  for(i = 0; i < (int)nodes.size(); i++)
  {
    sum = sum + nodes.at(i);
  }

  //Set up 2d vector of node weights
  //Each node gets a list
  we.resize(sum - nodes.at(i - 1) + 1);
  we.at(0).resize(sum);
  sum = nodes.at(0);
  for(i = 0, j = 0; i < (int)we.size(); i++)
  {
    if(i >= sum)
    {
      j++;
      sum += nodes.at(j);
    }
    if(j < (int)nodes.size() - 1)
    {
      we.at(i+1).resize(nodes[j+1]);
    }
  }

  //Set initial dummy weights
  for(i = 0; i < (int)we[0].size(); i++)
  {
    we.at(0).at(i) = 0.01;
  }

  //Get weights from file
  i = 0;
  while(getline(weights, line))
  {
    stringstream s(line); 
    j = 0;

    while(s >> temp_int)
    {
      we.at(i+1).at(j) = temp_int;
      j++;
    }
    i++;
  }

  //===========Train Input=====================
  vector<long double> v_temp;
  i = 0;
  while(getline(train_input, line))
  {
    stringstream s(line); 
    in.push_back(v_temp);
    while(s >> temp_int)
    {
      in.at(i).push_back(temp_int);
    }
    i++;
  }

  //============Train Output==================
  while(getline(train_output, temp))
  {
    out.push_back(strtol(temp.c_str(), NULL, 10));
  }

  //===========Test Input====================
  i = 0;
  while(getline(test_input, line))
  {
    stringstream s(line); 
    test_in.push_back(v_temp);
    while(s >> temp_int)
    {
      test_in.at(i).push_back(temp_int);
    }
    i++;
  }

  //===========Test Output==================
  while(getline(test_output, temp))
  {
    test_out.push_back(strtol(temp.c_str(), NULL, 10));
  }

  //Create Ann object and run simulation
  Ann A(we, in, test_in, out, test_out, nodes, k, layers);
  A.run();

  //Close files
  train_input.close();
  train_output.close();
  test_input.close();
  test_output.close();
  structure.close();
  weights.close();

  return 0;
}





