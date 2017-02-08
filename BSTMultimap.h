#ifndef BST_MULTIMAP
#define BST_MULTIMAP
#include "BSTNode.h"
#include <iostream>
#include <queue>
#include "BSTForwardIterator.h"
using namespace std;

template <class key_t, class val_t>
class BSTMultimap
{
 protected:
  BSTNode<key_t,val_t>* root;
  BSTNode<key_t,val_t>* sentinel;
  int numItems;
  virtual void helper(BSTNode<key_t,val_t>* node1,BSTNode<key_t,val_t>* node2);
  virtual void transform(BSTNode<key_t,val_t>* node1,BSTNode<key_t,val_t>* node2);
  virtual void insertNode(BSTNode<key_t, val_t>* newNode);

 public:
  BSTMultimap();
  virtual ~BSTMultimap();
  virtual void insert(const key_t& key, const val_t& val);
  virtual int getSize();
  virtual bool isEmpty();
  virtual void printTree();
  virtual bool contains(const key_t& key) const;
  virtual void clear();
  virtual BSTForwardIterator<key_t,val_t> getMin() const;
  virtual BSTForwardIterator<key_t,val_t> getMax() const;
  virtual BSTForwardIterator<key_t,val_t> findFirst(const key_t& key) const;
  virtual BSTForwardIterator<key_t,val_t> findLast(const key_t& key) const;
  virtual BSTForwardIterator<key_t, val_t> remove(const BSTForwardIterator<key_t, val_t>& pos);


  template <class k_t, class v_t> friend class BSTForwardIterator;
};

template <class key_t, class val_t>
BSTMultimap<key_t, val_t>::BSTMultimap() 
{

  sentinel = NULL;
  root = NULL;
  numItems = 0;
}

template <class key_t, class val_t>
void BSTMultimap<key_t, val_t>::insert(const key_t& key, const val_t& val)
{
  BSTNode<key_t, val_t>* newNode = new BSTNode<key_t, val_t>(key,val);
  insertNode(newNode);
}

template <class key_t, class val_t>
void BSTMultimap<key_t, val_t>::insertNode(BSTNode<key_t, val_t>* newNode)
{


  if (root== sentinel)
    {
      //root =new BSTNode<key_t, val_t>(key,val);
      root = newNode;
    }
  else
    {
    helper(root,newNode);
    }
  numItems += 1;
}



template <class key_t, class val_t>
void BSTMultimap<key_t, val_t>::helper(BSTNode<key_t,val_t>* node1,BSTNode<key_t,val_t>* node2)
{

  if (node1->getKey() > node2->getKey())
    {
      if (node1->getLeftChild() == sentinel)
	{
	  node1->setLeftChild(node2);
	  node2->setParent(node1);
	}
      else
	{
	  helper(node1->getLeftChild(),node2);
	}
    }
  else
    {
      if (node1->getRightChild() == sentinel)
	{
	  node1->setRightChild(node2);
	  node2->setParent(node1);

	}
      else
	{
	 
	  helper(node1->getRightChild(),node2);
	}

    }
}



template <class key_t, class val_t>
bool BSTMultimap<key_t, val_t>::contains(const key_t& key) const
{
  
  if (root == sentinel)
    {
      return false;
    }
  BSTNode<key_t, val_t>* x = root;
  while (x != sentinel && key != x->getKey())
    {
      if(key < x->getKey())
	{
	  x =x->getLeftChild();
	}
      else
	{
	  x = x->getRightChild();
	}
    }
  if (x == sentinel)
    return false;
  if (key == x->getKey())
    {
      return true;
    }
  return false;
    
}


template <class key_t, class val_t>
void BSTMultimap<key_t, val_t>::printTree()
{
  queue<BSTNode<key_t, val_t>*> q;
  q.push(root);
  while (q.empty() == false)
    {
      BSTNode<key_t, val_t>* temp = q.front();
      q.pop();
      if (temp != sentinel)
	{
	  cout<<temp->getKey()<<" ";
	  BSTNode<key_t, val_t>* temp2 = temp->getLeftChild();
	  if (temp2 != sentinel)
	    {
	      q.push(temp2);
	    }
	  else
	    {
	      q.push(sentinel);
	    }
	  BSTNode<key_t, val_t>* temp3 = temp->getRightChild();
	  if (temp3 != sentinel)
	    {
	      q.push(temp3);
	    }
	  else
	    {
	      q.push(sentinel);
	    }
	}
      else
	{
	  cout<<"NULL ";
	}
      
    } 
}

template <class key_t, class val_t>
  int BSTMultimap<key_t, val_t>:: getSize()
{
  return numItems;
}

template <class key_t, class val_t>
BSTMultimap<key_t, val_t>::~BSTMultimap()
{
  clear();
}

template <class key_t, class val_t>
bool BSTMultimap<key_t, val_t>::isEmpty()
{
  if (numItems == 0)
    {
      return true;
    }
  return false;
}

template <class key_t, class val_t>
void BSTMultimap<key_t, val_t>::clear()
{

  queue<BSTNode<key_t, val_t>*> q;
  q.push(root);
  while (q.empty() == false)
    {
      BSTNode<key_t, val_t>* temp = q.front();
      q.pop();
      if (temp != sentinel)
	{
	 
	  //BSTNode<key_t, val_t>* temp2 = temp->getLeftChild();
	  if (temp->getLeftChild() != sentinel)
	    {
	      q.push(temp->getLeftChild());
	    }
	  else
	    {
	      q.push(sentinel);
	    }
	  //BSTNode<key_t, val_t>* temp3 = temp->getRightChild();
	  if (temp->getRightChild() != sentinel)
	    {
	      q.push(temp->getRightChild());
	    }
	  else
	    {
	      q.push(sentinel);
	    }
	  delete temp;
	}
      
    } 
  root = sentinel;
  numItems =0;

}

template <class key_t, class val_t>
BSTForwardIterator<key_t,val_t> BSTMultimap<key_t, val_t>::getMin() const
{
  BSTNode<key_t, val_t>* cur = root;
  if (cur == sentinel)
    {
      return BSTForwardIterator<key_t,val_t>(root,sentinel);
    }  
 
   
  while (cur->getLeftChild() != sentinel)
    {
      cur = cur->getLeftChild();
    }
  return BSTForwardIterator<key_t,val_t> (cur,sentinel);
}

template <class key_t, class val_t>
BSTForwardIterator<key_t,val_t> BSTMultimap<key_t, val_t>::getMax() const
{
  BSTNode<key_t, val_t>* cur = root;
  if (cur == sentinel)
    {
      return BSTForwardIterator<key_t,val_t>(root,sentinel);
    }
 
   
  while (cur->getRightChild() != sentinel)
    {
      cur = cur->getRightChild();
    }
  return BSTForwardIterator<key_t,val_t> (cur,sentinel);
}

template <class key_t, class val_t>
BSTForwardIterator<key_t,val_t> BSTMultimap<key_t, val_t>::findFirst(const key_t& key) const
{


  if (root == sentinel)
    {
      return BSTForwardIterator<key_t,val_t>(sentinel,sentinel);
    }
  BSTNode<key_t, val_t>* cur = root;
  BSTNode<key_t, val_t>* cur2 = cur;

  while (cur != sentinel)
    {

      if(key <= cur->getKey())
	{

	  cur =cur->getLeftChild();
	  if (cur != sentinel)
	    {
	      if (cur->getKey() == key)
		{
		  cur2= cur;
		}
	    }
	    
	}
      else
	{

	  cur = cur->getRightChild();

	  if (cur != sentinel)
	    {
	      if (cur->getKey() == key)
		{
		  cur2 = cur;
		}
	    }
	}
    }
  cur = cur2;

  if (cur == sentinel)
    {
      return BSTForwardIterator<key_t,val_t>(sentinel,sentinel);
    }

  return BSTForwardIterator<key_t,val_t>(cur,sentinel);
}


template <class key_t, class val_t>
BSTForwardIterator<key_t,val_t> BSTMultimap<key_t, val_t>::findLast(const key_t& key) const
{


  if (root == sentinel)
    {

      return BSTForwardIterator<key_t,val_t>(sentinel,sentinel);
    }
  BSTNode<key_t, val_t>* cur = root;
  BSTNode<key_t, val_t>* cur2 = cur;
  while (cur != sentinel)
    {

      if(key < cur->getKey())
	{

	  cur =cur->getLeftChild();
	  if (cur != sentinel)
	    {
	      if (cur->getKey() == key)
		{
		  cur2= cur;
		}
	    }
	    
	}
      else
	{

	  cur = cur->getRightChild();

	  if (cur != sentinel)
	    {
	      if (cur->getKey() == key)
		{
		  cur2 = cur;
		}
	    }
	}
    }
  cur = cur2;

  if (cur == sentinel)
    {
      return BSTForwardIterator<key_t,val_t>(sentinel,sentinel);
    }

  return BSTForwardIterator<key_t,val_t>(cur,sentinel);
}

template <class key_t, class val_t>
void BSTMultimap<key_t, val_t>::transform(BSTNode<key_t,val_t>* node1,BSTNode<key_t,val_t>* node2)
{
  if (node1->getParent() == sentinel)
    {
      root = node2;
    }
  else if (node1 == node1->getParent()->getLeftChild())
    {
      node1->getParent()->setLeftChild(node2);
    }
  else
    {
      node1->getParent()->setRightChild(node2);
    }
  if (node2 != sentinel)
    {
      node2->setParent(node1->getParent());
    }
  
}

template <class key_t, class val_t>
BSTForwardIterator<key_t, val_t> BSTMultimap<key_t, val_t>::remove(const BSTForwardIterator<key_t, val_t>& pos)
{
  BSTNode<key_t,val_t>* z = pos.current;
  BSTForwardIterator<key_t,val_t> copy(z,sentinel);
  copy.next();

  if (z->getLeftChild() == sentinel)
    {
      transform(z,z->getRightChild());
    }
  else if (z->getRightChild() == sentinel)
    {
    transform(z,z->getLeftChild());
    }  
  else
    {
      BSTNode<key_t,val_t>* y = z->getRightChild();
      while (y->getLeftChild() != sentinel)
  	{
  	  y =y->getLeftChild();
  	}
      if (y->getParent() != z)
  	{
  	  transform(y,y->getRightChild());
  	  y->setRightChild(z->getRightChild());
  	  y->getRightChild()->setParent(y);
  	}
      transform(z,y);
      y->setLeftChild(z->getLeftChild());
      y->getLeftChild()->setParent(y);
      
    }
  //cout<<"here"<<endl;
  
  delete z;
  /* cout<<copy.current->getKey()<<endl; */
  /* cout<<copy */
  /* cout<<"here"<<endl; */
  numItems =numItems- 1;
  return copy;
}

#endif
