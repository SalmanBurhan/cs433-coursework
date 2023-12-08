/**
 * Assignment 3: CPU Scheduler
 * @file scheduler_rr.h
 * @author Salman Burhan
 * @brief This Scheduler class implements the RoundRobin (RR) scheduling algorithm.
 * @version 0.1
 */

#ifndef ASSIGN3_SCHEDULER_RR_H
#define ASSIGN3_SCHEDULER_RR_H

#include "scheduler.h"
#include <deque>

class SchedulerRR : public Scheduler
{
private:
    std::vector<PCB> processes, completed_processes;
    std::deque<PCB> ready_queue;
    int quantum;
    int time;

public:
    /**
     * @brief Construct a new SchedulerRR object
     */
    SchedulerRR(int time_quantum = 10);

    /**
     * @brief Destroy the SchedulerRR object
     */
    ~SchedulerRR() override;

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
     * @brief This function simulates the scheduling of processes in the ready queue.
     *        It stops when all processes are finished.
     */
    void simulate() override;

    /**
     * @brief
     *
     * @param process
     * @return int
     */
    int remaining_time(PCB &process);

    /**
     * @brief
     *
     * @param process
     * @param time_units
     */
    void simulate_run(PCB &process, int time_units);

    /**
     * @brief
     *
     * @param current_process
     */
    void increment_wait_times(PCB &current_process, int time_units);

    /**
     * @brief
     *
     */
    void complete_process(PCB &process);

    /**
     * @brief
     *
     * @param process
     */
    void requeue_process(PCB &process);

    /**
     * @brief
     *
     * @param process
     */
    void audit_process(PCB &process);

    bool simulate_run(PCB &process);
};

#endif // ASSIGN3_SCHEDULER_RR_H
