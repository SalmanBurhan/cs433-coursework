/**
 * Assignment 3: CPU Scheduler
 * @file scheduler_fcfs.h
 * @author Salman Burhan
 * @brief This Scheduler class implements the SJF scheduling algorithm.
 * @version 0.1
 */

#ifndef ASSIGN3_SCHEDULER_SJF_H
#define ASSIGN3_SCHEDULER_SJF_H

#include "scheduler.h"

class SchedulerSJF : public Scheduler
{
private:
    std::vector<PCB> processes;

public:
    /**
     * @brief Construct a new SchedulerSJF object
     */
    SchedulerSJF();
    /**
     * @brief Destroy the SchedulerSJF object
     */
    ~SchedulerSJF() override;
    /**
     * @brief This function is called once before the simulation starts.
     *        It is used to initialize the scheduler.
     * @param process_list The list of processes in the simulation.
     */
    void init(std::vector<PCB> &process_list) override;
    /**
     * @brief This function is called once after the simulation ends.
     *        It is used to print out the results of the simulation.
     */
    void print_results() override;

    /**
     * @brief This function simulates the scheduling of processes in the
     *        ready queue. It stops when all processes are finished.
     */
    void simulate() override;

    /**
     * @brief This function simulates the run order of the processes
     *        in the ready queue.
     */
    void simulate_run_order();

    /**
     * @brief This function sorts the processes in the ready queue by
     *        burst_time in ascending order, yielding tied values to
     *        the process with the smaller id.
     */
    void process_sort_burst_time();

    /**
     * @brief This function sorts the processes in the ready queue by
     *        the arrival time, yielding tied values to the process with
     *        the smaller id.
     */
    void process_sort_default();

    /**
     * @brief This function calculates the waiting_time and turnaround_time
     *        of each process in the ready queue.
     */
    void calculate_times();
};

#endif // ASSIGN3_SCHEDULER_SJF_H
