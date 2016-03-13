#include "pqueue.h"
#include "cust.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

void run_simulation(Pqueue&, int, int, ostream&);

struct Checker {
  Cust* current_customer = NULL;
  int money = 100;
  int break_left = 0;
  int time_finished = 0;
};

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

  //Deal with commandline arguments //-------------------------------------------------------------------------
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

  run_simulation(arrival_q, checkers, time_off, ofile);

  return 0;
}

void run_simulation(Pqueue &arrival_queue, int num_checkers, int break_time, ostream &os)
{
  int clock = 0;
  int customer_time = 0;
  int num_customers = arrival_queue.length();           //get number of customers
  Checker *check_array = new Checker[num_checkers];     //create array of checkers
  Cust* temp_customer = NULL;

  Pqueue shopping_q;

  //Initialize all of the checkers
  for(int i = 0; i < num_checkers; i++)
  {
    check_array[i].money = 100;
    check_array[i].break_left = 0;
    check_array[i].time_finished = 0;
    check_array[i].current_customer = NULL;
  }

  //start simulation
  for(clock = 1; num_customers > 0; clock++)
  {
    while(!arrival_queue.empty() && arrival_queue.get_priority_of_first() == clock)
    {
      temp_customer = arrival_queue.dequeue();                  //get customer to enter store
      temp_customer->print_entered(os, clock);
      
      customer_time = 2*4;

      shopping_q.enqueue(temp_customer, customer_time);         //que up customers by the time they are done shopping

      num_customers--;
    }
  }
}











