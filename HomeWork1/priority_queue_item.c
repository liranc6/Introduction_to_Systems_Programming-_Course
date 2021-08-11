#include <stdlib.h>
#include "priority_queue_item.h"


struct priority_queue_item_t {
    item_element queue_element;
    item_element_priority queue_element_priority;
    struct priority_queue_item_t* next;
};


item_element pqItemGetElement(PriorityQueueItem priority_queue_item)
{
    return priority_queue_item->queue_element;
}


item_element_priority pqItemGetPriority(PriorityQueueItem priority_queue_item)
{
    return priority_queue_item->queue_element_priority;
}


void pqItemDestroy(PriorityQueueItem priority_queue_item)
{
    free(priority_queue_item);
}


PriorityQueueItem pqItemCreate(item_element new_element, item_element_priority new_priority)
{
    if (new_element == NULL || new_priority == NULL)
    {
        return NULL;
    }

    PriorityQueueItem new_priority_queue_item = malloc(sizeof(*new_priority_queue_item));
    if (new_priority_queue_item == NULL)
    {
        return NULL;
    }

    new_priority_queue_item->queue_element = new_element;
    new_priority_queue_item->queue_element_priority = new_priority;
    new_priority_queue_item->next = NULL;

    return new_priority_queue_item;
}


void pqItemChangeNext(PriorityQueueItem priority_queue_item, PriorityQueueItem new_next)
{
    if (priority_queue_item != NULL)
    {
        priority_queue_item -> next = new_next;
    }
}


PriorityQueueItem pqItemGetNext(PriorityQueueItem priority_queue_item)
{
    if (priority_queue_item != NULL)
    {
        return priority_queue_item->next;
    }

    return NULL;
}