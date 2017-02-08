#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include "List.h"
#include <iostream>
using namespace std;

template <class item_t>
class ArrayList: public List<item_t>
{
  protected:
   item_t* items;
   int size;
   int capacity;
   
  public:
   //Creates an empty list with capacity 10
   ArrayList();
   //Creates a list with the given capacity
   ArrayList(int capacity);
   virtual ~ArrayList();

   //Pushes item to the back of the list
   virtual void pushBack(const item_t& item);   
   //Removes, but does not return, the last item
   virtual void popBack();
   //Returns a reference to the last item (does not remove it).
   virtual const item_t& getBack() const;
   
   //Pushes item to the front of the list
   virtual void pushFront(const item_t& item);
   //Removes, but does not return, the first item
   virtual void popFront();
   //Returns a reference to the first item (does not remove it).
   virtual const item_t& getFront() const;

   //Returns a reference to the item at the given index
   virtual const item_t& getItem(int index) const;
   //Sets the item at the given index
   virtual void setItem(int index, const item_t& item);

   //Inserts the given item at the given index
   //(items at index or beyond shift up one position)
   //Inserting just past the last element (i.e. position
   //size) shoud be equivalent to pushBack.
   virtual void insert(int index, const item_t& item);
   //Removes the item at the given index
   //(items beyond index shift down one position)
   virtual void remove(int index);

   //Returns the number of items in the list
   virtual int getSize() const;
   //Returns true if the list is empty (false otherwise)
   virtual bool isEmpty() const;
   //Returns the size of the array that contains the list
   virtual int getCapacity() const;
};

template <class item_t>
ArrayList<item_t>::ArrayList()
{
  size= 0;
  capacity = 10;
  items= new item_t[capacity];
}

template <class item_t>
ArrayList<item_t>::ArrayList(int capacity)
{
  size = 0;
  this->capacity = capacity;
  items= new item_t[capacity];

}

template <class item_t>
ArrayList<item_t>::~ArrayList()
{
  delete[] items;
}

template <class item_t>
void ArrayList<item_t>::pushBack(const item_t& item)
{
  insert(size,item);
}


template <class item_t>
void ArrayList<item_t>::popBack()
{
  size= size-1;
}


template <class item_t>
const item_t& ArrayList<item_t>::getBack() const
{
  //item_t* item= items[size];
  return items[size-1];

}


template <class item_t>
void ArrayList<item_t>::pushFront(const item_t& item)
{
  insert(0,item);
}

template <class item_t>
void ArrayList<item_t>::popFront()
{

  remove(0);
}

template <class item_t>
const item_t& ArrayList<item_t>::getFront() const
{
  return getItem(0);
}



template <class item_t>
void ArrayList<item_t>::insert(int index, const item_t& item)
{
  int i;
  if (size < capacity)
    {
      i = size;
      while (i > index)
	{
	  items[i] = items[i-1];
	  i = i-1;
	}
      items[i] = item;
    }
  
  else
    {
      capacity = capacity *2;
      i = 0;
      int j = 0;
      item_t* temps = new item_t[capacity];
      while (i < size)
  	{
	  if (j == index)
	    {
	      temps[j] = item;
	      j+=1;
	    }
	  else
	    {
	      temps[j] = items[i];
	      i += 1;
	      j += 1;
	    }
  	}
      if (size == index)
	{
	  temps[size]= item;
	}
      delete[] items;
      items = temps;
    }
  size += 1;

}


template <class item_t>
const item_t& ArrayList<item_t>::getItem(int index) const
{
  return items[index];
}


template <class item_t>
void ArrayList<item_t>::remove(int index)
{
      int i =0;
      int j =0;
      item_t* temps = new item_t[capacity];
      while (i < size)
	{
	  if (index == i)
	    {
	      i+=1;
	    }
	  else
	    {
	      temps[j] = items[i];
	      i += 1;
	      j += 1;
	    }
	}
      delete[] items;
      items = temps;
      size = size -1;
}


template <class item_t>
void ArrayList<item_t>::setItem(int index, const item_t& item)
{
  items[index] =item;
}

template <class item_t>
int ArrayList<item_t>::getSize() const
{
  return size;
}

template <class item_t>
bool ArrayList<item_t>::isEmpty() const
{
  if (size == 0)
    {
      return true;
    }
  return false;
}

template <class item_t>
int ArrayList<item_t>::getCapacity() const
{
  return capacity;
}

#endif
