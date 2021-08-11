#ifndef PRIORITY_QUEUE_ITEM_H
#define PRIORITY_QUEUE_ITEM_H


/** Type for defining the priority queue item */
typedef struct priority_queue_item_t* PriorityQueueItem;

/** Data element data type for priority queue item container */
typedef void* item_element;

/** priority data type for priority queue item container */
typedef void* item_element_priority;


/**
* pqItemGetElement: returns the element of the priority queue item node
* @param priority_queue_item - a priority queue item
* @return
* the items nodes element
*/
item_element pqItemGetElement(PriorityQueueItem priority_queue_item);


/**
* pqItemGetPriority: returns the priority of the priority queue item node
* @param priority_queue_item - a priority queue item
* @return
* the items nodes priority
*/
item_element_priority pqItemGetPriority(PriorityQueueItem priority_queue_item);


/**
* pqItemDestroy: deallocates a priority queue item node
* @param priority_queue_item - a priority queue item
*
*/
void pqItemDestroy(PriorityQueueItem priority_queue_item);


/**
* pqItemCreate: creates a new priority queue item node and inserts the new element and priority into it
* @param new_element - the element that will be in the new node
* @param new_priority - the priority that will be in the new node
* @return
* a pointer to the newly created item node, NULL if there was a memory error
*/
PriorityQueueItem pqItemCreate(item_element new_element, item_element_priority new_priority);


/**
* pqItemChangeNext: changes the next node in a priority queue item to a new next node
* @param priority_queue_item - the node whose next will be changed
* @param new_next - the new next node
*
*/
void pqItemChangeNext(PriorityQueueItem priority_queue_item, PriorityQueueItem new_next);


/**
* pqItemGetNext: returns the next node in the list after a certain priority queue item node
* @param priority_queue_item - a priority queue item node whose next will be returned
* @return
* the next node in the list, if the next node is NULL will return NULL
*/
PriorityQueueItem pqItemGetNext(PriorityQueueItem priority_queue_item);


#endif /* PRIORITY_QUEUE_ITEM_H */
#pragma once