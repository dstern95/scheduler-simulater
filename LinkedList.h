#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "List.h"
#include "LinkedListNode.h"
#include <iostream>
using namespace std;

template <class item_t>
class LinkedList: public List<item_t>
{

 protected:
  LinkedListNode<item_t>* head;
  LinkedListNode<item_t>* tail;
  int size;

 public:
  LinkedList();
  virtual ~LinkedList();
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
};
  
template <class item_t>
LinkedList<item_t>::LinkedList()
{
  size= 0;
  head = 0;
  tail= 0;
}



template <class item_t>
LinkedList<item_t>::~LinkedList()
{

  int i = 0;
  LinkedListNode<item_t>* temp = head;
  LinkedListNode<item_t>* temp2;
  while (i <size-1)
    {
      temp2 = temp;
      temp = temp->getNext();
      delete temp2;
      i +=1;
    }
  delete temp;

  
}

template <class item_t>
void LinkedList<item_t>::pushFront(const item_t& item)
{
  head = new LinkedListNode<item_t>(head,item);

  if (size == 0)
    {
      tail = head;
    }
  size += 1;
}

template <class item_t>
void LinkedList<item_t>::popFront()
{
  LinkedListNode<item_t>* temp = head;
  size = size -1;
  head = head->getNext();
  if (size == 0)
    {

      head = 0;
      tail = 0;
    }

  delete temp;
}

template <class item_t>
void LinkedList<item_t>::popBack()
{
  if (size == 1)
    {
      popFront();
    }
  else
    {
      remove(size-1);
    }

}
 
template <class item_t>
const item_t& LinkedList<item_t>::getFront()const
{

  return head->getItem();
}

template <class item_t>
void LinkedList<item_t>::pushBack(const item_t& item)
{

  
  if (size == 0)
    {
      pushFront(item);
    }
  else
    {
      LinkedListNode<item_t>*  temp = tail;
      tail = new LinkedListNode<item_t>(temp,item);
      temp->setNext(tail);
      size += 1;
    }
}

template <class item_t>
const item_t& LinkedList<item_t>::getBack()const
{
  cout<<head<<endl;
  cout<<tail<<endl;
  return tail->getItem();
}

template <class item_t>
const item_t& LinkedList<item_t>::getItem(int index)const
{
  int i = 0;
  LinkedListNode<item_t>* temp = head;
  while (i <index)
    {
      temp = temp->getNext();
      i +=1;
    }
  return temp->getItem();
}


template <class item_t>
void LinkedList<item_t>::setItem(int index, const item_t& item)
{
  int i = 0;
  LinkedListNode<item_t>* temp = head;
  while (i <index)
    {
      temp = temp->getNext();
      i +=1;
    }
  temp->setItem(item);
}


template <class item_t>
void LinkedList<item_t>::insert(int index,const item_t& item)
{
  
  if (index == 0)
    {
      pushFront(item);
    }
  else if ((index == size))
    {
      pushBack(item);
    }
  else
    {
      int i = 0;
      LinkedListNode<item_t>* temp = head;
      LinkedListNode<item_t>* temp2;
      while (i <index-1)
	{
	  temp = temp->getNext();
	  i +=1;
	}
      temp2 = temp->getNext();
      LinkedListNode<item_t>* ntemp = new LinkedListNode<item_t>(temp2,item);
      temp->setNext(ntemp);
      size+=1;
    }
}

template <class item_t>
void LinkedList<item_t>::remove(int index)
{
  int i = 0;
  if (index == 0)
    {
      popFront();
    }
  else
    {

      LinkedListNode<item_t>* temp = head;
      LinkedListNode<item_t>* temp2;
      LinkedListNode<item_t>* temp3;
      while (i <index-1)
	{
	  temp = temp->getNext();
	  i +=1;
	}
      if (index == size-1)
	{
	  temp2 = temp->getNext();
	  temp->setNext(0);
	  tail = temp;
	}
      else
	{
	  temp2 = temp->getNext();
	  temp3 = temp2->getNext();
	  temp->setNext(temp3);
	}
      size = size -1;
      delete temp2;
    }
}


template <class item_t>
int LinkedList<item_t>::getSize()const
{
  return size;
}

template <class item_t>
bool LinkedList<item_t>::isEmpty()const
{
  if (size == 0)
    {
      return true;
    }
  else
    {
      return false;
    }
}
#endif
