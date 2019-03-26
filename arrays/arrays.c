#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct Array
{
  int capacity;    // How many elements can this array hold?
  int count;       // How many states does the array currently hold?
  char **elements; // The string elements contained in the array
} Array;

/************************************
 *
 *   CREATE, DESTROY, RESIZE FUNCTIONS
 *
 ************************************/

/*****
 * Allocate memory for a new array
 *****/
Array *create_array(int capacity)
{
  // Allocate memory for the Array struct

  // for the type Array struct assign arr pointer to memory allocation and pass in sizeof Array which allocates enough bytes for the Array
  Array *arr = malloc(sizeof(Array));

  // Set initial values for capacity and count
  // asign capacity to the new array's capacity
  arr->capacity = capacity;
  // assign 0 to the new array's count
  arr->count = 0;

  // Allocate memory for elements
  // multiply the capacity to the sizeof char pointer, memory allocate and assign it to the elements array from the newly created array
  arr->elements = malloc(capacity * sizeof(char *));
  // return array
  return arr;
}

/*****
 * Free memory for an array and all of its stored elements
 *****/
void destroy_array(Array *arr)
{

  // Free all elements
  // same as free(arr->elements)?
  for (int i = 0; i < arr->count; i++)
  {
    free(arr->elements[i]);
  }
  free(arr->elements);
  // Free array
  free(arr);
}

/*****
 * Create a new elements array with double capacity and copy elements
 * from old to new
 *****/
void resize_array(Array *arr)
{

  // Create a new element storage with double capacity
  // create new elements array pointer, memory allocate double the capacity of arr with char type bytes
  char **new_elements = malloc((arr->capacity * 2) * sizeof(char *));

  // Copy elements into the new storage
  // copy using realloc, arr elements, double capacity of original capacity, enough bytes for char
  // accepts ptr and size of mem
  // arr->elements = realloc(arr->elements, (arr->capacity * 2) * sizeof(char *));
  for (int i = 0; i < arr->count; i++)
  {
    new_elements[i] = arr->elements[i];
  }

  // Free the old elements array (but NOT the strings they point to)
  free(arr->elements);
  // Update the elements and capacity to new values
  // capacity of arr will now have double capacity
  arr->capacity = arr->capacity * 2;
  // assign elements to new_elements with double capacity
  arr->elements = new_elements;
}

/************************************
 *
 *   ARRAY FUNCTIONS
 *
 ************************************/

/*****
 * Return the element in the array at the given index.
 *
 * Throw an error if the index is out of range.
 *****/
char *arr_read(Array *arr, int index)
{

  // Throw an error if the index is greater or equal than the current count
  if (index >= arr->count)
  {
    printf("Error index is greater than current count");
    return NULL;
  }
  // Otherwise, return the element at the given index
  else
    return arr->elements[index];
}

/*****
 * Insert an element to the array at the given index
 *****/
void arr_insert(Array *arr, char *element, int index)
{

  // Throw an error if the index is greater than the current count
  if (index > arr->count)
  {
    printf("error, index is greater than current count");
    exit(1);
  }
  // Resize the array if the number of elements is over capacity
  if (arr->count >= arr->capacity)
  {
    resize_array(arr);
  }

  // Move every element after the insert index to the right one position
  // initialize current element pointer at current index
  char *elem = arr->elements[index];
  // initialize next element pointer
  char *next_elem;
  // start loop at index i, increment i, stop at arr count
  for (int i = index; i <= arr->count; i++)
  {
    // do something
    // assign the next element pointer to the value of i+1
    next_elem = arr->elements[i + 1];
    // assign element pointer to the next value of the elements array
    arr->elements[i + 1] = elem;
    // assign current element pointer to next_element pointer
    elem = next_elem;
  }
  // Copy the element and add it to the array
  // assign the value of the element to the elements string at index
  char *dup = strdup(element);
  arr->elements[index] = dup;
  // Increment count by 1
  arr->count++;
}

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element)
{

  // Resize the array if the number of elements is over capacity
  if (arr->count >= arr->capacity)
  {
    resize_array(arr);
  }
  // or throw an error if resize isn't implemented yet.
  // else
  // {
  //   printf("error resize_array hasn't been implemented yet.");
  //   exit(1);
  // }

  // Copy the element and add it to the end of the array
  // initialize copy pointer to string duplicate, pass in element
  char *copy = strdup(element);
  // assign the end of the elements array to copy
  arr->elements[arr->count] = copy;
  // Increment count by 1
  arr->count++;
}

/*****
 * Remove the first occurence of the given element from the array,
 * then shift every element after that occurence to the left one slot.
 *
 * Throw an error if the value is not found.
 *****/
void arr_remove(Array *arr, char *element)
{

  // Search for the first occurence of the element and remove it.
  // Don't forget to free its memory!
  // initialize index;
  int index;
  // loop through until arr until end of count, initialize int to 0, increment
  for (int i = 0; i < arr->count; i++)
  {
    // if arr of elements at index i equals passed in element
    if (strcmp(arr->elements[i], element) == 0)
    {
      // assign index which is the first occurance of element to i
      index = i;
      // free memory of elements at index of i
      free(arr->elements[i]);
      // break, exit loop, only need to return first occurence
      break;
    }
    // if element does not exist
    // else
    // {
    //   // error out, exit
    //   printf("element does not exist");
    //   exit(1);
    // }
  }

  // Shift over every element after the removed element to the left one position
  // for loop, assign int j to index, loop until count
  for (int j = index; j < arr->count; j++)
  {
    // assign element at j to element at j+1
    arr->elements[j] = arr->elements[j + 1];
  }
  // Decrement count by 1
  arr->count--;
}

/*****
 * Utility function to print an array.
 *****/
void arr_print(Array *arr)
{
  printf("[");
  for (int i = 0; i < arr->count; i++)
  {
    printf("%s", arr->elements[i]);
    if (i != arr->count - 1)
    {
      printf(",");
    }
  }
  printf("]\n");
}

#ifndef TESTING
int main(void)
{

  Array *arr = create_array(1);

  arr_insert(arr, "STRING1", 0);
  arr_append(arr, "STRING4");
  arr_insert(arr, "STRING2", 0);
  arr_insert(arr, "STRING3", 1);
  arr_print(arr);
  arr_remove(arr, "STRING3");
  arr_print(arr);

  destroy_array(arr);

  return 0;
}
#endif
