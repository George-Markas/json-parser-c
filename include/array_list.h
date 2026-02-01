#pragma once

#include <stddef.h>
#include <stdbool.h>

#define INITIAL_CAPACITY 8
#define BYTE_CAPACITY (array_list->capacity * array_list->element_size)
#define LENGTH_OFFSET (array_list->data + (array_list->length * array_list->element_size))
#define INDEX_OFFSET(index) (array_list->data + index * array_list->element_size)
#define FREE(ptr) free(ptr); ptr = NULL

typedef struct ArrayList {
    void *data;
    size_t length; // Current number of elements
    size_t capacity; // Max number of elements
    size_t element_size; // The byte size an element
} AList_t;

/**
 * @brief Create an array list.
 * @param element_size The byte size of a single element.
 * @return Pointer to new the array list or NULL on error.
 */
AList_t *array_list_new(size_t element_size);

/**
 * @brief Append a value to an array list.
 * @param array_list The array list to append to.
 * @param val Value to append.
 * @return True if the array list was modified, false if it wasn't.
 */
bool array_list_add(AList_t *array_list, const void *val);

/**
 * @brief Access a value at a specific index of an array list.
 * @param array_list The array list to access.
 * @param index The index of the value.
 * @return A pointer to the value or NULL on error.
 */
void *array_list_get(const AList_t *array_list, size_t index);

/**
 * @brief Write a value at a specific index of an array list.
 * This will overwrite existing values.
 * @param array_list The array list to write to.
 * @param index The index to write at.
 * @param val The value to write.
 * @return True if the array list was modified, false if it wasn't.
 */
bool array_list_set(const AList_t *array_list, size_t index, const void *val);

/**
 * @brief Remove a value from an array list.
 * @param array_list The array list to remove from.
 * @return True if the array list was modified, false if it wasn't.
 */
bool array_list_remove(AList_t *array_list);

/**
 * @brief Free an array list.
 * @param array_list The array list to free.
 */
void array_list_delete(AList_t *array_list);