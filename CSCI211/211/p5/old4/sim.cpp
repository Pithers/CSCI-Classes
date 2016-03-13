#include "pqueue.h"
#include "cust.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
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
  string buffer;
  string name;
  string alignment;
  string arrival;
  string items;
  char* endptr;

  Pqueue arrival_q;

  //Deal with commandline arguments //-------------------------------------------------------------------------
  if(argc != 5)
  {
    cerr << "Error: invalid number of command line arguments." << endl;
    exit(1);
  }

  checkers = strtol(argv[1], &endptr, 10);                          //convert argv[1] to integer, noting if it's invalid
  if(!*argv[1] || *endptr || atoi(argv[1]) < 1 )
  {
    cerr << "Error: invalid number of checkers specified." << endl;
    exit(1);
  }

  time_off = strtol(argv[2], &endptr, 10);                          //convert argv[2] to integer, noting if it's invalid
  if(!*argv[1] || *endptr || atoi(argv[2]) < 0)
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
  Pqueue checker_q;

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
    //----Entering Store----
    while(!arrival_queue.empty() && arrival_queue.get_priority_of_first() == clock)
    {
      temp_customer = arrival_queue.dequeue();                  //get customer to enter store
      temp_customer->print_entered(os, clock);                  //print that customer entered store
      customer_time = clock + temp_customer->get_items()*2;     //calculate when customer will be done
      shopping_q.enqueue(temp_customer, customer_time);         //que up customers by the time they are done shopping
    }

    //----Shopping----
    while(!shopping_q.empty() && shopping_q.get_priority_of_first() == clock)
    {
      temp_customer = shopping_q.dequeue();                     //get customer to enter checker's line
      temp_customer->print_finish_shop(os, clock);              //print that customer finished shopping
      checker_q.enqueue(temp_customer, 0);                      //place customer on checker q with no priority
    }

    //----See if any Checkers are done----
    for(int i = 0; i < num_checkers; i++)
    {
      if(check_array[i].current_customer != NULL && check_array[i].time_finished <= clock)
      {
        if(check_array[i].current_customer->get_alignment())    //if person is a robber
        {
          check_array[i].current_customer->print_finish_cs(os, clock, i, check_array[i].money);
          check_array[i].money = 0;                            //checker loses all money
          check_array[i].break_left = clock + break_time;
        }
        else                                                    //if person is a customer 
        {
          check_array[i].current_customer->print_finish_cs(os, clock, i, 0);
          check_array[i].money += check_array[i].current_customer->get_items()*3;       //customer gets 3*number of items
        }
        
        temp_customer = check_array[i].current_customer; 
        check_array[i].current_customer = NULL;
        //delete temp_customer;
        num_customers--;                                        //a customer has been served and leaves the store
      }
    }

    //----Finding Available Checker----
    //while(!checker_q.empty()) 
    //{
      for(int i = 0; i < num_checkers; i++)
      {
        if(check_array[i].current_customer == NULL && check_array[i].break_left <= clock && !checker_q.empty())    //if checker is available
        {
          temp_customer = checker_q.dequeue();                                //get cusotomer waiting in line
          check_array[i].current_customer = temp_customer;                    //assign that checker the customer
          if(temp_customer->get_alignment())
          {
            customer_time = clock + 4;                                        //robbers take clock + 4
          }
          else
          {
            customer_time = clock + temp_customer->get_items();               //customers take *1 every item
          }
          check_array[i].time_finished = customer_time;                       //set the time the checker will be finished at
          temp_customer->print_start_cs(os, clock, i);
        }
      }
    //}
  }
  for(int i = 0; i < num_checkers; i++)
  {
    os << "registers[" << i << "] = $" << check_array[i].money << endl;
  }
  os << "time = " << clock << endl;
}





