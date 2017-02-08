#include "ArrayList.h"
#include "LinkedList.h"
#include "BSTMultimap.h"
#include <iostream>
#include "Scheduler.h"
#include "RBTMultimap.h"

using namespace std;

RoundRobin::RoundRobin()
{

  
  procQueue = new ArrayList<Process*>;
  //procQueue = &temp;
}

RoundRobin::~RoundRobin()
{
  delete procQueue;
}

void RoundRobin::addProcess(Process* proc)
{
  procQueue->pushBack(proc);
}

Process* RoundRobin::popNext(int curCycle)
{
  Process* tempitem; 
  tempitem = procQueue->getFront();
  procQueue->popFront();
  return tempitem;
}


FastRoundRobin::FastRoundRobin() : RoundRobin()
{

  delete procQueue;

  procQueue = new LinkedList<Process*>;

}

CompletelyFair::CompletelyFair()
{
  procTree = new BSTMultimap<int, Process*>;
}

CompletelyFair::~CompletelyFair()
{
  delete procTree;
}

void CompletelyFair::addProcess(Process* proc)
{

  procTree->insert(proc->getCPUTime(),proc);
}

Process* CompletelyFair::popNext(int curCycle)
{
  BSTForwardIterator<int, Process*> iter =procTree->getMin();
  Process* tempitem;
  //&&iter.isPastEnd()==false

  while (iter.getValue()->isBlocked(curCycle))
    {
      iter.next();
    }

  tempitem = iter.getValue();
  if (tempitem->isBlocked(curCycle) == true)
    {
      cout<<"yes"<<endl;
    }
  //Process* cur = iter.getValue();
  procTree->remove(iter);



  return tempitem;
  
}

FastCompletelyFair::FastCompletelyFair() : CompletelyFair()
{

  delete procTree;

  procTree = new RBTMultimap<int, Process*>;

}
