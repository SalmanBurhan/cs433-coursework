/**
 * Assignment 5: Page replacement algorithms
 * @file lifo_replacement.cpp
 * @author Salman Burhan, Nathaniel Vandenberg
 * @brief A class implementing the Last in First Out (LIFO) page replacement algorithms
 * @version 0.1
 */

#include "lifo_replacement.h"

/**
 * @brief Constructs a LIFOReplacement object with the specified number of
 * pages and frames.
 *
 * @param num_pages The total number of pages.
 * @param num_frames The number of frames available for page replacement.
 */
LIFOReplacement::LIFOReplacement(int num_pages, int num_frames)
    : Replacement(num_pages, num_frames)
{
    total_frames = num_frames;
}

/**
 * Destructor for the LIFOReplacement class.
 */
LIFOReplacement::~LIFOReplacement()
{
    frame_queue.clear();
}

/**
 * Loads a page into the LIFO replacement algorithm.
 *
 * @param page_num The number of the page to be loaded.
 */
void LIFOReplacement::load_page(int page_num)
{
    // sets page to valid, assigns `frame_number`
    page_table[page_num].valid = true;
    page_table[page_num].frame_num = frame_number;

    // decrements `total_frames` , increments `frame_number`
    total_frames--;
    frame_number++;

    // adds new page to back of queue.
    frame_queue.push_back(page_num);
}

/**
 * Replaces a page using the LIFO (Last In, First Out) replacement algorithm.
 *
 * @param page_num The page number to be replaced.
 * @return The page number that was replaced.
 */
int LIFOReplacement::replace_page(int page_num)
{
    // gets back of queue, pops it
    int temp = frame_queue.back();
    frame_queue.pop_back();

    // sets page to invalid, assigns `frame_number`
    page_table[temp].valid = false;
    page_table[page_num].valid = true;
    page_table[page_num].frame_num = page_table[temp].frame_num;

    // adds new page to back of queue.
    frame_queue.push_back(page_num);

    return 0;
}