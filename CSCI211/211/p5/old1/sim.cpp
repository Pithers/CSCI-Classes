#include "pqueue.h"
#include "cust.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

void run_simulation(Pqueue&, int, int, ostream&);

int main(int argc, char *argv[])
{
  int checkers;
  int time_off;
 // int clock = 1;
  string buffer;
  string name;
  string alignment;
  string arrival;
  string items;

  Pqueue arrival_q;

  //Deal with commandline arguments
  //-------------------------------------------------------------------------
  if(argc != 5)
  {
    cerr << "Error: invalid number of command line arguments." << endl;
    exit(1);
  }

  checkers = atoi(argv[1]);
  if(checkers < 1)
  {
    cerr << "Error: invalid number of checkers specified." << endl;
    exit(1);
  }

  time_off = atoi(argv[2]);
  if(time_off < 0)
  {
    cerr << "Error: invalid checker break duration specified." << endl;
    exit(1);
  }

  ifstream ifile(argv[3], ios::in);
  if(!ifile)
  {
    cerr << "Error: could not open input file <" << argv[3] << ">." << endl;
    exit(1);
  }

  ofstream ofile(argv[4], ios::out);
  if(!ofile)
  {
    cerr << "Error: could not open output file <" << argv[4] << ">." << endl;
    exit(1);
  }
  //-------------------------------------------------------------------------------

  // As long as there is more input (not end of file), read a line
  while (getline(ifile, name, ' ') && getline(ifile, alignment, ' ') && getline(ifile, arrival, ' ') && getline(ifile, items, '\n'))
  {
    arrival_q.enqueue(new Cust(name, (alignment == "robber" ? 1:0), atoi(arrival.c_str()), atoi(items.c_str())), atoi(arrival.c_str()));
  }

  return 0;
}


void run_simulation(Pqueue &arrival_queue, int num_checkers, int break_time, ostream &os)
{



}











