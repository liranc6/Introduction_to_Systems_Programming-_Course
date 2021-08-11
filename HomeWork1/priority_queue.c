#include "priority_queue.h"
#include "priority_queue_item.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


#define NULL_POINTER_WAS_SENT_TO_PQGETSIZE -1
#define ZERO 0

struct PriorityQueue_t {
    PriorityQueueItem head_of_queue;
    PriorityQueueItem iterator;
    CopyPQElement copy_element;
    FreePQElement free_element;
    EqualPQElements equal_elements;
    CopyPQElementPriority copy_priority;
    FreePQElementPriority free_priority;
    ComparePQElementPriorities compare_priorities;
};


// static function declarations

/**
 * removeItem:Connects two other functions in one function,clearing a priority_queue_item 
 *                                  and connecting the priority_queue_items around it.
 *
 * @param queue - The priority queue where the priority_queue_items are located.
 * @param current_priority_queue_item - The priority_queue_item that will be removed.
 * @param previous_priority_queue_item - The priority_queue_item whose "next" pointer is 
 *                                         connected to current_priority_queue_item.
 *
 */
static void removeItem(PriorityQueue queue, PriorityQueueItem current_priority_queue_item,
                                               PriorityQueueItem previous_priority_queue_item);


/**
 * connectItemsAroundCurrentItem:Takes a priority_queue_item and connects its previous 
 *                                       priority_queue_item the priority_queue_item after it.
 *
 * @param queue - The priority queue where the priority_queue_items are located.
 * @param current_priority_queue_item - The priority_queue_item that will be disconnected from the chain
 * @param previous_priority_queue_item - The priority_queue_item whose "next" pointer is 
 *                                          connected to current_priority_queue_item.
 *
 */
static void connectItemsAroundCurrentItem(PriorityQueue queue, PriorityQueueItem current_priority_queue_item,
                                                                PriorityQueueItem previous_priority_queue_item);


/**
 * clearAndFreeItem:Frees all the data elements in a priority_queue_item using functions from its priority queue,
 *                  then frees the priority_queue_item itself.
 *
 * @param queue - The priority queue where the priority_queue_item is located.
 * @param priority_queue_item - The priority_queue_item that will be deleted.
 *
 */
static void clearAndFreeItem(PriorityQueue queue, PriorityQueueItem priority_queue_item);


/**
 * resetIterator:sets the internal iterator to NULL
 * @param queue - The priority queue whose iterator will be set to NULL
 *
 */
static void resetIterator(PriorityQueue queue);


/**copyToItem: Creates a priority_queue_item for the queue with an element and a priority, connects the
*          new priority_queue_item to the queue's priority_queue_item chain, in accordance to its priority compared to 
*          the priority_queue_items around it.
*
* @param queue - The priority queue that the item will be inserted into
* @param current_priority_queue_item - The node that the new node will be created around
* @param previous_priority_queue_item - The item node that will be before the new new node in the list
* @param compare_priorities - The comparison result that will decide where the new node will be connected
* @param element - The element that will be copied into the new item node
* @param priority - The priority that will be copied into the new item node
* @return
* EM_SUCCESS if the new item node was created
* EM_OUT_OF_MEMORY if there was a memory error during allocation
*/
static PriorityQueueResult copyToItem(PriorityQueue queue, PriorityQueueItem current_priority_queue_item, 
PriorityQueueItem previous_priority_queue_item,int compare_priorities, PQElement element, PQElementPriority priority);


/**
* findElementWithPriority: Finds the first element in a priority queue with the specific priority given.
* @param queue - Queue to search in
* @param element - The specific element to find
* @param priority - The specific priority to find
* @return
* The first priority queue item node that has the specific element and priority
* NULL if no item node with the specific element and priority is found
*/
static PriorityQueueItem findElementWithPriority(PriorityQueue queue, PQElement element, PQElementPriority priority);



PriorityQueue pqCreate(CopyPQElement copy_element,
    FreePQElement free_element,
    EqualPQElements equal_elements,
    CopyPQElementPriority copy_priority,
    FreePQElementPriority free_priority,
    ComparePQElementPriorities compare_priorities)
{
    if (!copy_element || !equal_elements || !copy_priority || !free_priority || !compare_priorities)
    {
        return NULL;
    }
    PriorityQueue priority_queue = malloc(sizeof(*priority_queue));
    if (priority_queue == NULL)
    {
        return NULL;
    }
    priority_queue->head_of_queue = NULL;
    priority_queue->iterator = NULL;
    priority_queue->copy_element = copy_element;
    priority_queue->free_element = free_element;
    priority_queue->equal_elements = equal_elements;
    priority_queue->copy_priority = copy_priority;
    priority_queue->free_priority = free_priority;
    priority_queue->compare_priorities = compare_priorities;
    return priority_queue;
}

void pqDestroy(PriorityQueue queue)
{
    if (queue == NULL)
    {
        return;
    }
    pqClear(queue);
    free(queue);
}

PriorityQueue pqCopy(PriorityQueue queue)
{
    resetIterator(queue);


    if (queue == NULL)
    {
        return NULL;
    }

    PriorityQueue new_queue = pqCreate(queue->copy_element, queue->free_element, queue->equal_elements,
        queue->copy_priority, queue->free_priority, queue->compare_priorities);
    if (new_queue == NULL)
    {
        return NULL;
    }

    PriorityQueueItem current_priority_queue_item = queue->head_of_queue;
    PriorityQueueResult result;
    while (current_priority_queue_item != NULL)
    {
        result = pqInsert(new_queue, pqItemGetElement(current_priority_queue_item),
                                       pqItemGetPriority(current_priority_queue_item));
        if (result == PQ_OUT_OF_MEMORY)
        {
            pqDestroy(new_queue);
            return NULL;
        }

        current_priority_queue_item = pqItemGetNext(current_priority_queue_item);
    }
    return new_queue;
}

int pqGetSize(PriorityQueue queue)
{
    if (queue == NULL)
    {
        return NULL_POINTER_WAS_SENT_TO_PQGETSIZE;
    }
    int size = 0;
    PriorityQueueItem current_priority_queue_item = queue->head_of_queue;
    while (current_priority_queue_item != NULL)
    {
        size += 1;
        current_priority_queue_item = pqItemGetNext(current_priority_queue_item);
    }
    return size;
}

bool pqContains(PriorityQueue queue, PQElement element)
{
    if ((queue == NULL) || (element == NULL))
    {
        return false;
    }
    PriorityQueueItem current_priority_queue_item = queue->head_of_queue;
    while (current_priority_queue_item != NULL)
    {
        if (queue->equal_elements(pqItemGetElement(current_priority_queue_item), element))
        {
            return true;
        }
        current_priority_queue_item = pqItemGetNext(current_priority_queue_item);
    }
    return false;
}

PriorityQueueResult pqInsert(PriorityQueue queue, PQElement element, PQElementPriority priority)
{
    resetIterator(queue);

    if (queue == NULL || element == NULL || priority == NULL)
    {
        return PQ_NULL_ARGUMENT;
    }

    PriorityQueueItem current_priority_queue_item = queue->head_of_queue;
    PriorityQueueItem previous_priority_queue_item = NULL;

    if (current_priority_queue_item == NULL)
    {
        return copyToItem(queue, current_priority_queue_item, previous_priority_queue_item, 0, element, priority);
    }

    int compare_result = queue->compare_priorities(pqItemGetPriority(current_priority_queue_item), priority);

    while (compare_result >= ZERO && pqItemGetNext(current_priority_queue_item) != NULL)
    {
        previous_priority_queue_item = current_priority_queue_item;
        current_priority_queue_item = pqItemGetNext(current_priority_queue_item);
        compare_result = queue->compare_priorities(pqItemGetPriority(current_priority_queue_item), priority);
    }

    return copyToItem(queue,current_priority_queue_item,previous_priority_queue_item,compare_result,element,priority);
}

PriorityQueueResult pqChangePriority(PriorityQueue queue, PQElement element,
    PQElementPriority old_priority, PQElementPriority new_priority)
{
    if (queue == NULL || element == NULL || old_priority == NULL || new_priority == NULL)
    {
        return PQ_NULL_ARGUMENT;
    }

    resetIterator(queue);

    PriorityQueueItem element_queue_item = findElementWithPriority(queue, element, old_priority);
    if (element_queue_item == NULL)
    {
        return PQ_ELEMENT_DOES_NOT_EXISTS;
    }

    PQElement element_copy = queue->copy_element(element);
    if (element_copy == NULL)
    {
        return PQ_OUT_OF_MEMORY;
    }

    pqRemoveElement(queue, element);
    
    PriorityQueueResult insertion_result = pqInsert(queue, element_copy, new_priority);
    if (insertion_result != PQ_SUCCESS)
    {
        queue->free_element(element_copy);
        return insertion_result;
    }

    queue->free_element(element_copy);
    return PQ_SUCCESS;
}

PriorityQueueResult pqRemove(PriorityQueue queue)
{

    if (queue == NULL)
    {
        return PQ_NULL_ARGUMENT;
    }

    resetIterator(queue);

    PriorityQueueItem first_priority_queue_item = queue->head_of_queue; //get first priority_queue_item in queue

    if (first_priority_queue_item == NULL) //if empty
    {
        return PQ_SUCCESS;
    }

    queue->head_of_queue = pqItemGetNext(first_priority_queue_item); //set new head of queue
    clearAndFreeItem(queue, first_priority_queue_item);

    return PQ_SUCCESS;
}

PriorityQueueResult pqRemoveElement(PriorityQueue queue, PQElement element)
{
    if (queue == NULL || element == NULL)
    {
        return PQ_NULL_ARGUMENT;
    }

    resetIterator(queue);

    PriorityQueueItem current_priority_queue_item = queue->head_of_queue;
    if (current_priority_queue_item == NULL) //if the queue is empty
    {
        return PQ_ELEMENT_DOES_NOT_EXISTS;
    }
    PriorityQueueItem previous_priority_queue_item = NULL;
    while (current_priority_queue_item != NULL)
    {
        if (queue->equal_elements(pqItemGetElement(current_priority_queue_item), element))
        {
            removeItem(queue, current_priority_queue_item, previous_priority_queue_item);
            return PQ_SUCCESS;
        }
        previous_priority_queue_item = current_priority_queue_item;
        current_priority_queue_item = pqItemGetNext(current_priority_queue_item);
    }
    return PQ_ELEMENT_DOES_NOT_EXISTS;
}

PriorityQueueResult pqClear(PriorityQueue queue)
{
    if (queue == NULL) //check if the pointer sent is NULL
    {
        return PQ_NULL_ARGUMENT;
    }
    else
    {
        PriorityQueueItem priority_queue_item = queue->head_of_queue;

        while (priority_queue_item != NULL) //stops when head_of_queue is NULL == there are no elements in queue 
        {
            queue->head_of_queue = pqItemGetNext(queue->head_of_queue);
            clearAndFreeItem(queue, priority_queue_item);
            priority_queue_item = queue->head_of_queue;
        }
    }

    return PQ_SUCCESS;
}


PQElement pqGetFirst(PriorityQueue queue)
{
    if (queue == NULL)
    {
        return NULL;
    }
    else if (queue->head_of_queue == NULL)
    {
        return NULL;
    }
    else
    {
        queue->iterator = queue->head_of_queue;
        return pqItemGetElement(queue->head_of_queue);
    }
}

PQElement pqGetNext(PriorityQueue queue)
{
    if (queue == NULL)
    {
        return NULL;
    }
    else if (queue->iterator == NULL)
    {
        return NULL;
    }
    else if (pqItemGetNext(queue->iterator) == NULL)
    {
        return NULL;
    }
    else
    {
        queue->iterator = pqItemGetNext(queue->iterator);

        return pqItemGetElement(queue->iterator);

    }

}

//static functions

static void removeItem(PriorityQueue queue, PriorityQueueItem current_priority_queue_item,
                                              PriorityQueueItem previous_priority_queue_item)
{
    connectItemsAroundCurrentItem(queue, current_priority_queue_item, previous_priority_queue_item);
    clearAndFreeItem(queue, current_priority_queue_item);
}



static void connectItemsAroundCurrentItem(PriorityQueue queue, PriorityQueueItem current_priority_queue_item,
                                                                PriorityQueueItem previous_priority_queue_item)
{
    if (previous_priority_queue_item == NULL)
    {
        queue->head_of_queue = pqItemGetNext(current_priority_queue_item);
    }
    else
    {
        pqItemChangeNext(previous_priority_queue_item, pqItemGetNext(current_priority_queue_item));
    }
}


static void clearAndFreeItem(PriorityQueue queue, PriorityQueueItem priority_queue_item)
{
    PQElement queue_element = pqItemGetElement(priority_queue_item);
    queue->free_element(queue_element);
    PQElementPriority queue_element_priority = pqItemGetPriority(priority_queue_item);
    queue->free_priority(queue_element_priority);
    pqItemDestroy(priority_queue_item);
}


static void resetIterator(PriorityQueue queue)
{
    if (queue != NULL)
    {
        queue->iterator = NULL;
    }
}


static PriorityQueueResult copyToItem(PriorityQueue queue, PriorityQueueItem current_priority_queue_item,
     PriorityQueueItem previous_priority_queue_item,int compare_result, PQElement element, PQElementPriority priority)
{
    PQElementPriority new_priority = queue->copy_priority(priority);
    if (new_priority == NULL)
    {
        return PQ_OUT_OF_MEMORY;
    }

    PQElement new_element = queue->copy_element(element);
    if (new_element == NULL)
    {
        queue->free_priority(new_priority);
        return PQ_OUT_OF_MEMORY;
    }

    PriorityQueueItem new_priority_queue_item = pqItemCreate(new_element, new_priority);
    if (new_priority_queue_item == NULL)
    {
        queue->free_priority(new_priority);
        queue->free_element(new_element);
        return PQ_OUT_OF_MEMORY;
    }

    if (current_priority_queue_item == NULL && previous_priority_queue_item == NULL) //the queue is empty
    {
        queue->head_of_queue = new_priority_queue_item;
        pqItemChangeNext(new_priority_queue_item, NULL);
    }
    else if (compare_result >= ZERO)
    {
        PriorityQueueItem next_priority_queue_item = pqItemGetNext(current_priority_queue_item);
        pqItemChangeNext(new_priority_queue_item, next_priority_queue_item);
        pqItemChangeNext(current_priority_queue_item, new_priority_queue_item);
    }
    else
    {
        if (previous_priority_queue_item == NULL) // if the current priority_queue_item is the head of the queue
        {
            pqItemChangeNext(new_priority_queue_item, current_priority_queue_item);
            queue->head_of_queue = new_priority_queue_item;
        }
        else
        {
            pqItemChangeNext(new_priority_queue_item, current_priority_queue_item);
            pqItemChangeNext(previous_priority_queue_item, new_priority_queue_item);
        }
    }

    return PQ_SUCCESS;
}


static PriorityQueueItem findElementWithPriority(PriorityQueue queue, PQElement element, PQElementPriority priority)
{
    if ((queue == NULL) || (element == NULL))
    {
        return NULL;
    }

    PriorityQueueItem current_priority_queue_item = queue->head_of_queue;
    while (current_priority_queue_item != NULL)
    {
        if (queue->equal_elements(pqItemGetElement(current_priority_queue_item), element))
        {
            if (queue->compare_priorities(pqItemGetPriority(current_priority_queue_item), priority) == 0)
            {
                return current_priority_queue_item;
            }
        }
        current_priority_queue_item = pqItemGetNext(current_priority_queue_item);
    }

    return NULL;
}