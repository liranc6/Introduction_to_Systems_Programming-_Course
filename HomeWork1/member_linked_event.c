#include "member_linked_event.h"
#include <stdlib.h>
#include <stdbool.h>


struct member_linked_event_t
{
    int event_id;
    struct member_linked_event_t* next;
};


MemberLinkedEvent memberLinkedEventGetNext(MemberLinkedEvent event)
{
    return event->next;
}


int memberLinkedEventGetId(MemberLinkedEvent event)
{
    return event->event_id;
}


MemberLinkedEvent memberLinkedEventCreate(MemberLinkedEvent new_link, MemberLinkedEvent previous_link,int event_id)
{
    new_link = malloc(sizeof(*new_link));
    if (new_link == NULL)
    {
        return NULL;
    }
    new_link->event_id = event_id;

    new_link->next = NULL;
    if (previous_link != NULL)
    {
        previous_link->next = new_link;
    }
    return new_link;
}


void memberLinkedEventDestroy(MemberLinkedEvent current_node, MemberLinkedEvent previous_node)
{
    if (previous_node != NULL)
    {
        previous_node->next = current_node->next;
    }
    free(current_node);
}


bool memberLinkedEventFindId(MemberLinkedEvent event, int event_id)
{
    while (event != NULL)
    {
        if (event->event_id == event_id)
        {
            return true;
        }
        else
        {
            event = event->next;
        }
    }

    return false;
}

