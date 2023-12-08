/**
 * Assignment 5: Page replacement algorithms
 * @file pagetable.cpp
 * @author Salman Burhan, Nathaniel Vandenberg
 * @brief This class represents a traditional page table data structure.
 * @version 0.1
 */

#include "pagetable.h"

/**
 * @brief Constructs a PageTable object with the specified number of pages.
 *
 * @param num_pages The number of pages in the PageTable.
 */
PageTable::PageTable(int num_pages)
{
    this->pages.resize(num_pages);
}

/**
 * @brief Destructor for the PageTable class.
 *
 * This destructor clears the pages vector, freeing up the memory occupied
 * by the page entries.
 */
PageTable::~PageTable()
{
    this->pages.clear();
}