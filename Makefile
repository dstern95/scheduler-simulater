OPTS = -Wall -std=c++11




Process.o: Process.h Process.cc
	g++ ${OPTS} -g -c Process.cc

Scheduler.o: Scheduler.h Scheduler.cc
	g++ ${OPTS} -g -c Scheduler.cc

simulate.o: simulate.cc simulate.h
	g++ ${OPTS} -g -c simulate.cc
schedulesim: schedulesim.cc Scheduler.o Process.o simulate.o
	g++ ${OPTS} -g -o schedsim schedulesim.cc Scheduler.o Process.o simulate.o
