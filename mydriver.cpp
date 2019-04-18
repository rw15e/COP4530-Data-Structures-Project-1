// Assignment 1 COP4530
// Ryan Winter
// 9/28/17 (Fall 2017)

#include <iostream>
#include <string>
#include "tlist.h"

using namespace std;


template <typename T> 
void PrintList(const TList<T>& L, string label) // Print function sourced from Professors example driver.cpp
{
   cout << label << " size is: " << L.GetSize() << "\n"
        << label << " = "; 
   L.Print(cout);
   cout << "\n\n";
}

int main(void)
{

TList<int> List1;	    // list of ints
TList<double> List2;    // list of doubles

cout << "Printing empty list of ints" << endl;
PrintList(List1, "List1");

cout << "Printing empty list of doubles" << endl;
PrintList(List2, "List2");

cout << "Insert 12 numbers to back of int list" << endl;
for (int i = 0; i < 12; i++)
	List1.InsertBack(i*2);
PrintList(List1, "List1");

cout << "Insert 12 numbers to front of int list" << endl;
for (int i = 0; i < 12; i++)
	List1.InsertFront(i);
PrintList(List1, "List1");

cout << "Remove 10 numbers from back of int list" << endl;
for (int i = 0; i < 10; i++)
	List1.RemoveBack();
PrintList(List1, "List1");

cout << "Remove 10 numbers from front of int list" << endl;
for (int i = 0; i < 10; i++)
	List1.RemoveFront();
PrintList(List1, "List1");

// start of double list testing
cout << "Insert 12 numbers to back of double list" << endl;
for (int i = 0; i < 12; i++)
	List2.InsertBack(i*2.0);
PrintList(List2, "List2");

cout << "Insert 12 numbers to front of double list" << endl;
for (int i = 0; i < 12; i++)
	List2.InsertFront(i);
PrintList(List2, "List2");

cout << "Remove 10 numbers from back of double list" << endl;
for (int i = 0; i < 10; i++)
	List2.RemoveBack();
PrintList(List2, "List2");

cout << "Remove 10 numbers from front of double list" << endl;
for (int i = 0; i < 10; i++)
	List2.RemoveFront();
PrintList(List2, "List2");


TListIterator<int> itrList1 = List1.GetIterator();  // List1 int iterator
TListIterator<double> itrList2 = List2.GetIterator();  // List2 double iterator

for (int i = 0; i < List1.GetSize(); i++) // move through whole list iteratively in forward direction
	itrList1.Next();
	
for (int i = 0; i < List1.GetSize(); i++) // move through whole list iteratively in backwards direciton
	itrList1.Previous();

for (int i = 0; i < 4; i++)
	List1.RemoveBack();
cout << "Clear List 1" << endl;
PrintList(List1, "List1");


List1.InsertFront(1);
List1.InsertFront(2);
cout << "Use InsertFront to add 2 numbers into List 1" << endl;
PrintList(List1, "List1");

List1.InsertFront(4);
cout << "Use InsertBack to add 1 number into List 1" << endl;
PrintList(List1, "List1");

List1.Insert(itrList1, 707);
cout << "Iteratively insert the number 707 into List 1" << endl;
PrintList(List1, "List1");

List1.RemoveFront();
cout << "Use RemoveFront to remove 1 number from List 1" << endl;
PrintList(List1, "List1");

List1.RemoveBack();
cout << "Use RemoveBack to remove 1 number from List 1" << endl;
PrintList(List1, "List1");


return 0;
}
