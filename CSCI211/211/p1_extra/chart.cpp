//chart.cpp
//Smith, Brandon
//bpsmith
//Project 1
//Extra Credit 

#include<iostream>
using namespace std;

int find_max(int values[], int size);
void print_up(int, int, int values[]);
void print_right(int, int, int values[]);
void print_left(int, int, int values[]);
void print_down(int, int, int values[]);

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

  //Find the number of rows
  rows = find_max(values, col);

  //Print out the chart
  print_up(rows, col, values);
  cout << endl;
  print_down(rows,col, values);
  cout << endl;
  print_right(rows,col, values);
  cout << endl;
  print_left(rows,col, values);

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

//Prints out array up 
void print_up(int row, int col, int values[])
{
  for(int i = row; i > 0; i--) //for each row
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
  return;
}

//Prints out array right
void print_right(int row, int col, int values[])
{
  for(int i = 0; i < col; i++) //for each column
  {
    for (int j = 0; j < row; j++) //for each row 
    {
      if(values[i] > j)
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
  return;
}

//Print out array left 
void print_left(int row, int col, int values[])
{
  for(int i = col-1; i >= 0 ; i--) //for each column 
  {
    for (int j = row; j > 0; j--) //for each row
    {
      if(values[i] >= j)
      {
        cout << "*"; }
      else
      {
        cout << " ";
      }
    }
    cout << "\n";
  }
  return;
}

//Prints out array down 
void print_down(int row, int col, int values[])
{
  for(int i = 0; i < row; i++) //for each row
  {
    for (int j = col -1; j >= 0 ; j--) //for each column
    {
      if(values[j] > i)
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
  return;
}

