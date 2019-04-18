// Assignment 1 COP4530
// Ryan Winter
// 9/28/17 (Fall 2017)

#include <iostream>
#include <utility>
#include "tnode.h"

// Declaration of class TList

template <typename T>
class TList
{
   friend class TListIterator<T>;


public:
   TList();				// create empty linked list
   TList(T val, int num);		// create list with num copies of val
   ~TList();				// destructor
   TList(const TList& L);		// copy constructor
   TList operator=(const TList& L);	// copy assignment operator
   TList(TList && L);			// move constructor
   TList operator=(TList && L);		// move assignment operator

   bool IsEmpty() const;		// checks to see whether list is empty
   void Clear();			// clear out list, reset to empty
   int GetSize() const;			// return the size of the list

   void InsertFront(const T& d);	// insert data d as first element
   void InsertBack(const T& d);		// insert data d as last element
   void RemoveFront();			// remove first element of list
   void RemoveBack();			// remove last element of list

   
   T& GetFirst() const;			// return first element of list
   T& GetLast() const;			// return last element of list

   TListIterator<T> GetIterator() const;  // return iterator to first item
   TListIterator<T> GetIteratorEnd() const; // return iterator to last item

   // insert data element d just before item at pos position
   void Insert(TListIterator<T> pos, const T& d);

   // remove data item at position pos. Return iterator to the item 
   //  that comes after the one being deleted
   TListIterator<T> Remove(TListIterator<T> pos);

   // print list contents in order, separated by given delimiter
   void Print(std::ostream& os, char delim = ' ') const;

private:
   Node<T>* first;		// pointer to first node in list
   Node<T>* last;		// pointer to last node in list
   int size;			// number of nodes in the list
   static T dummy;		// dummy object, for empty list data returns
   				//  assuming type T has default construction
   void setEmpty(); 		// set list to empty

};

template <typename T>
T TList<T>::dummy;		// initialization of static member

// stand-alone function for concatenating two TList objects
template <typename T>
TList<T> operator+(const TList<T>& t1, const TList<T>& t2)
{
   TListIterator<T> itr = t2.GetIterator();     //iterator for going through second list

   TList<T> result = t1;                        //use assignment for copying the first list

   if (t2.GetSize() == 0) return result;        //if t2 is empty, we can return immediately

   for (int i = 0; i < t2.GetSize(); i++)       //if not, copy remaining elements from the second list
   {
      result.InsertBack(itr.GetData());
      itr.Next();
   }

   return result;
}



// Declaration of class TListIterator

template <typename T>
class TListIterator
{
   friend class TList<T>;

public:
   TListIterator();			// default constructor
   bool HasNext() const;		// next item available?
   bool HasPrevious() const;		// previous item available?
   TListIterator<T> Next();		// advance to next item
   TListIterator<T> Previous();		// move to previous item
   T& GetData() const;			// return data element of current node

private:
   Node<T>* ptr;		// pointer to current list item
};

#include "tlist.hpp"		// bring in definition file here


