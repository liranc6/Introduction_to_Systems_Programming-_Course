#ifndef MEMBER_H
#define MEMBER_H

#include <stdbool.h>

/** Type for defining the member */
typedef struct member_struct_t* Member;


/**
* memberCreate: Creates a member and assigns a name and an id to him
* @param member_name - new member name
* @param  member_id - new member id
* @return
* pointer to the member if the creation succeeded or null if didnt
*/
Member memberCreate(char* member_name, int member_id);


/**
* memberDestroy: Deallocates an existing member
* @param member - pointer to member
*/
void memberDestroy(Member member);


/**
* memberGetId: returns the members id
* @param member - pointer to member
* @return
* member id
*/
int memberGetId(Member member);


/**
* memberGetName: returns the members name
* @param member - pointer to member
* @return
* a pointer the members name
*/
char* memberGetName(Member member);


/**
* memberGetNumberOfLinkedEvents: returns the mumber of events linked to member
* @param member - pointer to member
* @return
* mumber of events linked to member
*/
int memberGetNumberOfLinkedEvents(Member member);


/**
* memberLinkEvent: add event to list of events linked to member
* @param  member - pointer to member
* @param event_id - the id of the event to link

* @return
* true if the member is linked
* false if there was a memory error
*/
bool memberLinkEvent(Member member, int event_id);


/**
* memberCheckIfEventIsLinked: check if a member is linked to an event
* @param event_id - id of the event
* @param  member - pointer to member
* @return
* true if the member is linked
* false event was not linked to member (member was null or id isnt valid or faild to link)
*/
bool memberCheckIfEventIsLinked(int event_id, Member member);


/**
* memberRemoveEventLink: remove the link between an event and a member
* @param event_id - id of the event
* @param  member - pointer to member
* @return
* true if the event was successfully unlinked from the member
* false if the event is not linked to the member 
*/
bool memberRemoveEventLink(Member member, int event_id);

#endif /* MEMBER_H */
#pragma once
