/**
 * Assignment 5: Page replacement algorithms
 * @file lifo_replacement.h
 * @author Salman Burhan, Nathaniel Vandenberg
 * @brief A class implementing the LIFO page replacement algorithms
 * @version 0.1
 */

#pragma once

// Remember to add comments to your code

#include "replacement.h"

/**
 * @class LIFOReplacement
 * @brief Represents a Last-In-First-Out (LIFO) page replacement algorithm.
 *
 * This class inherits from the Replacement class and implements the LIFO
 * page replacement algorithm.
 * It maintains a stack of frames and replaces the page that has been in
 * memory the longest when there are no free frames available.
 */
class LIFOReplacement : public Replacement
{
private:
    vector<int> frame_queue;

public:
    /**
     * @brief Constructor
     * @param num_pages Total number of available free frames.
     * @param num_frames Total number of free frames.
     */
    LIFOReplacement(int num_pages, int num_frames);

    /**
     * @brief Destructor
     */
    virtual ~LIFOReplacement();

    /**
     * @brief Access an invalid page, but free frames are available.
     * Assign the page to an available  frame, not replacement needed
     * @param page_num The logical page number.
     */
    virtual void load_page(int page_num);

    /**
     * @brief Access an invalid page, and there is no free frame.
     * Replace the page with the page that has been in memory the longest.
     * @param page_num The logical page number.
     * @return Selected victim page #
     */
    virtual int replace_page(int page_num);
};
