/**
 * Assignment 5: Page replacement algorithms
 * @file replacement.h
 * @author Salman Burhan, Nathaniel Vandenberg
 * @brief A base class for different page replacement algorithms.
 * @version 0.1
 */

#pragma once

#include "pagetable.h"

/**
 * @class Replacement
 * @brief Base class for page replacement algorithms.
 * @details
 * This class provides the basic functionality for simulating page
 * replacement algorithms.
 * It keeps track of the page table, number of frames, number of references,
 * number of page faults, number of page replacements, total frames,
 * and total pages.
 *
 * Derived classes can override the virtual functions to implement specific
 * page replacement algorithms. e.g. FIFO or LRU, should be subclass of this.
 */
class Replacement
{
protected:
    PageTable page_table;          // The page table
    int num_frames = 0;            // Number of available free frames
    int num_references = 0;        // Number of page references
    int num_page_faults = 0;       // Number of page faults
    int num_page_replacements = 0; // Number of page replacements
    int total_frames;              // Total number of frames
    int total_pages;               // Total number of logical pages

public:
    /**
     * @brief Constructor
     * @param num_pages Total number of logical pages for the simulation.
     * @param num_frames Total number of available free frames.
     */
    Replacement(int num_pages, int num_frames);

    /**
     * @brief Destructor
     */
    virtual ~Replacement();

    /**
     * @brief Simulate a single page access.
     *
     * If the page is valid, it calls the touch_page function.
     *
     * If the page is not valid but free frames are available,
     * it calls the load_page function.
     *
     * If the page is not valid and there is no free frame,
     * it calls the replace_page function.
     *
     * @param page_num The logical page number.
     * @param is_write Whether this access is a memory write.
     * @return True if it's a page fault, false otherwise.
     */
    virtual bool access_page(int page_num, bool is_write = false);

    /**
     * @brief Access a page already in physical memory.
     *
     * This function may be overridden in a subclass.
     *
     * @param page_num The logical page number.
     */
    virtual void touch_page(int page_num) {}

    /**
     * @brief Access an invalid page, but free frames are available.
     *
     * Assign the page to an available frame, no replacement needed.
     * This function may be overridden in a subclass.
     *
     * @param page_num The logical page number.
     */
    virtual void load_page(int page_num) {}

    /**
     * @brief Access an invalid page and no free frame is available.
     *
     * Select a victim page to be replaced.
     * This is a pure virtual function to be implemented in specific
     * replacement subclasses.
     *
     * @param page_num The logical page number of the desired page.
     * @return The selected victim page number.
     */
    virtual int replace_page(int page_num) = 0;

    /**
     * @brief Get the ith entry of the page table.
     *
     * @param page_num The logical page number.
     * @return The page entry.
     */
    PageEntry getPageEntry(int page_num)
    {
        return page_table[page_num];
    }

    /**
     * @brief Print the statistics of the simulation.
     */
    void print_statistics() const;
};