/**
 * @file party.cc
 *
 * @brief
 *    Definition of party.h
 *
 * @author Brandon Smith
 * @date 1/27/16
 */

#include"party.h"

/**
 * @brief Default party constructor
 */
Party::Party()
{
  reservationName = nullptr;
  numDiners = 0;
  timeRequired = 0;
}

/**
 * @brief Party constructor
 */
Party::Party(const string& reservationName, int numDiners, int timeRequired)
{
  this->reservationName = new string(reservationName);
  this->timeRequired = timeRequired;
  this->numDiners = numDiners;
}

/**
 * @brief Party deconstructor
 */
Party::~Party()
{
  delete reservationName;
}

