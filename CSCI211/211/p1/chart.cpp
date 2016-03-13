//chart.cpp
//Smith, Brandon
//bpsmith
//Project 1

#include<iostream>
using namespace std;

int find_max(int values[], int size);

int main()
{
  //Define Variables
  const int MAX = 100;
  int values[MAX];
  int col;
  int rows;

  //Read in input from and decide on size of array (# of columns)
  for(int i = 0; i < MAX; i++)
  {
    cin >> values[i];
    if(values[i] <= 0)
    {
      col = i;
      break;
    }
  }

  // Find the number of rows
  rows = find_max(values, col);

  //Print out the chart

  for(int i = rows; i > 0; i--) //for each row
  {
    for (int j = 0; j < col; j++) //for each column
    {
      if(values[j] >= i)
      {
        cout << "*";
      }
      else
      {
        cout << " ";
      }
    }
    cout << "\n";
  }


  return 0;
}

//Function that finds the largest integer in an integer array
int find_max(int values[], int size)
{
  int largest = 0;
  for(int i = 0; i < size;  i++)
  {
    if(values[i] > largest)
    {
      largest = values[i];
    }
  }
  return largest;
}
