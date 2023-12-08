/**
 * Assignment 5: Page replacement algorithms
 * @file pagetable.h
 * @author Salman Burhan, Nathaniel Vandenberg
 * @brief This class represents a traditional pagetable data structure.
 * @version 0.1
 */

#pragma once

#include <vector>
using namespace std;

/**
 * @brief A page table entry.
 *
 * The PageEntry class represents a page table entry.
 * Each page in the logical memory has one corresponding PageEntry
 * in the page table. It contains the following fields:
 * @param frame_num: The frame number of the page in the physical memory.
 * @param valid: A flag indicating whether the page is valid or not.
 * @param dirty: A flag indicating whether the page has been modified or not.
 */
class PageEntry
{
public:
    int frame_num;
    bool valid = false;
    bool dirty = false;
};

/**
 * @brief A page table data structure.
 *
 * The PageTable class represents a page table, which is used
 * to map logical pages to physical frames in memory. It provides
 * methods to access and modify the page table entries. The size of
 * the page table should be equal to the number of pages in the
 * logical memory.
 */
class PageTable
{
private:
    vector<PageEntry> pages; // An array of page entries representing the page table.

public:
    /**
     * @brief Constructor for PageTable class.
     * @param num_pages The number of pages in the logical memory.
     */
    PageTable(int num_pages);

    /**
     * @brief Destructor for PageTable class.
     */
    ~PageTable();

    /**
     * @brief Access a page in the page table.
     * @param i The index of the page in the page table.
     * @return A reference to the PageEntry object representing the page.
     */
    PageEntry &operator[](int i)
    {
        return pages[i];
    }
};