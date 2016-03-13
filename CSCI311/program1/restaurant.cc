/**
 * @file restaurant.cc 
 *
 * @brief
 *    Functional Definition of Restaurant.h
 *
 * @author Brandon Smith 
 * @date 1/27/16
 */

#include"restaurant.h"
#include<iostream>

/**
 * @brief reads input from user to create tables and parties
 */
void Restaurant::getInput()
{
  std::string type = "";
  std::string tableID;
  std::string name;
  int number;
  int time;

  while(type != "end")
  {
    std::cin >> type;

    if(type == "party")
    {
      std::cin >> number;
      std::cin >> name;
      std::cin >> time;
      waiting.append(new Party(name, number, time));
    }
    else if(type == "table")
    {
      std::cin >> tableID;
      std::cin >> number;
      std::cin >> name;
      available.append(new Table(tableID, number, name));
    }
  }
}

/**
 * @brief runs simulation to serve parties and tables
 */
void Restaurant::serveParties()
{
  int open = 1;
  int seated;

  while(open)
  { 
    //For every occupied table, decrement table's timer.
    //If timer = 0, party is finished and clean up table.
    for(Table* ptr = occupied.first(); ptr != nullptr;)
    {
      ptr->decrementTimer();                
      if(ptr->getTimer() <= 0)
      {
        std::cout << *((ptr->getParty())->getReservationName()) <<
          " finished at " << *(ptr->getTableID()) << "\n";
        ptr->clearTable();
        available.append(ptr);   //table goes back to being available
        ptr = occupied.remove(); //party finished, remove from occupied list
      }
      else
      {
        ptr = occupied.next();   //party not done, move to next occupied table
      }
    }

    //For every waiting Party
    for (Party* pptr = waiting.first(); pptr != nullptr;)
    {
      seated = 0;
      //For every available Table
      for(Table* tptr = available.first(); (tptr != nullptr) && seated == 0;)
      {
        //Create server if the current server hasn't been created
        if(servers.find(*(tptr->getServerName())) == servers.end())
        {
          servers.insert(std::pair<std::string,int>
              (*(tptr->getServerName()), 0));
        }
        if(pptr->getNumDiners() <= tptr->getNumSeats())
        {
          seated = 1;
          std::cout << *(pptr->getReservationName()) <<
            " seated at " << *(tptr->getTableID()) << "\n"; 
          tptr->seatParty(pptr); 
          tptr->setTimer(pptr->getTimeRequired());

          //add number of people to server's count
          servers.at(*(tptr->getServerName())) += pptr->getNumDiners(); 

          occupied.append(tptr); 
          tptr = available.remove(); //occupied, remove from available list
        }
        else
        {
          tptr = available.next(); //table not able to seat, goto next table 
        }
      }
      if(seated == 1)
      {
        pptr = waiting.remove(); //party seated, no longer waiting
      }
      else
      {
        pptr = waiting.next();   //party could not be seated, look at next party
      }
    }

    if(waiting.empty() && occupied.empty())
    {
     //print number of diners served by servers
     for(std::map<std::string,int>::iterator it = servers.begin();
         it != servers.end(); it++)
     {
        std::cout << it->first << " served " << it->second << "\n";
     }
      open = 0; //close restaurant
    }
  }
}

int main()
{
  Restaurant r;      //create restaurant
  r.getInput();      //get input for tables/parties
  r.serveParties();  //run simulation
  return 0;
}

