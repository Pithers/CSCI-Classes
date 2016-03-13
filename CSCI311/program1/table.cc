/**
 * @file table.cc
 *
 * @brief
 *    Definition of a class to represent a restaurant table.
 *
 * @author Brandon Smith
 * @date 1/27/16
 */

#include"table.h"

/**
 * @brief Default Table constructor
 */
Table::Table()
{
  tableID = nullptr;
  numSeats = 0;
  serverName = nullptr;
  timer = 0;
  party = nullptr;
}

/**
 * @brief Table constructor
 */
Table::Table(const string& tableID, int numSeats, const string& serverName)
{
  this->tableID = new string(tableID);
  this->numSeats = numSeats;
  this->serverName = new string(serverName);
}

/*
 * @brief Table deconstructor
 */
Table::~Table()
{
  delete tableID;
  delete serverName;
}

/*
 * @brief setter for Table's Party pointer
 */
void Table::seatParty(const Party* newparty)
{
  party = newparty;
}

