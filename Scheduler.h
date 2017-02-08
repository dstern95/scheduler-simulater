#ifndef SCHEDULER
#define SCHEDULER
#include "Process.h"
#include "ArrayList.h"
#include "LinkedList.h"
#include "BSTMultimap.h"
#include "RBTMultimap.h"
class Scheduler
{
 public:
  virtual ~Scheduler() { };
  virtual void addProcess(Process* proc)=0;
  virtual Process* popNext(int curCycle)=0;

};

class RoundRobin: public Scheduler
{
 protected:
  List<Process*>* procQueue;

 public:
  //initializes procQueue as an empty ArrayList.
  RoundRobin();

  //deletes procQueue (not its contents!)
  virtual ~RoundRobin();

  //adds the given process to the back of procQueue
  virtual void addProcess(Process* proc);

  //pops the process at the front of the queue and returns it
  virtual Process* popNext(int curCycle);

};

class FastRoundRobin: public RoundRobin
{

 public:
  //initializes procQueue as an empty ArrayList.
  FastRoundRobin();

  /* //deletes procQueue (not its contents!) */
  /* virtual ~FastRoundRobin(); */

  /* //adds the given process to the back of procQueue */
  /* virtual void addProcess(Process* proc); */

  /* //pops the process at the front of the queue and returns it */
  /* virtual Process* popNext(int curCycle); */

};

class CompletelyFair:public Scheduler
{
 protected:
  BSTMultimap<int, Process*>* procTree;

 public:
  CompletelyFair();
  virtual ~CompletelyFair();
  virtual void addProcess(Process* proc);
  virtual Process* popNext(int curCycle);

};

class FastCompletelyFair:public CompletelyFair
{

 public:
  FastCompletelyFair();


};

#endif
