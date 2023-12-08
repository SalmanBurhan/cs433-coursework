/**
 * Assignment 5: Page replacement algorithms
 * @file fifo_replacement.h
 * @author Salman Burhan, Nathaniel Vandenberg
 * @brief A class implementing the FIFO page replacement algorithms
 * @version 0.1
 */

#pragma once

#include "replacement.h"

/**
 * @brief The First-In-First-Out (FIFO) page replacement algorithm.
 *
 * The FIFOReplacement class is responsible for managing the frame queue
 * and performing page replacement operations based on the FIFO algorithm.
 * It keeps track of the available free frames and replaces pages that have
 * been in memory the longest when there are no free frames available.
 */
class FIFOReplacement : public Replacement
{
private:
    int *frame_queue;   // Array to store the frame queue
    int queue_head = 0; // Index of the head of the queue
    int queue_tail = 0; // Index of the tail of the queue

public:
    /**
     * @brief Constructor for the FIFOReplacement class.
     *
     * @param num_pages Total number of available free frames.
     * @param num_frames Total number of free frames.
     */
    FIFOReplacement(int num_pages, int num_frames);

    /**
     * @brief Destructor for the FIFOReplacement class.
     */
    virtual ~FIFOReplacement();

    /**
     * @brief Copy constructor for FIFOReplacement class.
     * Included since it has dynamic memory/resource allocation(s)
     *
     * @param other The object to be copied.
     */
    FIFOReplacement(const FIFOReplacement &other);

    /**
     * @brief Access an invalid page when free frames are available.
     *
     * This function assigns the given page to an available frame without
     * the need for replacement.
     *
     * @param page_num The logical page number.
     */
    virtual void load_page(int page_num);

    /**
     * @brief Access an invalid page when there are no free frames.
     *
     * This function replaces the page with the page that has been in memory
     * the longest, based on the FIFO algorithm.
     *
     * @param page_num The logical page number.
     * @return The selected victim page number.
     */
    virtual int replace_page(int page_num);
};
