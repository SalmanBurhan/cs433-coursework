/**
 * Assignment 3: CPU Scheduler
 * @file scheduler_fcfs.cpp
 * @author Salman Burhan
 * @brief This Scheduler class implements the FCSF scheduling algorithm.
 * @version 0.1
 */

#include "scheduler_fcfs.h"

/**
 * @brief Construct a new SchedulerFCFS object
 */
SchedulerFCFS::SchedulerFCFS() {}

/**
 * @brief Destroy the SchedulerFCFS object
 */
SchedulerFCFS::~SchedulerFCFS()
{
    this->processes.clear();
}

/**
 * @brief This function is called once before the simulation starts.
 *        It is used to initialize the scheduler.
 * @param process_list The list of processes in the simulation.
 */
void SchedulerFCFS::init(std::vector<PCB> &process_list)
{
    this->processes = process_list;
}

/**
 * @brief This function is called once after the simulation ends.
 *        It is used to print out the results of the simulation.
 */
void SchedulerFCFS::print_results()
{
    float total_turnaround_time = 0, total_waiting_time = 0;

    for (const PCB &process : this->processes)
    {
        cout << "T" << process.id + 1
             << " turn-around time = "
             << process.turnaround_time
             << ", waiting time = "
             << process.waiting_time
             << endl;
        total_turnaround_time += process.turnaround_time;
        total_waiting_time += process.waiting_time;
    }

    cout << "Average turn-around time = "
         << total_turnaround_time / this->processes.size()
         << ", Average waiting time = "
         << total_waiting_time / this->processes.size()
         << endl;
}

/**
 * @brief This function simulates the scheduling of processes in the ready queue.
 *        It stops when all processes are finished.
 */
void SchedulerFCFS::simulate()
{
    this->processes[0].waiting_time = 0;
    this->processes[0].turnaround_time = this->processes[0].burst_time;

    for (int i = 1; i < this->processes.size(); ++i)
    {
        this->processes[i].waiting_time =
            this->processes[i - 1].waiting_time +
            this->processes[i - 1].burst_time -
            this->processes[i].arrival_time;

        if (this->processes[i].waiting_time < 0)
        {
            this->processes[i].waiting_time = 0;
        }

        this->processes[i].turnaround_time =
            this->processes[i].waiting_time +
            this->processes[i].burst_time;
    }
}