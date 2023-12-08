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
    frame_stack = new int[num_frames];
}

/**
 * Destructor for the LIFOReplacement class.
 */
LIFOReplacement::~LIFOReplacement()
{
    delete[] frame_stack;
}

/**
 * @brief Copy constructor for LIFOReplacement class.
 *
 * @param other The LIFOReplacement object to be copied.
 */
LIFOReplacement::LIFOReplacement(const LIFOReplacement &other)
    : Replacement(other)
{
    frame_stack = new int[other.total_frames];
    for (int i = 0; i < other.total_frames; i++)
    {
        frame_stack[i] = other.frame_stack[i];
    }
}

/**
 * Loads a page into the LIFO replacement algorithm.
 *
 * @param page_num The number of the page to be loaded.
 */
void LIFOReplacement::load_page(int page_num)
{
    page_table[page_num].valid = true;
    page_table[page_num].frame_num = stack_top;
    frame_stack[stack_top] = page_num;
    stack_top++;
    num_page_faults++;
}

/**
 * Replaces a page using the LIFO (Last In, First Out) replacement algorithm.
 *
 * @param page_num The page number to be replaced.
 * @return The page number that was replaced.
 */
int LIFOReplacement::replace_page(int page_num)
{
    int frame_num = page_table[page_num].frame_num;
    page_table[page_num].valid = true;
    page_table[page_num].frame_num = frame_num;
    frame_stack[stack_top] = page_num;
    stack_top++;
    num_page_faults++;
    return 0;
}