#include <iostream>
#include <string>
#include <cstdlib>
#include "Scheduler.h"
#include <chrono>
#include <queue>

using namespace std;

double* simulate(Scheduler* sched, int numCPUBound, int numIOBound, int numCycles)
{
  queue<Process*> q;

  double scount = 0;
  int i = 0;


  while (i < numCPUBound)
    {

      CPUBoundProcess* proc= new CPUBoundProcess(1);
      sched->addProcess(proc);
      q.push(proc);
      i+= 1;
    }
  i = 0;


  while (i <numIOBound)
    {
      IOBoundProcess* proc2=new IOBoundProcess(2);
      sched->addProcess(proc2);
      q.push(proc2);
      i+= 1;
    }


  i = 0;
  auto t1 =chrono::system_clock::now();
  Process* a;

  while (i< numCycles)
    {
      a = sched->popNext(i);
      i += a->simulate(i,10);
      //i += 10;
      sched->addProcess(a);
      scount += 1;
    }

  auto t2 =chrono::system_clock::now();
  auto dur = t2 -t1;
  auto durMS = chrono::duration_cast<chrono::nanoseconds>(dur);
  double elapsed = durMS.count();
  int i2 = 0;
  double cpuct = 0;
  double cpuwt = 0;
  double ioct = 0;
  double iowt = 0;


  while ( q.empty() == false)
    {
      a = q.front();
      q.pop();

      if (a->getID()== 1)
	{
	  cpuct += double(a->getCPUTime());
	  cpuwt += double(a->getWaitTime(i));
	}
      else
	{
	  ioct += double(a->getCPUTime());
	  iowt += double(a->getWaitTime(i));
	}
      delete a;
      i2 += 1;
    }


  // cpuct = cpuct/numCPUBound;
  // cpuwt = cpuwt/numCPUBound;
  // ioct = ioct/numIOBound;
  // iowt = iowt/numIOBound;

  double* data = new double[5];
  data[0] = elapsed/numCycles;
  data[1] = cpuct/double(numCPUBound);
  data[2] = cpuwt/double(numCPUBound);
  data[3] = ioct/double(numIOBound);
  data[4] = iowt/double(numIOBound);
  return data;
}
