#ifndef MEMBER_LINKED_EVENT_H
#define MEMBER_LINKED_EVENT_H

#include <stdbool.h>

/** Type for defining the member linked event node */
typedef struct member_linked_event_t *MemberLinkedEvent;

/**
* memberLinkedEventGetNext: returns next member linked event
* @param event - pointer to event link node
* @return
* next member linked event
*/
MemberLinkedEvent memberLinkedEventGetNext(MemberLinkedEvent member_event_link);


/**
* memberLinkedEventGetId: returns id of linked event
* @param event - pointer to event
* @return
* id of linked event
*/
int memberLinkedEventGetId(MemberLinkedEvent member_event_link);


/**
* memberLinkedEventCreate: creates a new event link node and connects it to the linked list
* @param new_link - a pointer to the new node that will be created
* @param previous_link - pointer to the previous node the in chain
* @param event_id - the id of the event that is being linked
* @return
* a pointer to the member linked event node, if there was a memory error returns NULL
*/
MemberLinkedEvent memberLinkedEventCreate(MemberLinkedEvent new_link,MemberLinkedEvent previous_link,int event_id);


/**
* memberLinkedEventFindId: checks if the list of events linked to a member contains  a certain event by id
* @param first_linked_event - first event in list
* @param event_id - id of event to find
* @return
* true if contains or false if not
*/
bool memberLinkedEventFindId(MemberLinkedEvent first_linked_event, int event_id);


/**
* memberLinkedEventDestroy: deallocates the current event link node and connects the nodes around it
* @param current_node - the event link node to be removed
* @param previous_node - the previous node in the list
*
*/
void memberLinkedEventDestroy(MemberLinkedEvent current_node, MemberLinkedEvent previous_node);


#endif /* MEMBER_LINKED_EVENT_H */
#pragma once


