/******************************************************************************/
// File : main.c
// Function : Example program form stack
/******************************************************************************/
// Version : 1.0    Date : 14/06/2021    Author : tartifP
// Modification :
//     - Original
/******************************************************************************/

/******************************************************************************/
/*                                 Includes                                   */
/******************************************************************************/

#include <time.h>       // for rand init
#include <stdio.h>      // printf
#include <stdlib.h>     // rand
#include <stdint.h>     // uint...

#include "GSTACK.h"       // GSTACK data type

/******************************************************************************/
/*                                 Define                                     */
/******************************************************************************/

#define GSTACK_SIZE     5   // GSTACK data size

/******************************************************************************/
/*                                 Main    function                           */
/******************************************************************************/

/**
* Main function
* Example of usage of the gstack with 8-bit integer
*/
int main(int argc, char** argv)
{
    // Data declaration
    GSTACK_STATUS   gstack_status;              // Status of gstack
    GSTACK          gstack;                     // Stack data type
    uint8_t         container[GSTACK_SIZE];     // Data container for stack (array of element)
    uint8_t         element;                    // Data type of an element
    size_t          size;                       // Size type of stack
    
    // GSTACK init
    gstack_status = GSTACK_Initialise(&gstack, container, sizeof(container), sizeof(uint8_t), GSTACK_SIZE);
    if(gstack_status == GSTACK_STATUS_INIT_ERROR)
	{
        printf("Error at initialisation, check input data\r\n");
		return EXIT_FAILURE;
	}
    
    // Push one element into the stack
	element = 10;
    gstack_status = GSTACK_Push(&gstack, &element);
    printf("Element push : %d\r\n", element);
	
	// Peek the element
    gstack_status = GSTACK_Peek(&gstack, &element);
    printf("Element peek : %d\r\n", element);
	
	// Test if the stack is full
    if(GSTACK_IsFull(&gstack))
		printf("GSTACK is full\r\n");
	
	// Pop an element
    gstack_status = GSTACK_Pop(&gstack, &element);
    printf("Element pop : %d\r\n", element);

    // Test if the stack is empty
    if(GSTACK_IsEmpty(&gstack))
		printf("GSTACK is empty\r\n");
    
    // Get stack length
    gstack_status = GSTACK_GetLength(&gstack, &size);
    printf("GSTACK Lenght : %d\r\n", size);
    
    return (EXIT_SUCCESS);
}