#include <cassert>
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
using namespace std;

/*Type delcarations - NO MEMORY ALLOCATED (EVEN STATICALLY)*/
struct emprec	/*Employee record with two fields*/
{
  int id;
  float salary;
};
typedef emprec * emprecptr; // Employee record pointer type
typedef emprecptr * indexarr; // Pointer to a dynamic array of employee record pointers

int main ()
{
  void readdata (indexarr &, int &);
  void printdata (indexarr, int);
  void copyindex (indexarr, indexarr &, int);
  void sortbyID (indexarr, int);
  void sortbySalary (indexarr, int);
  void deallocate (indexarr &, int &);
  indexarr DBindex, IDindex, Salaryindex;
  int dbsize;
  char temp;

  //Original Data
  readdata (DBindex, dbsize);
  cout << "Original data:" << endl;
  printdata (DBindex, dbsize);

  //Sort by ID
  copyindex (DBindex, IDindex, dbsize);
  sortbyID (IDindex, dbsize);
  cout << "Data sorted by the ID:" << endl;
  printdata (IDindex, dbsize);

  //Sort by salary
  copyindex (DBindex, Salaryindex, dbsize);
  sortbySalary (Salaryindex, dbsize);
  cout << "Data sorted by the salary:" << endl;
  printdata (Salaryindex, dbsize);

  //Free up memory
  deallocate (DBindex, dbsize);

  return 0;
};

/*Skip over white space to end of file or the next non-white space character*/
void eat_white (ifstream & in)
{
  while ((in.peek()!=EOF) && isspace(in.peek())) in.ignore();
};

/* Base is expanded or shrunk into a new (dynamic) indexarr of size */
void resize (indexarr & Base, int OLDSIZE, int NEWSIZE)
{
  indexarr newptrs = new emprecptr[NEWSIZE];
  for(int i=0;i<OLDSIZE;i++)
    {
      newptrs[i] = Base[i];
    }
  delete Base;
  Base = newptrs;
}

/* ptrs points to a dynamic pointer array of the right size based on the input read in from the data file. All the elements of the dynamic array are fikled with pointers to dynamically allocated employee records, which in turn are filled with input data */
void readdata (indexarr & ptrs, int & size)
{
  {
  ifstream fin("p1data.txt");
  ptrs = new emprecptr[10]; //creates a new array on the heap with a memory size of 10.
  size = 0;
  int a,b;
  while(fin>>a>>b) //reads both integers in the file, assigning them to a and b respectively.
    {
      emprec* record  = new emprec; //creates a new emprec pointer on the heap
      record->id = a;
      record->salary = b; //assigns a and b to the pointer "record"
      
      ptrs[size] = record; //adds the id and salary information contained in "record" into the array.
      size++;
    }

  fin.close();
  }
  
  void resize (indexarr &, int, int);
  
 
};

/* The data in rec printed out */ 
void printrec (emprec rec)
{
  cout << rec.id << ' ' << rec.salary << endl;
};

/* The first "size" elements of the array pointed at by ptrs are employee records containing data and this information is printed out in the order pointed at */
void printdata (indexarr ptrs, int size)
{
  void printrec (emprec);
  for (int i=0; i<size; i++)
    {
      printrec(*ptrs[i]);
    }

};

/* Copy points to a newly allocated dynamic array of pointers (with teh size elements), and the elements of this array are copies of the first size element of orig  */
void copyindex (indexarr orig, indexarr & copy, int size)
{
  copy = new emprecptr[size]; //creates the new array
  for (int i=0;i<size;i++) 
    {
      copy[i] = orig[i]; //copies the original array into the new array
    }
  
};

/* A value k is returned such that, for i ranging from first to last, the relation ptrs[k]->id <= ptrs[i]->id holds */
int selectsmallestID (indexarr ptrs, int first, int last)
{
  int k,result;
  result = first;
  for(k=first+1;k<=last;k++)
    {
      if(ptrs[k]->id<ptrs[result]->id) //Goes through the ID component of the array to find the smallest value.
	{
	  result = k;
	}
    }
  return result;
};

/* For i ranging from 1 to size-2, the relation ptrs[i]->id <= ptrs[i+1]->id holds. Also, the employee records themselves are not disturbed/moved around */
void sortbyID (indexarr ptrs, int size)
{
  int selectsmallestID (indexarr, int, int);
  int i, smallindex;
  for(i=0;i<=size-2;i++)
    {
      smallindex = selectsmallestID(ptrs,i,size-1); 
      swap(ptrs[i],ptrs[smallindex]);
    }
};

/* A value k is returned such that, for i ranging from first to last, the relation ptrs[k]->salary <= ptrs[i]->salary holds */
int selectsmallestSalary (indexarr ptrs, int first, int last)
{
  int k, result;
  result = first;
  for(k=first+1;k<=last;k++)
    {
      if(ptrs[k]->salary<ptrs[result]->salary) //Goes through the salary component of the array to find the smallest value.
	{
	  result = k;
	}
    }
  return result;
};

/* For i ranging from 1 to size-2, the relation ptrs[i]->salary <= ptrs[i+1]->salary holds. */
void sortbySalary (indexarr ptrs, int size)
{
  int selectsmallestSalary (indexarr, int, int);
  int i, smallindex;
  for(i=0;i<=size-2;i++)
    {
      smallindex = selectsmallestSalary(ptrs,i,size-1);
      swap(ptrs[i],ptrs[smallindex]);
    }
};

/* Ptrs points to a dynamic pointer array. The "size" elements of the dynamic array, filled with pointers to dynamically allocated employee records, are now deallocated, with ptrs reset to NULL and the size reset to 0. */
void deallocate (indexarr & ptrs, int & size)
{
  for (int i=0; i<size; i++) delete (ptrs[i]);
  delete ptrs;
  ptrs = NULL;
  size = 0;
};
