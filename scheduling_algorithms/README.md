## CS433 - Operating Systems
# Programming Assignment 3
### Scheduling Algorithms

In this assignment, you will implement some basic scheduling algorithms discussed in the class. It is based on the programming project in chapter 5 of the textbook.

Complete the implementations of scheduling algorithms in the provided source files, and remove "TODO"s from the comments after you are done. Read on the course website for more details and submission instructions.

| `pcb.h` |
| ------- |

> A class representing a single task. Add your names to the file header. No other changes are needed for this file.

| `scheduler.h` |
| ------------- |
> A base class for different schedulers. It defines several pure virtual functions, init, print_results, and simulate, which are implemented in the subclasses. You don't need to make changes to this file. 

| `scheduler_fcfs.h` | `scheduler_fcfs.cpp` |
| ------------------ | -------------------- |
> A subclass of Scheduler implements the FCFS scheduling algorithm. You need to implement its constructor, and destructor, and override the init, print_results and simulate functions. The init function initializes the scheduler with an array of incoming processes. The simulate function simulates the scheduling of processes in an FCFS ready-queue. The print_results function prints out the statistics, including the turn-around and waiting time of each process and the average turn-around and waiting time. 

| `driver_fcfs.cpp` |
| ----------------- |
> A driver program tests the SchedulerFCFS class. It calls the member functions init, print_results and simulate. You don't need to change this file.

| `driver_sjf.cpp` | `scheduler_sjf.h` | `scheduler_sjf.cpp` |
| ---------------- | ----------------- | ------------------- |
> Files for SJF scheduling. Use the similar instructions as the FCFS scheduling algorithm.

| `driver_priority.cpp` | `scheduler_priority.h` | `scheduler_priority.cpp` |
| --------------------- | ---------------------- | ------------------------ |
> Files for priority scheduling.

| `driver_rr.cpp` | `scheduler_rr.h` | `scheduler_rr.cpp` |
| --------------- | ---------------- | ------------------ |
> Files for RR scheduling.

| `driver_priority_rr.cpp` | `scheduler_priority_rr.h` | `scheduler_priority_rr.cpp` |
| ------------------------ | ------------------------- | --------------------------- |
> Files for priority based RR scheduling (extra credits).
