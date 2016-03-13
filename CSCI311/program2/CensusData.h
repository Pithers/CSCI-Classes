/**
 * @file CensusData.h   Declaration of the CensusData class.
 *
 * @author Judy Challinger and Brandon Smith
 * @date 2/22/13
 */

#ifndef CSCI_311_CENSUSDATA_H
#define CSCI_311_CENSUSDATA_H

#include <vector>
#include <random>
using std::ifstream;
using std::string;
using std::vector;

class CensusData {
public:
   static const int POPULATION = 0;       // type of sort
   static const int NAME = 1;
   ~CensusData();
   void initialize(ifstream&);            // reads in data
   int getSize(){return data.size();}
   void print();                          // prints out data
   void insertionSort(int);               // sorts data using insertionSort
   void mergeSort(int);                   // sorts data using mergeSort
   void quickSort(int);                   // sorts data using quickSort
private:
   class Record {                         // declaration of a Record
   public:
      string* city;
      string* state;
      int population;
      Record(string&, string&, int);
      ~Record();
   };
   vector<Record*> data;                  // data storage

   //Private helper functions 
   void mergeSortHelp(int, int, int);     
   void merge(int, int, int, int);        
   void quickSortHelp(int, int, int);
   int randomPartition(int, int, int);
   int partition(int, int, int);

   //Random Generator
   std::default_random_engine gen;
};

#endif // CSCI_311_CENSUSDATA_H
