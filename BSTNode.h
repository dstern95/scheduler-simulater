#ifndef BST_NODE
#define BST_NODE
#include <iostream>

using namespace std;

template <class key_t, class val_t>
class BSTNode
{
 protected:
  key_t key;
  val_t val;
  BSTNode<key_t,val_t>* parent;
  BSTNode<key_t,val_t>* leftChild;
  BSTNode<key_t,val_t>* rightChild;

 public:
  BSTNode(const key_t& ikey, const val_t& ival);

  virtual ~BSTNode();
  
  virtual void setValue(const val_t& ival);
  virtual void setKey(const key_t& ikey);
  virtual void setParent(BSTNode<key_t,val_t>* newParent);
  virtual void setLeftChild(BSTNode<key_t,val_t>* newlchild);
  virtual void setRightChild(BSTNode<key_t,val_t>* newrchild);

  virtual const val_t& getValue() const;
  virtual const key_t& getKey() const;
  virtual BSTNode<key_t,val_t>* getParent() const;
  virtual BSTNode<key_t,val_t>* getLeftChild() const;
  virtual BSTNode<key_t,val_t>* getRightChild() const;

};

template <class key_t, class val_t>
BSTNode<key_t, val_t>::~BSTNode()
{

}

template <class key_t, class val_t>
BSTNode<key_t, val_t>::BSTNode(const key_t& ikey, const val_t& ival)
{
  
  key = ikey;
  val = ival;
  parent = NULL;
  leftChild = 0;
  rightChild = 0;

}

template <class key_t, class val_t>
const val_t& BSTNode<key_t, val_t>::getValue() const
{
  return val;
}

template <class key_t, class val_t>
const key_t& BSTNode<key_t, val_t>::getKey() const
{
  return key;
}

template <class key_t, class val_t>
void BSTNode<key_t, val_t>::setValue(const val_t& ival)
{
  val = ival;
}

template <class key_t, class val_t>
void BSTNode<key_t, val_t>::setKey(const key_t& ikey)
{
  key = ikey;
}

template <class key_t, class val_t>
void BSTNode<key_t, val_t>::setParent(BSTNode<key_t,val_t>* newParent)
{
  parent = newParent;
}

template <class key_t, class val_t>
void BSTNode<key_t, val_t>::setLeftChild(BSTNode<key_t,val_t>* newlchild)
{
  leftChild = newlchild;
}

template <class key_t, class val_t>
void BSTNode<key_t, val_t>::setRightChild(BSTNode<key_t,val_t>* newrchild)
{
  rightChild = newrchild;
}


template <class key_t, class val_t>
BSTNode<key_t,val_t>* BSTNode<key_t, val_t>::getParent() const
{
  return parent;
}

template <class key_t, class val_t>
BSTNode<key_t,val_t>* BSTNode<key_t, val_t>::getLeftChild() const
{
  return leftChild;
}

template <class key_t, class val_t>
BSTNode<key_t,val_t>* BSTNode<key_t, val_t>::getRightChild() const
{
  return rightChild;
}

#endif
