/******************************************************************************/
// File : GSTACK.h
// Function : Generic fixed size stack implementation
/******************************************************************************/
// Version : 1.0    Date : 14/06/2021    Author : tartifP
// Modification :
//     - Original
/******************************************************************************/

#ifndef GSTACK_H
#define GSTACK_H

/******************************************************************************/
/*                                 Define                                     */
/******************************************************************************/

#define GSTACK_DEBUG            0   // Debug mode, clear memory at init and after pop (1 = debug, 0 = no debug)
#define GSTACK_GROWS_DOWNWARD   1   // Define the grows direction of the stack (1 = downward, 0 = upward)

/******************************************************************************/
/*                                 Includes                                   */
/******************************************************************************/

#include <stdint.h>     // uint...
#include <stddef.h>     // size_t
#include <stdbool.h>    // boolean

/******************************************************************************/
/*                              Data definition                               */
/******************************************************************************/

// Return type of GSTACK function
typedef enum {
    GSTACK_STATUS_OK = 0,       // No problem
    GSTACK_STATUS_INIT_ERROR,   // Initialisation problem        
    GSTACK_STATUS_NULL_PTR,     // Bad argument to function (NULL ptr)
    GSTACK_STATUS_FULL,         // Stack full error
    GSTACK_STATUS_EMPTY,        // Stack empty error
} GSTACK_STATUS;

// Stack struture definition
typedef struct {
    void*   container;          // Pointer de base address container stack
    size_t  container_size;     // Size (in bytes) of the container (to avoid stack overflow)
    size_t  element_size;       // Size (in bytes) of an element of the stack
    size_t  element_count;      // Current number of element in the stack
    size_t  element_maxnumber;  // Maximum number of element in the stack
} GSTACK;

/******************************************************************************/
/*                          Public function defintion                         */
/******************************************************************************/

// Initialisation
GSTACK_STATUS GSTACK_Initialise(GSTACK* _gstack, void* _container, size_t _container_size, size_t _element_size, size_t _element_maxnumber);

// Base function
GSTACK_STATUS GSTACK_Push(GSTACK* _gstack, void* _element);
GSTACK_STATUS GSTACK_Pop(GSTACK* _gstack, void* _element);
GSTACK_STATUS GSTACK_Peek(GSTACK* _gstack, void* _element);

// Control function
bool GSTACK_IsEmpty(GSTACK* _gstack);
bool GSTACK_IsFull(GSTACK* _gstack);
GSTACK_STATUS GSTACK_GetStatus(GSTACK* _gstack);
GSTACK_STATUS GSTACK_GetLength(GSTACK* _gstack, size_t* _size);

#endif /* GSTACK_H */

