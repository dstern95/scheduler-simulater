#include <chrono>
#include <iostream>
#include <string>
#include <cstdlib>
#include "Scheduler.h"
#include "simulate.h"

using namespace std;
int main(int argc, char** argv)
{
  int cpu = atoi(argv[1]);
  int io = atoi(argv[2]);
  int numCycles = atoi(argv[3]);

  //RoundRobin sched;
  //FastRoundRobin sched;
  int amt =4;
  Scheduler** types = new Scheduler*[4];
  types[0] = new RoundRobin;
  types[1] = new FastRoundRobin;
  types[2] = new CompletelyFair;
  types[3] = new FastCompletelyFair;
  int t = 0;
  string* text = new string[4];
  text[0] = "Round Robin";
  text[1] = "Fast Round Robin";
  text[2] = "Completely Fair";
  text[3] = "Fast Completely Fair";

  while (t<amt)
    {

      int i =0;

      double* fin = simulate(types[t],cpu,io,numCycles);
      cout<<text[t]<<"\t";
      cout<<"nanosec per sched"<<"\t"<<"avg cpu cpu time"<<"\t"<<"avg cpu wait time"<<"\t"<<"avg io cpu time"<<"\t"<<"avg io wait time"<<"\t"<<endl;

      cout<<"\t";
      while(i<5)
	{
	  //cout<<*fin<<"\t";
	  cout<<fin[i]<<"\t";
	  //fin += 1;
	  i+=1;
	}
      delete[] fin;
      cout<<endl;
      t +=1;
    }

}
