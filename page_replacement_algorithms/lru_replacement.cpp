/**
 * Assignment 5: Page replacement algorithms
 * @file lru_replacement.cpp
 * @author Salman Burhan, Nathaniel Vandenberg
 * @brief A class implementing the LRU page replacement algorithms
 * @version 0.1
 */

#include "lru_replacement.h"

/**
 * @brief Constructs an LRUReplacement object.
 *
 * @param num_pages The total number of pages in the system.
 * @param num_frames The number of frames available in the memory.
 */
LRUReplacement::LRUReplacement(int num_pages, int num_frames)
    : Replacement(num_pages, num_frames)
{
    total_frames = num_frames;
}

/**
 * Destructor for LRUReplacement class.
 */
LRUReplacement::~LRUReplacement()
{
    frame_list.clear();
}

/**
 * Accesss a page alreay in physical memory.
 * It may be overridden in a subclass.
 *
 * @param page_num The logical page number.
 */
void LRUReplacement::touch_page(int page_num)
{
    // deletes node from list
    frame_list.erase(map[page_num]);

    // adds new node to front
    frame_list.push_front(page_num);

    // sets new key in map
    map[page_num] = frame_list.begin();
}

/**
 * Access an invalid page, but free frames are available.
 * Assign the page to an available frame, no replacement needed.
 *
 * @param page_num The logical page number.
 */
void LRUReplacement::load_page(int page_num)
{
    // sets page to valid, assigns `frame_number`
    page_table[page_num].valid = true;
    page_table[page_num].frame_num = frame_number;

    // decrements `total_frames` , increments `frame_number`
    total_frames--;
    frame_number++;

    // pushes new page to front of list, sets its key in map.
    frame_list.push_front(page_num);
    map[page_num] = frame_list.begin();
}

/**
 * Access an invalid page, and there is no free frame.
 * Replace the page with the page that has been in memory the longest.
 *
 * @param page_num The logical page number.
 * @return Selected victim page #
 */
int LRUReplacement::replace_page(int page_num)
{
    // gets back of list, pops it
    int temp = frame_list.back();
    frame_list.pop_back();

    // sets old page to invalid, new page to valid
    page_table[temp].valid = false;
    page_table[page_num].valid = true;

    // sets new page's frame number to old page's frame number
    page_table[page_num].frame_num = page_table[temp].frame_num;

    // erases old page's key in map
    map.erase(temp);

    // pushes new page to front of list, sets its key in map.
    frame_list.push_front(page_num);
    map[page_num] = frame_list.begin();

    return 0;
}