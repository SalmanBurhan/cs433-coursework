/**
 * Assignment 4: Producer Consumer Problem
 * @file buffer.cpp
 * @author ??? (TODO: your name)
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

Buffer::Buffer(int size) {
    maxSize = size;
    count = 0;
    items.resize(maxSize);
}

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
    items.push_back(item);
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
    *item = items.back();
    items.pop_back();
    return true;
}

/**
 * @brief Get the size of the buffer
 * @return the size of the buffer
 */
int Buffer::get_size() { return maxSize; }

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

bool Buffer::is_full() { return count == maxSize; }

/**
 * @brief Print the buffer
 */
void Buffer::print_buffer() {
    for (const buffer_item &item : items) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}
