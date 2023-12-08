/**
 * Assignment 4: Producer Consumer Problem
 * @file buffer.cpp
 * @author Salman Burhan
 * @brief Implementation file for the buffer class
 * @version 0.1
 */

// You must complete the all parts marked as "TODO". Delete "TODO" after you are
// done. Remember to add sufficient and clear comments to your code
#include "buffer.h"

#include <iostream>

/**
 * @brief The bounded buffer class. The number of items in the buffer cannot
 * exceed the size of the buffer.
 */

Buffer::Buffer() { count = 0; }

/**
 * @brief Destroy the Buffer object
 */
Buffer::~Buffer() {}

/**
 * @brief Insert an item into the buffer
 * @param item the item to insert
 * @return true if successful
 * @return false if not successful
 */
bool Buffer::insert_item(buffer_item item) {
    if (is_full()) {
        return false;
    }

    buffer[count] = item;
    count++;
    return true;
}
/**
 * @brief Remove an item from the buffer
 * @param item the item to remove
 * @return true if successful
 * @return false if not successful
 */
bool Buffer::remove_item(buffer_item *item) {
    if (is_empty()) {
        return false;
    }

    buffer_item popped_item = buffer[0];
    *item = popped_item;
    // Shift remaining elements
    for (int i = 0; i < get_size() - 1; ++i) {
        buffer[i] = buffer[i + 1];
    }
    count--;

    return true;
}

/**
 * @brief Get the size of the buffer
 * @return the size of the buffer
 */
int Buffer::get_size() { return size; }

/**
 * @brief Get the number of items in the buffer
 * @return the number of items in the buffer
 */
int Buffer::get_count() { return count; }

/**
 * @brief Chceck if the buffer is empty
 * @return true if the buffer is empty, else false
 */
bool Buffer::is_empty() { return count == 0; }

/**
 * @brief Check if the buffer is full
 * @return true if the buffer is full, else false
 */

bool Buffer::is_full() { return count == get_size(); }

/**
 * @brief Print the buffer
 */
void Buffer::print_buffer() {
    std::cout << "Buffer: [";
    for (int i = 0; i < get_count(); i++) {
        if (i == 0) {
            if (count == 1) {
                std::cout << buffer[i];
            } else {
                std::cout << buffer[i] << ",";
            }
        } else if (i == count - 1) {
            std::cout << " " << buffer[i];
        } else {
            std::cout << " " << buffer[i] << ",";
        }
    }
    std::cout << "]" << std::endl;
}
