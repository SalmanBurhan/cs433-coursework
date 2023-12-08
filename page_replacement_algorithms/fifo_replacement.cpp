/**
 * Assignment 5: Page replacement algorithms
 * @file fifo_replacement.cpp
 * @author Salman Burhan, Nathaniel Vandenberg
 * @brief A class implementing the FIFO page replacement algorithms
 * @version 0.1
 */

#include "fifo_replacement.h"

/**
 * @brief Constructor for the FIFOReplacement class.
 *
 * @param num_pages The total number of pages.
 * @param num_frames The number of frames available for page replacement.
 */
FIFOReplacement::FIFOReplacement(int num_pages, int num_frames)
    : Replacement(num_pages, num_frames)
{
    frame_queue = new int[num_frames];
}

/**
 * Destructor for the FIFOReplacement class.
 * Frees the memory allocated for the frame queue.
 */
FIFOReplacement::~FIFOReplacement()
{
    delete[] frame_queue;
}

/**
 * @brief Copy constructor for FIFOReplacement class.
 * Included since it has dynamic memory/resource allocation(s)
 *
 * @param other The object to be copied.
 */
FIFOReplacement::FIFOReplacement(const FIFOReplacement &other)
    : Replacement(other)
{
    frame_queue = new int[other.total_frames];
    for (int i = 0; i < other.total_frames; i++)
    {
        frame_queue[i] = other.frame_queue[i];
    }
}

/**
 * Loads a page into the page table using the FIFO replacement algorithm.
 *
 * @param page_num The number of the page to be loaded.
 */
void FIFOReplacement::load_page(int page_num)
{
    page_table[page_num].valid = true;
    page_table[page_num].frame_num = num_frames;
    frame_queue[queue_tail] = page_num;
    queue_tail++;
    num_frames++;
    num_page_faults++;
}

/**
 * Replaces a page in the FIFO replacement algorithm.
 *
 * @param page_num The page number to be replaced.
 * @return 0 indicating successful page replacement.
 */
int FIFOReplacement::replace_page(int page_num)
{
    int victim = frame_queue[queue_head];
    page_table[victim].valid = false;
    page_table[page_num].valid = true;
    page_table[page_num].frame_num = page_table[victim].frame_num;
    frame_queue[queue_head] = page_num;
    queue_head++;
    if (queue_head == total_frames)
    {
        queue_head = 0;
    }
    num_page_faults++;
    num_page_replacements++;
    return 0;
}