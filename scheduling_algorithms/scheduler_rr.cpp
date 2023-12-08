/**
 * Assignment 3: CPU Scheduler
 * @file scheduler_rr.h
 * @author Salman Burhan
 * @brief This Scheduler class implements the RoundRobin (RR) scheduling algorithm.
 * @version 0.1
 */
// You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
//  Remember to add sufficient and clear comments to your code
//

#include "scheduler_rr.h"

/**
 * @brief Construct a new SchedulerRR object
 */
SchedulerRR::SchedulerRR(int time_quantum)
{
    this->quantum = time_quantum;
    this->time = 0;
}

/**
 * @brief Destroy the SchedulerRR object
 */
SchedulerRR::~SchedulerRR()
{
    this->processes.clear();
    // this->completed_processes.clear();
    this->quantum = 0;
    this->time = 0;
}

/**
 * @brief This function is called once before the simulation starts.
 *        It is used to initialize the scheduler.
 * @param process_list The list of processes in the simulation.
 */
void SchedulerRR::init(std::vector<PCB> &process_list)
{
    this->processes = process_list;
}

// PCB SchedulerRR::next_process()
// {
//     PCB process = this->processes.front();
//     this->processes.pop();
//     return process;
// }

// int SchedulerRR::remaining_time(PCB &process)
// {
//     return (process.remaining_burst_time > this->quantum)
//                ? this->quantum
//                : process.remaining_burst_time;
// }

// void SchedulerRR::increment_wait_times(PCB &current_process, int time_units)
// {
//     for (PCB &process : this->processes)
//         if (process.remaining_burst_time > 0 && process.id != current_process.id)
//             process.waiting_time += time_units;
// }

void SchedulerRR::simulate_run(PCB &process, int time_units)
{
    // for (int i = 0; i < time_units; i++)
    // {
    //     cout << "Running Process "
    //          << process.name
    //          << " for "
    //          << process.burst_time
    //          << " time units."
    //          << " current time = "
    //          << this->time
    //          << ", remaining_burst_time = "
    //          << process.remaining_burst_time
    //          << endl;
    //     this->time++;
    //     process.remaining_burst_time--;
    // }
}

// void SchedulerRR::audit_process(PCB &process)
// {
//     if (process.remaining_burst_time == 0)
//         this->complete_process(process);
//     else
//         this->requeue_process(process);
// }

// void SchedulerRR::complete_process(PCB &process)
// {
//     process.turnaround_time = this->time - process.start_time;
//     this->processes.erase(this->processes.begin());
//     this->completed_processes.push_back(process);
// }

// void SchedulerRR::requeue_process(PCB &process)
// {
//     this->processes.erase(this->processes.begin());
//     this->processes.push_back(process);
// }

/**
 * @brief This function is called once after the simulation ends.
 *        It is used to print out the results of the simulation.
 */
void SchedulerRR::print_results()
{
    float total_turnaround_time = 0, total_waiting_time = 0;

    for (const PCB &process : this->completed_processes)
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
              << total_turnaround_time / this->completed_processes.size()
              << ", Average waiting time = "
              << total_waiting_time / this->completed_processes.size()
              << std::endl;
}

bool SchedulerRR::simulate_run(PCB &process)
{
    if (process.remaining_burst_time <= 0)
    {
        // process.turnaround_time = process.waiting_time + process.burst_time;
        cout << "remaining-burst-time = 0" << endl;
        return true;
    }
    else
    {
        int remaining_time = std::min(this->quantum, process.remaining_burst_time);
        cout << "remaining-time = " << remaining_time << endl;
        for (int i = 0; i < remaining_time; i++)
        {
            for (PCB &p : this->ready_queue)
            {
                p.waiting_time++;
                p.turnaround_time++;
                cout << "p.id = " << p.id << ", process.id = " << process.id << endl;
                if (p.id == process.id)
                {
                    process.remaining_burst_time--;
                }
            }
            this->time++;
        }
        return false;
    }
}

/**
 * @brief This function simulates the scheduling of processes in the ready queue.
 *        It stops when all processes are finished.
 */
void SchedulerRR::simulate()
{
    for (const PCB &process : this->processes)
        ready_queue.push_back(process);

    while (ready_queue.empty() == false)
    {
        PCB process = ready_queue.front();

        bool complete = this->simulate_run(process);
        ready_queue.pop_front();

        if (complete == false)
            ready_queue.push_back(process);
        else
        {
            this->completed_processes.push_back(process);
        }
    }

    // bool complete = false;
    // int process_count = this->processes.size();

    // for (int i = 0; i < this->processes.size(); i++)
    // {
    //     PCB process = this->processes[i];
    //     if (this->is_process_complete(process) == false)
    //     {
    //         complete = false;
    //         int remaining_burst_time = process.remaining_burst_time;
    //         this->simulate_run(process, -1);
    //         int
    //     }
    // }
    // while (this->processes.empty() == false)
    // {
    //     PCB process = this->processes.front();
    //     if (process.start_time == 0)
    //         process.start_time = this->time;
    //     int time_left = this->remaining_time(process);
    //     this->simulate_run(process, time_left);
    //     this->increment_wait_times(process, time_left);
    //     this->audit_process(process);
    // }
    sort(this->completed_processes.begin(), this->completed_processes.end(), [](PCB a, PCB b)
         { return tie(a.arrival_time, a.id) < tie(b.arrival_time, b.id); });
}