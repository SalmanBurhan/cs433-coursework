/**
 * Assignment 5: Page replacement algorithms
 * @file replacement.cpp
 * @author Salman Burhan, Nathaniel Vandenberg
 * @brief A base class for different page replacement algorithms.
 * @version 0.1
 */

#include <iostream>
#include "replacement.h"

/**
 * @brief Constructs a Replacement object with the specified number of
 *        pages and frames.
 *
 * @param num_pages The total number of pages.
 * @param num_frames The total number of frames.
 */
Replacement::Replacement(int num_pages, int num_frames) : page_table(num_pages)
{
    this->total_frames = num_frames;
    this->total_pages = num_pages;
}

/**
 * Destructor for the Replacement class.
 */
Replacement::~Replacement() {}

/**
 * Accesses a page in the page table.
 *
 * @param page_num The page number to access.
 * @param is_write A boolean indicating whether the access is a write operation.
 * @return A boolean indicating whether a page fault occurred during the access.
 */
bool Replacement::access_page(int page_num, bool is_write)
{
    num_references++;
    // If the page is valid, it calls the touch_page function.
    if (page_table[page_num].valid)
    {
        touch_page(page_num);
        return false;
    }
    // If the page is not valid but free frames are available,
    // it calls the load_page function.
    else if (num_frames < total_frames)
    {
        load_page(page_num);
        return true;
    }
    // If the page is not valid and there is no free frame,
    // it calls the replace_page function.
    else
    {
        replace_page(page_num);
        return true;
    }
}

/**
 * Prints the statistics of the Replacement object.
 * This function displays the number of references, page faults, and page replacements.
 */
void Replacement::print_statistics() const
{
    std::cout << "Number of references: \t\t" << num_references << std::endl;
    std::cout << "Number of page faults: \t\t" << num_page_faults << std::endl;
    std::cout << "Number of page replacements: \t" << num_page_replacements << std::endl;
}