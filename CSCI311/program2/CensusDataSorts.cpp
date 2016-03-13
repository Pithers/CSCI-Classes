/**
 * @file CensusDataSorts.cpp   Sort functions for census population data.
 * 
 * @brief
 *    Implements several different types of sorts. Data can be sorted
 * by population or by name of town. This file contains all of the sorting
 * functions and their helpers. Sorting algorithim based of ones from (Cormen)
 *
 * @reference Cormen, Thomas H. Introduction To Algorithms. Cambridge, Mass.:
 *                     MIT Press, 2009. Print.
 * 
 * @author Judy Challinger and Brandon Smith
 * @date 2/22/13
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include "CensusData.h"

/**
 * CensusData::insertionSort.
 *
 * Sorts the private census data vector by input type (name or population). 
 *
 * @param int type.
 * type == 0 sorts by population, type == 1 sorts by name.
 */
void CensusData::insertionSort(int type)
{
  if(type == 0) //Sort based on population
  {
    Record* key;
    int i;

    //For every element...
    for(int j = 1; j < getSize(); j++)
    {
      key = data.at(j); //Get key
      i = j - 1;

      //Insert current data into sorted sequence if data less than key
      while(i >= 0 && data.at(i)->population > key->population)
      {
        data.at(i+1) = data.at(i);
        i = i - 1;
      }
      data.at(i+1) = key;
    }
  }
  else          //Sort based on name, similar to above
  {
    Record* key;
    int i;
    for(int j = 1; j < getSize(); j++)
    {
      key = data.at(j);
      i = j - 1; 
      while(i >= 0 && (*(data.at(i)->city) > *(key->city)))  
      {
        data.at(i+1) = data.at(i);
        i = i - 1;
      }
      data.at(i+1) = key;
    }
  }
}

/**
 * CensusData::mergeSort.
 *
 * Public function to call merge sort, calls private helper function
 * to actually sort data.
 *
 * @param int type.
 * type == 0 sorts by population, type == 1 sorts by name.
 */
void CensusData::mergeSort(int type)
{
  mergeSortHelp(type, 0, getSize()-1);
}

/**
 * CensusData::mergeSortHelp.
 *
 * Private helper function that recursively calls to run
 * the mergesort algorithim.
 *
 * @param int type, int p, int r
 * type == 0 sorts by population, type == 1 sorts by name.
 * p is the starting index of the data vector to sort
 * r is the ending index of the data vector to sort
 */
void CensusData::mergeSortHelp(int type, int p, int r)
{
  int q;
  if(p < r)
  {
    q = std::floor((p+r)/2);        //get middle of vector
    mergeSortHelp(type, p, q);      //merge sort lower half of vector 
    mergeSortHelp(type, q + 1, r);  //merge sort upper half of vector
    merge(type, p, q, r);           //call merge on both halves
  }
}

/**
 * CensusData::merge.
 *
 * Merges and sorts sub-vectors back into original data vector
 * according to the merge sort algorithim.
 *
 * @param int type, int p, int q, int r.
 * type == 0 sorts by population, type == 1 sorts by name.
 * p is the starting index of the data vector to merge.
 * q is the middle index of the data vector to merge.
 * r is the ending index of the data vector to merge.
 */
void CensusData::merge(int type, int p, int q, int r)
{
  int n1 = q - p + 1; //Calculate size of left subvector
  int n2 = r - q;     //Calculate size of right subvector
  int i;
  int j;
  int k;
  vector<Record*> L(n1);  //Create left subvector
  vector<Record*> R(n2);  //Create right subvector

  for(i = 0; i < n1; i++)     //Fill up created left subvector
  {
    L.at(i) = data.at(p + i);
  }
  for(j = 0; j < n2; j++)     //Fill up created right subvector
  {
    R.at(j) = data.at(q + j + 1);
  }

  i = 0;
  j = 0;

  if(type ==  0) //Sort based on population
  {
    //Compare left and right data values and change orriginal vector 
    for(k = p; k < r && i < n1 && j < n2; k++)
    {
      if(L.at(i)->population < R.at(j)->population)
      {
        data.at(k) = L.at(i);
        i++;
      }
      else
      {
        data.at(k) = R.at(j);
        j++;
      }
    }
  }
  else           //Sort based on name (similar to above)
  { 
    for(k = p; k < r && i < n1 && j < n2; k++)
    {
      if(*(L.at(i)->city) <= *(R.at(j)->city))
      {
        data.at(k) = L.at(i);
        i++;
      }
      else
      {
        data.at(k) = R.at(j);
        j++;
      }
    }
  }

  //Verify that entire left and right subvectors have been sorted through
  //If not, add remaining data to original vector
  while(i < n1)
  {
    data.at(k) = L.at(i);
    i++;
    k++;
  }
  while(j < n2)
  {
    data.at(k) = R.at(j);
    j++;
    k++;
  }
}

/**
 * CensusData::quickSort.
 *
 * Public function that calls private helper function to use
 * the quicksort algorithim to sort the private data vector.
 *
 * @param int type.
 * type == 0 to sort by population, type == 1 to sort by name.
 */
void CensusData::quickSort(int type)
{
  gen.seed(time(0)); //seed random before calling sort
  quickSortHelp(type, 0, getSize()-1);
}

/**
 * CensusData::quickSortHelp.
 *
 * Private helper function that is called recursively in order
 * to run the quicksort algorithim.
 *
 * @param int type, int p, int r.
 * type == 0 to sort by population, type == 1 to sort by name.
 * int p = starting index of vector.
 * int r = ending index of vector.
 */
void CensusData::quickSortHelp(int type, int p, int r)
{
  int q;
  if(p < r)
  {
    q = randomPartition(type, p, r);  //sort a randomized partition
    quickSortHelp(type, p, q - 1);    //quicksort the lower half of vector
    quickSortHelp(type, q + 1, r);    //quicksort the upper half of vector
  }
}

/**
 * CensusData::randomPartition.
 *
 * Changes the current pivot with a random index and calls the
 * partition function.
 *
 * @param int type, int p, int r.
 * type == 0 to sort by population, type == 1 to sort by name.
 * int p = starting index of vector.
 * int r = ending index of vector.
 */
int CensusData::randomPartition(int type, int p, int r)
{
  //Get a random number between p and r
  std::uniform_real_distribution<float> distribution(p, r);
  int i = int(distribution(gen));
  std::swap(data[r], data[i]);    //Swap current pivot with random index
  return partition(type, p, r);
}

/**
 * CensusData::partition.
 *
 * Partitions the private data vector based on population or city name
 * accoreding to the quicksort algorithim.
 *
 * @param int type, int p, int r.
 * type == 0 to sort by population, type == 1 to sort by name.
 * int p = starting index of vector.
 * int r = ending index of vector.
 */
int CensusData::partition(int type, int p, int r)
{
  int x = data.at(r)->population; //grab population of pivot
  string y = *(data.at(r)->city); //grab city name of pivot
  int i = p - 1;

  //For partition size compare pivot with data 
  for(int j = p; j < r; j++)
  {
    //if the current data is less than the pivot
    //increment the index i and swap the data
    //at j with the data at i
    if(type == 0 && data.at(j)->population <= x)
    {
       i++;
       std::swap(data[i], data[j]);     }
    else if(type == 1 && *(data.at(j)->city) <= y)
    {
        i++;
        std::swap(data[i], data[j]);
    }
  }
  std::swap(data[i+1], data[r]);
  return i + 1;
}


