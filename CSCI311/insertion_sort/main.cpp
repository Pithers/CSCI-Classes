//Brandon Smith
//Insertion Sort
//Worksheet

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <time.h>

void insertion_sort(int* A,int size)
{
  int key;
  int j;
  for(int i = 1; i < size; i++)
  {
    key = A[i];
    j = i - 1;
    while(j >= 0 && A[j] > key)
    {
      A[j+1] = A[j];
      j = j - 1;
    }
    A[j+1] = key;
  }
}


int main(int argc, char* argv[])
{
  if(argc != 3)
  {
    std::cout << "incorrect number of arguments\n";
  }

  srand(time(NULL));
  int size = atoi(argv[1]); 
  int array[size];

  if(!strcmp(argv[2],"b"))
  {
    for(int i = 0; i < size; i++)
    {
      array[i] = i;
    }
  }
  else if(!strcmp(argv[2],"w"))
  {
    for(int i = 0; i < size; i++)
    {
      array[i] = size-i-1;
    }
  }
  else
  {
    for(int i = 0; i < size; i++)
    {
      array[i] = rand();
    }
  }

  insertion_sort(array,size);

  return 0;

}
