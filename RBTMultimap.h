#ifndef RBT_MULTIMAP
#define RBT_MULTIMAP

#include "BSTMultimap.h"
#include "RBTNode.h"
#include "BSTForwardIterator.h"
#include <string>
#include <fstream>
#include <queue>
#include <iostream>
#include <map>

using namespace std;

template <class key_t, class val_t>
class RBTMultimap : public BSTMultimap<key_t, val_t>
{
  protected:
   //Performs the rotate left operation
   //(assumes node has a right child)
   virtual void rotateLeft(BSTNode<key_t, val_t>* node);

   //Performs the rotate right operation
   //(assumes node has a left child)
   virtual void rotateRight(BSTNode<key_t, val_t>* node);

   //Fix up the tree after an insert
   //(assumes insertedNode is red)
   virtual void insertFixup(RBTNode<key_t, val_t>* insertedNode);

   //Fix up the tree after deleting a node
   //ReplacementNode is the node that replaced the deleted node
   //(possibly the sentinel)
   
   virtual void deleteFixup(RBTNode<key_t, val_t>* replacementNode);

   //Puts replacementNode in nodeToReplace's position in the tree
   //(replacementNode takes its children along with it)
   //Assumes nodeToReplace is a real node (not the sentinel)
   
   virtual void transplant(BSTNode<key_t, val_t>* nodeToReplace, BSTNode<key_t, val_t>* replacementNode);

  public:
   //Creates an empty red-black tree
   RBTMultimap();
   virtual ~RBTMultimap();

   //Inserts (key, value) into the multimap
   virtual void insert(const key_t& key, const val_t& value);

   //Removes the key/value pair pointed to by pos
   //(if pos is off the end, does nothing)
   //Returns an iterator pointing to the next node after the
   //deleted node

   virtual BSTForwardIterator<key_t, val_t> remove(const BSTForwardIterator<key_t, val_t>& pos);

   //Prints the tree in the "dot" format for visualization
   //using graphviz
   //NOTE: Requires that keys are streamable (values are not printed)
   virtual void printDOT(std::string filename);
};

//////////////////////////////////////////
//RBTMultimap implementation begins here//
//////////////////////////////////////////

template <class key_t, class val_t>
RBTMultimap<key_t, val_t>::RBTMultimap()
{
  key_t key;
  val_t val;
  RBTNode<key_t, val_t>* newNode = new RBTNode<key_t, val_t>(key,val,false);


  this->sentinel = newNode;
  this->root = this->sentinel;


}
template <class key_t, class val_t>
RBTMultimap<key_t, val_t>::~RBTMultimap()
{
  this->clear();
  delete this->sentinel;

}



template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::insert(const key_t& key, const val_t& value)
{
  RBTNode<key_t, val_t>* newNode = new RBTNode<key_t, val_t>(key,value,true);
  newNode->setLeftChild(this->sentinel);
  newNode->setRightChild(this->sentinel);
  newNode->setParent(this->sentinel);
  this->insertNode(newNode);
  insertFixup(newNode);

}


template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::insertFixup(RBTNode<key_t, val_t>* insertedNode)
{
  //FILL THIS IN
  RBTNode<key_t, val_t>* y;
  while (insertedNode->getParent()->getColor() == true)
    {
      if (insertedNode->getParent()==insertedNode->getParent()->getParent()->getLeftChild())
	{
	  y = insertedNode->getParent()->getParent()->getRightChild();
	  
	  if (y->getColor() == true)
	    {
	      insertedNode->getParent()->setColor(false);
	      y->setColor(false);
	      insertedNode->getParent()->getParent()->setColor(true);
	      insertedNode = insertedNode->getParent()->getParent();
	    }
	  else
	    { 
	      if (insertedNode ==insertedNode->getParent()->getRightChild())
		{
		  insertedNode = insertedNode->getParent();
		  rotateLeft(insertedNode);
		}
	      insertedNode->getParent()->setColor(false);
	      insertedNode->getParent()->getParent()->setColor(true);
	      rotateRight(insertedNode->getParent()->getParent());
	    
	    }
	  
	}
      else
	{
	  //switch sides
	  y = insertedNode->getParent()->getParent()->getLeftChild();
	  
	  if (y->getColor() == true)
	    {
	      insertedNode->getParent()->setColor(false);
	      y->setColor(false);
	      insertedNode->getParent()->getParent()->setColor(true);
	      insertedNode = insertedNode->getParent()->getParent();
	    }
	  else
	    { 
	      if (insertedNode ==insertedNode->getParent()->getLeftChild())
		{
		  insertedNode = insertedNode->getParent();
		  rotateRight(insertedNode);
		}
	      insertedNode->getParent()->setColor(false);
	      insertedNode->getParent()->getParent()->setColor(true);
	      rotateLeft(insertedNode->getParent()->getParent());
	    
	    }
	  
	}
    }
  RBTNode<key_t, val_t>* root = dynamic_cast<RBTNode<key_t, val_t>*>(this->root);
  root->setColor(false);
}

template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::rotateLeft(BSTNode<key_t, val_t>* node)
{
  BSTNode<key_t, val_t>* y = node->getRightChild();
  node->setRightChild(y->getLeftChild());
  if (y->getLeftChild() != this->sentinel)
    {
      y->getLeftChild()->setParent(node);
    }
  y->setParent(node->getParent());
  if (node->getParent()== this->sentinel)
    {
      this->root =y;
    }
  else if( node == node->getParent()->getLeftChild())
    {
      node->getParent()->setLeftChild(y);
    }
  else
    {
      node -> getParent()->setRightChild(y);
    }
  y->setLeftChild(node);
  node->setParent(y);
}

template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::rotateRight(BSTNode<key_t, val_t>* node)
{
  BSTNode<key_t, val_t>* y = node->getLeftChild();
  node->setLeftChild(y->getRightChild());
  if (y->getRightChild() != this->sentinel)
    {
      y->getRightChild()->setParent(node);
    }
  y->setParent(node->getParent());
  if (node->getParent()== this->sentinel)
    {
      this->root =y;
    }
  else if( node == node->getParent()->getRightChild())
    {
      node->getParent()->setRightChild(y);
    }
  else
    {
      node -> getParent()->setLeftChild(y);
    }
  y->setRightChild(node);
  node->setParent(y);
}
 

template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::transplant(BSTNode<key_t, val_t>* nodeToReplace, BSTNode<key_t, val_t>* replacementNode)
{
  if (nodeToReplace->getParent() == this->sentinel)
    {
      this->root = replacementNode;
    }
  else if (nodeToReplace == nodeToReplace->getParent()->getLeftChild())
    {
      nodeToReplace->getParent()->setLeftChild(replacementNode);
    }
  else
    {
      nodeToReplace->getParent()->setRightChild(replacementNode);
    }
  replacementNode->setParent(nodeToReplace->getParent());
}
 


template <class key_t, class val_t>
BSTForwardIterator<key_t, val_t> RBTMultimap<key_t, val_t>::remove(const BSTForwardIterator<key_t, val_t>& pos)
{
  //RBTNode<key_t,val_t>* q = pos.current;
  this->numItems -=1;
  RBTNode<key_t, val_t>* z = dynamic_cast<RBTNode<key_t, val_t>*>(pos.current);
  //RBTNode<key_t, val_t>* z  =pos.current;


  BSTForwardIterator<key_t,val_t> newtemp (z,this->sentinel);
  newtemp.next();

  RBTNode<key_t, val_t>* y=  (RBTNode<key_t, val_t>*) z;

  RBTNode<key_t, val_t>* x;

  bool yorigcolor = y->getColor();
  if ((RBTNode<key_t, val_t>*)z->getLeftChild()== this->sentinel)
    {
      x = (RBTNode<key_t, val_t>*)z->getRightChild();
      transplant((RBTNode<key_t, val_t>*)z,(RBTNode<key_t, val_t>*)z->getRightChild());
    }
  else if ((RBTNode<key_t, val_t>*)z->getRightChild() == this->sentinel)
    {
      x = (RBTNode<key_t, val_t>*)z->getLeftChild();
      transplant((RBTNode<key_t, val_t>*)z,(RBTNode<key_t, val_t>*)z->getLeftChild());
    } 
  else
    {
      //finding min
      y = (RBTNode<key_t, val_t>*)z->getRightChild();
      while (y->getLeftChild() != this->sentinel)
	{
	  y = y->getLeftChild();
	}
      //done finding min
      yorigcolor = y->getColor();
      x = y->getRightChild();
      if (y->getParent() == (RBTNode<key_t, val_t>*)z)
	{
	  x->setParent(y);
	}
      else
	{
	  transplant(y,y->getRightChild());
	  y->setRightChild((RBTNode<key_t, val_t>*)z->getRightChild());
	  y->getRightChild()->setParent(y);
	  
	}
      transplant(z,y);
      y->setLeftChild((RBTNode<key_t, val_t>*)z->getLeftChild());
      y->getLeftChild()->setParent(y);
      y->setColor((RBTNode<key_t, val_t>*)z->getColor());
    }
  if (yorigcolor == false)
    {
      
      deleteFixup(x);
    }
  delete pos.current;

  return newtemp;
}


template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::deleteFixup(RBTNode<key_t, val_t>* replacementNode)
{
  /* cout<<replacementNode->getKey()<<endl; */
  /* if (replacementNode == this->sentinel) */
  /*   { */
  /*     cout<<"yes"<<endl; */
  /*   } */
  while (replacementNode != this->root && replacementNode->getColor()==false)
    {
      if (replacementNode == replacementNode->getParent()->getLeftChild())
	{
	  RBTNode<key_t, val_t>* w = replacementNode->getParent()->getRightChild();
	  if (w->getColor() == true)
	    {
	      w->setColor(false);
	      replacementNode->getParent()->setColor(true);
	      rotateLeft(replacementNode->getParent());
	      w = replacementNode->getParent()->getRightChild();
	    }
	  if (w->getLeftChild()->getColor() == false && w->getRightChild()->getColor()==false)
	    {
	      w->setColor(true);
	      replacementNode = replacementNode->getParent();
	    }
	  else
	    {
	      if (w->getRightChild()->getColor()==false)
		{
		  w->getLeftChild()->setColor(false);
		  w->setColor(false);
		  rotateRight(w);
		  w= replacementNode->getParent()->getRightChild();
		}
	      w->setColor(replacementNode->getParent()->getColor());
	      replacementNode->getParent()->setColor(false);
	      w->getRightChild()->setColor(false);
	      rotateLeft(replacementNode->getParent());
	      replacementNode = (RBTNode<key_t, val_t>*)this->root;
	    }
	}
      else
	{
	  //flipped left-right

	  RBTNode<key_t, val_t>* w = replacementNode->getParent()->getLeftChild();
	  if (w->getColor() == true)
	    {
	      w->setColor(false);
	      replacementNode->getParent()->setColor(true);
	      rotateRight(replacementNode->getParent());
	      w = replacementNode->getParent()->getLeftChild();
	    }
	  if (w->getRightChild()->getColor() == false && w->getLeftChild()->getColor()==false)
	    {
	      w->setColor(true);
	      replacementNode = replacementNode->getParent();
	    }
	  else
	    {
	      if (w->getLeftChild()->getColor()==false)
		{
		  w->getRightChild()->setColor(false);
		  w->setColor(false);
		  rotateLeft(w);
		  w= replacementNode->getParent()->getLeftChild();
		}
	      w->setColor(replacementNode->getParent()->getColor());
	      replacementNode->getParent()->setColor(false);
	      w->getLeftChild()->setColor(false);
	      rotateRight(replacementNode->getParent());
	      replacementNode = (RBTNode<key_t, val_t>*)this->root;
	    }
	}

    }

  replacementNode->setColor(false);
}


template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::printDOT(std::string filename)
{
   using namespace std;
   ofstream fout(filename.c_str());

   long long counter = 1;
   map<RBTNode<key_t, val_t>*, long long> nodeToCounter;
   nodeToCounter[dynamic_cast<RBTNode<key_t, val_t>* >(this->sentinel)] = counter;
   counter++;

   fout << "digraph RBTMultimap {" << endl;

   fout << "\t node" << nodeToCounter[dynamic_cast<RBTNode<key_t, val_t>* >(this->sentinel)] << " [label=\"nil\", style=filled, color=grey, fontcolor=white];" << endl;

   if(this->root != this->sentinel)
   {
      RBTNode<key_t, val_t>* rt = dynamic_cast<RBTNode<key_t, val_t>* >(this->root);
      if(!nodeToCounter[rt])
      {
	 nodeToCounter[rt] = counter;
	 counter++;
      }
      if(!nodeToCounter[rt->getParent()])
      {
	 nodeToCounter[rt->getParent()] = counter;
	 counter++;
      }
      fout << "\t node" << nodeToCounter[rt] << " -> node" << nodeToCounter[rt->getParent()] << " [constraint=false, tailport=n, headport=s";
      if(rt->getParent() == this->sentinel)
      {
	 fout << ", color=grey];" << endl;
      }
      else
      {
	 //The root's parent is something weird!! Make the arrow orange so it sticks out
	 fout << ", color=orange];" << endl;
      }

      map<RBTNode<key_t, val_t>*, bool> printed;
   
      queue<RBTNode<key_t, val_t>* > q;
      q.push(rt);
      while(!q.empty())
      {
	 RBTNode<key_t, val_t>* node = q.front();
	 q.pop();

	 printed[node] = true;
      
	 //Set up node's appearance
	 if(!nodeToCounter[node])
	 {
	    nodeToCounter[node] = counter;
	    counter++;
	 }
	 fout << "\t node" << nodeToCounter[node] << " [label=\"k: " << node->getKey() << "\", style=filled, color=";
	 if(node->getColor())
	 {
	    fout << "red";
	 }
	 else
	 {
	    fout << "black, fontcolor=white";
	 }
	 fout << "];" << endl;

	 //Set up child links
	 //First the left node
	 if(!nodeToCounter[node->getLeftChild()])
	 {
	    nodeToCounter[node->getLeftChild()] = counter;
	    counter++;
	 }
	 fout << "\t node" << nodeToCounter[node] << " -> node" << nodeToCounter[node->getLeftChild()] << " [tailport=sw";    
	 if(node->getLeftChild() == this->sentinel)
	 {
	    fout << ", color=grey";
	 }
	 else if(printed[node->getLeftChild()])
	 {
	    fout << ", color=orange";
	 }
	 else
	 {
	    q.push(node->getLeftChild());
	 }

	 if(node->getLeftChild() != this->sentinel)
	 {
	    if(node->getLeftChild()->getParent() == node)
	    {
	       //The child's parent pointer points right back,
	       //so draw the second arrow
	       fout << ", dir=both];" << endl;
	    }
	    else
	    {
	       //The child node's parent pointer is not correct!
	       //Draw it in orange so it sticks out
	       fout << "];" << endl;
	       if(!nodeToCounter[node->getLeftChild()->getParent()])
	       {
		  nodeToCounter[node->getLeftChild()->getParent()] = counter;
		  counter++;
	       }
	       fout << "\t node" << nodeToCounter[node->getLeftChild()] << " -> node" << nodeToCounter[node->getLeftChild()->getParent()] << " [tailport=n, color=orange];" << endl;
	    }
	 }
	 else
	 {
	    fout << "];" << endl;
	 }

	 //Now the right node
	 if(!nodeToCounter[node->getRightChild()])
	 {
	    nodeToCounter[node->getRightChild()] = counter;
	    counter++;
	 }
	 fout << "\t node" << nodeToCounter[node] << " -> node" << nodeToCounter[node->getRightChild()] << " [tailport=se";    
	 if(node->getRightChild() == this->sentinel)
	 {
	    fout << ", color=grey";
	 }
	 else if(printed[node->getRightChild()])
	 {
	    fout << ", color=orange";
	 }
	 else
	 {
	    q.push(node->getRightChild());
	 }

	 if(node->getRightChild() != this->sentinel)
	 {
	    if(node->getRightChild()->getParent() == node)
	    {
	       //The child's parent pointer points right back,
	       //so draw the second arrow
	       fout << ", dir=both];" << endl;
	    }
	    else
	    {
	       //The child node's parent pointer is not correct!
	       //Draw it in orange so it sticks out
	       fout << "];" << endl;
	       if(!nodeToCounter[node->getRightChild()->getParent()])
	       {
		  nodeToCounter[node->getRightChild()->getParent()] = counter;
		  counter++;
	       }
	       fout << "\t node" << nodeToCounter[node->getRightChild()] << " -> node" << nodeToCounter[node->getRightChild()->getParent()] << " [tailport=n, color=orange];" << endl;
	    }
	 }
	 else
	 {
	    fout << "];" << endl;
	 }
      }
   }
   fout << "}" << endl;
}

#endif
