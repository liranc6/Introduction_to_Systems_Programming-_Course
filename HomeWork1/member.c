#include "member.h"
#include "member_linked_event.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


struct member_struct_t
{
    char* member_name;
    int member_id;
    int number_of_linked_events;
    MemberLinkedEvent first_event;
};


bool memberLinkEvent(Member member, int event_id)
{
    MemberLinkedEvent current_node = member->first_event;
    MemberLinkedEvent previous_node = NULL;

    while (current_node != NULL)
    {
        previous_node = current_node;
        current_node = memberLinkedEventGetNext(current_node);
    }

    current_node = memberLinkedEventCreate(current_node,previous_node,event_id);
    if (current_node == NULL)
    {
        return false;
    }   

    if (member->first_event == NULL)
    {
        member->first_event = current_node;
    }

    member->number_of_linked_events++;
    return true;
    
}


bool memberCheckIfEventIsLinked(int event_id, Member member)
{
    if (member == NULL || event_id < 0)
    {
        return false;
    }

    MemberLinkedEvent event = member->first_event;

    if (memberLinkedEventFindId(event, event_id))
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool memberRemoveEventLink(Member member, int event_id)
{

    MemberLinkedEvent current_link_node = member->first_event;
    MemberLinkedEvent previous_link_node = NULL;

    while (current_link_node != NULL)
    {
        if (memberLinkedEventGetId(current_link_node) == event_id)
        {
            if (previous_link_node == NULL)
            {
                member->first_event = memberLinkedEventGetNext(current_link_node);
            }
            memberLinkedEventDestroy(current_link_node, previous_link_node);
            member->number_of_linked_events -= 1;
            return true;
        }

        previous_link_node = current_link_node;
        current_link_node = memberLinkedEventGetNext(current_link_node);
    }

    return false;
}


Member memberCreate(char* member_name, int member_id)
{
    if (member_name == NULL || member_id < 0)
    {
        return NULL;
    }

    Member new_member = malloc(sizeof(*new_member));
    if (new_member == NULL)
    {
        return NULL;
    }

    char* new_name = malloc(strlen(member_name) + 1);
    if (new_name == NULL)
    {
        free(new_member);
        return NULL;
    }

    strcpy(new_name, member_name);

    new_member->member_name = new_name;
    new_member->member_id = member_id;
    new_member->first_event = NULL;
    new_member->number_of_linked_events = 0;

    return new_member;
}



void memberDestroy(Member member)
{
    MemberLinkedEvent event_pointer_node;
    while (member->first_event != NULL)
    {
        event_pointer_node = member->first_event;
        member->first_event = memberLinkedEventGetNext(member->first_event);
        free(event_pointer_node);
    }

    free(member->member_name);
    free(member);
}


int memberGetId(Member member)
{
    return member->member_id;
}


char* memberGetName(Member member)
{
    if (member == NULL)
    {
        return NULL;
    }

    return member -> member_name;
}


int memberGetNumberOfLinkedEvents(Member member)
{
    return member->number_of_linked_events;
}
