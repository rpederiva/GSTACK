/******************************************************************************/
// File : GSTACK.c
// Function : Generic fixed size stack implementation
/******************************************************************************/
// Version : 1.0    Date : 14/06/2021    Author : tartifP
// Modification :
//     - Original
/******************************************************************************/

/******************************************************************************/
/*                                 Includes                                   */
/******************************************************************************/

#include "GSTACK.h" // Header
#include <string.h> // memset

/******************************************************************************/
/*                        Public function implementation                      */
/******************************************************************************/

/**
 * Initialisation of a generic stack
 * @param _gstack : GSTACK ptr
 * @param _container : Container base ptr
 * @param _container_size : Container size (in bytes)
 * @param _element_size : Elements size (in bytes)
 * @param _element_maxnumber : Element max number
 * @return GSTACK_STATUS
 */
GSTACK_STATUS GSTACK_Initialise(GSTACK* _gstack, void* _container, size_t _container_size, size_t _element_size, size_t _element_maxnumber)
{
    // Check if element can fit in container (protect segfaut error)
    if(_container_size < _element_size * _element_maxnumber)
        return GSTACK_STATUS_INIT_ERROR;
    
    // Check if ptr arent NULL
    if(_gstack == NULL || _container == NULL)
        return GSTACK_STATUS_NULL_PTR;
    
    // Initialisation
    _gstack->container          = _container;
    _gstack->container_size     = _container_size;
    _gstack->element_size       = _element_size;
    _gstack->element_maxnumber  = _element_maxnumber;
#if GSTACK_GROWS_DOWNWARD == 1
    _gstack->element_count      = _element_maxnumber;
#else
    _gstack->element_count      = 0;
#endif

#if GSTACK_DEBUG == 1
    memset(_gstack->container, 0, _gstack->container_size);
#endif
    
    return GSTACK_STATUS_OK;
}

/**
 * Push a element into the stack
 * @param _gstack : Stack to add an element
 * @param _element : Element to add
 * @return GSTACK_STATUS
 */
GSTACK_STATUS GSTACK_Push(GSTACK* _gstack, void* _element)
{
    // Check if ptr arent NULL
    if(_gstack == NULL || _element == NULL)
        return GSTACK_STATUS_NULL_PTR;
    
   // Check if stack is already full
    if(GSTACK_IsFull(_gstack))
        return GSTACK_STATUS_FULL;
    
    // Push an element and update index
#if GSTACK_GROWS_DOWNWARD == 1
    _gstack->element_count--;
    memcpy(_gstack->container+(_gstack->element_size*_gstack->element_count), _element, _gstack->element_size);
#else
    memcpy(_gstack->container+(_gstack->element_size*_gstack->element_count), _element, _gstack->element_size);
    _gstack->element_count++;
#endif
    
    return GSTACK_STATUS_OK;
}

/**
 * Pop an element out of the stack
 * @param _gstack : Stack to remove an element
 * @param _element : returned element removed
 * @return GSTACK_STATUS
 */
GSTACK_STATUS GSTACK_Pop(GSTACK* _gstack, void* _element)
{
    // Check if ptr arent NULL
    if(_gstack == NULL || _element == NULL)
        return GSTACK_STATUS_NULL_PTR;
    
   // Check if stack isnst empty
    if(GSTACK_IsEmpty(_gstack))
        return GSTACK_STATUS_EMPTY;
    
    // Pop an element and update index
#if GSTACK_GROWS_DOWNWARD == 1
    memcpy(_element, _gstack->container+(_gstack->element_size*_gstack->element_count), _gstack->element_size);
    #if GSTACK_DEBUG == 1
    memset(_gstack->container+(_gstack->element_size*_gstack->element_count), 0, _gstack->element_size);
    #endif
    _gstack->element_count++;
#else
    _gstack->element_count--;
    memcpy(_element, _gstack->container+(_gstack->element_size*(_gstack->element_count)), _gstack->element_size);
    #if GSTACK_DEBUG == 1
    memset(_gstack->container+(_gstack->element_size*_gstack->element_count), 0, _gstack->element_size);
    #endif
#endif

    return GSTACK_STATUS_OK;
}

/**
 * Peek the first element of the stack
 * (See him without remove it from the stack)
 * @param _gstack : Stack  to see first element
 * @param _element : Returned first element of the stack
 * @return GSTACK_STATUS
 */
GSTACK_STATUS GSTACK_Peek(GSTACK* _gstack, void* _element)
{
    // Check if ptr arent NULL
    if(_gstack == NULL || _element == NULL)
        return GSTACK_STATUS_NULL_PTR;
    
   // Check if stack isnst empty
    if(GSTACK_IsEmpty(_gstack))
        return GSTACK_STATUS_EMPTY;
    
    // Peek first element
#if GSTACK_GROWS_DOWNWARD == 1
    memcpy(_element, _gstack->container+(_gstack->element_size*_gstack->element_count), _gstack->element_size);
#else
    memcpy(_element, _gstack->container+(_gstack->element_size*(_gstack->element_count-1)), _gstack->element_size);
#endif    
    return GSTACK_STATUS_OK;
}

/**
 * Tell is a stack is empty
 * @param _gstack : stack to check
 * @return true if empty, false any other case
 */
bool GSTACK_IsEmpty(GSTACK* _gstack)
{
    // Check if ptr inst NULL
    if(_gstack == NULL)
        return false;
    // Check if stack isnst empty
#if GSTACK_GROWS_DOWNWARD == 1
    if(_gstack->element_count == _gstack->element_maxnumber)
        return true;
#else
    if(_gstack->element_count == 0)
        return true;
#endif
    else
        return false;
        
}

/**
 * Tell is a stack is full
 * @param _gstack : stack to check
 * @return true if full, false any other case
 */
bool GSTACK_IsFull(GSTACK* _gstack)
{
    // Check if ptr inst NULL
    if(_gstack == NULL)
        return false;
    // Check if stack isnst empty
#if GSTACK_GROWS_DOWNWARD == 1
    if(_gstack->element_count == 0)
        return true;
#else
    if(_gstack->element_count >= _gstack->element_maxnumber)
        return true;
#endif
    else
        return false;
}

/**
 * Return the status of the stack
 * @param _gstack : queue to check
 * @return GSTACK_STATUS
 */
GSTACK_STATUS GSTACK_GetStatus(GSTACK* _gstack)
{
    if(_gstack == NULL)                 return GSTACK_STATUS_NULL_PTR;
    else if(GSTACK_IsEmpty(_gstack))    return GSTACK_STATUS_EMPTY;
    else if(GSTACK_IsFull(_gstack))     return GSTACK_STATUS_FULL;
    else                                return GSTACK_STATUS_OK;
}

/**
 * Return size (element count) of the stack
 * @param _gstack : Stack to get size of
 * @param _size : Return value of size
 * @return GSTACK_STATUS
 */
GSTACK_STATUS GSTACK_GetLength(GSTACK* _gstack, size_t* _size)
{
    // Check if ptr inst NULL
    if(_gstack == NULL)
        return GSTACK_STATUS_NULL_PTR;
    
#if GSTACK_GROWS_DOWNWARD == 1
    *_size = _gstack->element_maxnumber - _gstack->element_count;
#else
    *_size = _gstack->element_count;
#endif
    return GSTACK_GetStatus(_gstack);
}