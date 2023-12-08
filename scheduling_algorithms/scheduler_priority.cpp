/**
 * Assignment 3: CPU Scheduler
 * @file scheduler_priority.cpp
 * @author Salman Burhan
 * @brief This Scheduler class implements the Priority scheduling algorithm.
 * @version 0.1
 */

#include "scheduler_priority.h"

/**
 * @brief Construct a new SchedulerPriority object
 */
SchedulerPriority::SchedulerPriority() {}

/**
 * @brief Destroy the SchedulerPriority object
 */
SchedulerPriority::~SchedulerPriority()
{
    this->processes.clear();
}

/**
 * @brief This function is called once before the simulation starts.
 *        It is used to initialize the scheduler.
 * @param process_list The list of processes in the simulation.
 */
void SchedulerPriority::init(std::vector<PCB> &process_list)
{
    this->processes = process_list;
}

/**
 * @brief This function simulates the run order of the processes
 *        in the ready queue.
 */
void SchedulerPriority::simulate_run_order()
{
    for (const PCB &process : this->processes)
    {
        cout << "Running Process "
             << process.name
             << " for "
             << process.burst_time
             << " time units."
             << endl;
    }
}

/**
 * @brief This function sorts the processes in the ready queue by
 *        priority in descending order, yielding tied values to
 *        the process with the smaller id.
 */
void SchedulerPriority::process_sort_priority()
{
    sort(this->processes.begin(), this->processes.end(), [](PCB a, PCB b)
         { return tie(a.priority, b.id) > tie(b.priority, a.id); });
}

/**
 * @brief This function sorts the processes in the ready queue by
 *        the arrival time, yielding tied values to the process with
 *        the smaller id.
 */
void SchedulerPriority::process_sort_default()
{
    sort(this->processes.begin(), this->processes.end(), [](PCB a, PCB b)
         { return tie(a.arrival_time, a.id) < tie(b.arrival_time, b.id); });
}

/**
 * @brief This function calculates the waiting_time and turnaround_time
 *        of each process in the ready queue.
 */
void SchedulerPriority::calculate_times()
{
    this->processes[0].waiting_time = 0;
    this->processes[0].turnaround_time = this->processes[0].burst_time;

    for (int i = 1; i < this->processes.size(); ++i)
    {
        this->processes[i].waiting_time =
            this->processes[i - 1].waiting_time +
            this->processes[i - 1].burst_time;

        this->processes[i].turnaround_time =
            this->processes[i].waiting_time +
            this->processes[i].burst_time;
    }
}

/**
 * @brief This function is called once after the simulation ends.
 *        It is used to print out the results of the simulation.
 */
void SchedulerPriority::print_results()
{
    float total_turnaround_time = 0, total_waiting_time = 0;

    for (const PCB &process : this->processes)
    {
        std::cout << process.name
                  << " turn-around time = "
                  << process.turnaround_time
                  << ", waiting time = "
                  << process.waiting_time
                  << std::endl;
        total_turnaround_time += process.turnaround_time;
        total_waiting_time += process.waiting_time;
    }

    std::cout << "Average turn-around time = "
              << total_turnaround_time / this->processes.size()
              << ", Average waiting time = "
              << total_waiting_time / this->processes.size()
              << std::endl;
}

/**
 * @brief This function simulates the scheduling of processes in the ready queue.
 *        It stops when all processes are finished.
 */
void SchedulerPriority::simulate()
{
    this->process_sort_priority();
    this->simulate_run_order();
    this->calculate_times();
    this->process_sort_default();
}