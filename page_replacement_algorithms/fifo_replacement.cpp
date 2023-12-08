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
    total_frames = num_frames;
}

/**
 * Destructor for the FIFOReplacement class.
 * Frees the memory allocated for the frame queue.
 */
FIFOReplacement::~FIFOReplacement()
{
    while (!frame_queue.empty())
        frame_queue.pop();
}

/**
 * Loads a page into the page table using the FIFO replacement algorithm.
 *
 * @param page_num The number of the page to be loaded.
 */
void FIFOReplacement::load_page(int page_num)
{
    // sets page to valid, assigns `frame_number`
    page_table[page_num].valid = true;
    page_table[page_num].frame_num = frame_number;

    // decrements `total_frames` , increments `frame_number`
    total_frames--;
    frame_number++;

    // adds new node to back
    frame_queue.push(page_num);
}

/**
 * Replaces a page in the FIFO replacement algorithm.
 *
 * @param page_num The page number to be replaced.
 * @return 0 indicating successful page replacement.
 */
int FIFOReplacement::replace_page(int page_num)
{
    // gets front of queue, pops it
    int temp = frame_queue.front();
    frame_queue.pop();

    // sets old page to invalid, new page to valid
    page_table[temp].valid = false;
    page_table[page_num].valid = true;

    // sets new page's frame number to old page's frame number.
    page_table[page_num].frame_num = page_table[temp].frame_num;

    // adds new page to back of queue.
    frame_queue.push(page_num);

    return 0;
}