/**
 * Assignment 5: Page replacement algorithms
 * @file lru_replacement.h
 * @author Salman Burhan, Nathaniel Vandenberg
 * @brief A class implementing the LRU page replacement algorithms
 * @version 0.1
 */

#pragma once

#include "replacement.h"
#include <list>
#include <unordered_map>

/**
 * @brief A class to simulate the least recently used (LRU) page
 *        replacement algorithm.
 */
/**
 * @class LRUReplacement
 * @brief Represents a Least Recently Used (LRU) page replacement algorithm.
 *
 * This class inherits from the Replacement class and implements the LRU page
 * replacement algorithm. It keeps track of a list of frames and a map of page
 * numbers to frame list iterators. The LRUReplacement class provides methods
 * to access pages already in physical memory, load pages into free frames,
 * and replace pages when there are no free frames available.
 */
class LRUReplacement : public Replacement
{
private:
    list<int> frame_list;                        // list of frames
    unordered_map<int, list<int>::iterator> map; // map of page numbers to frame list iterators

public:
    /**
     * @brief Constructor
     * @param num_pages
     * @param num_frames
     */
    LRUReplacement(int num_pages, int num_frames);

    /**
     * @brief Destructor
     */
    virtual ~LRUReplacement();

    /**
     * @brief Accesss a page alreay in physical memory
     * It may be overridden in a subclass
     * @param page_num The logical page number.
     */
    virtual void touch_page(int page_num);

    /**
     * @brief Access an invalid page, but free frames are available.
     * Assign the page to an available frame, not replacement needed
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