#include "event_manager.h"
#include "priority_queue.h"
#include "date.h"
#include "member.h"
#include "event.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>




struct EventManager_t
{
    Date system_date;
    PriorityQueue event_log;
    PriorityQueue member_log;
};
 
//static function declarations

/**
* findEventByEventId: searches the event_log for an event with an id equal to "event_id"
* @param event_log - a priority queue of events
* @param event_id - id of the event to search by
* @return
* pointer to the event if found or NULL if no such event is found
*/
static Event findEventByEventId(PriorityQueue event_log, int event_id);


/**
* findMemberById: searches the member_log for a member with an id equal to "member_id"
* @param member_log - a priority queue of members
* @param member_id - target member id
* @return
*  pointer to the member if found or null if not. returns null if id isnt valid
*/
static Member findMemberById(PriorityQueue member_log, int member_id);


/**
* deleteFormerEvents: deletes the events scheduled before the current date of the system
* @param em - event manager the events are saved in
* @param system_date - current date of the system
* @return
* EM_SUCCESS if there are no events in em or if all former events are deleted
* EM_OUT_OF_MEMORY if failed to delete an event
*/
static EventManagerResult deleteFormerEvents(EventManager em, Date system_date);


/**
* checkIfEventNameOrIdExist: checks if there already exists an event with an id equal to "event_id",or a an event with
                                the same date and name as "date" and "event_name"
* @param em - the event manger the events are saved in
* @param date - target date
* @param event_name - target event name
* @param event_id - target event id
* @return
* EM_INVALID_EVENT_ID if "event_id" is negative
* EM_EVENT_ALREADY_EXISTS if an event with the same name and date exists
* EM_EVENT_ID_ALREADY_EXISTS if an event with the same id exists
* EM_SUCCESS if no such events exist
*/
static EventManagerResult checkIfEventNameOrIdExist(EventManager em, Date date, char* event_name, int event_id); 


/**
* printMembersInEventToFile: prints to file all members that are linked to an event
* @param stream - the open file that the members will be printed to
* @param member_log - a priority queue of members
* @param event - the event that all the members linked to will be printed
*/
static void printMembersInEventToFile(FILE* stream, PriorityQueue member_log, Event event);


/**
* copyElementEvent: copies an element event for a PriorityQueue 
* @param element_event - the event out of a priority queue that will be copied
* @return
* a copied event casted for the PriorityQueue
*/
static PQElement copyElementEvent(PQElement element_event);


/**
* freeElementEvent: frees an element event for a PriorityQueue
* @param event - the event out of a priority queue that will be freed
*/
static void freeElementEvent(PQElement event);


/**
* comparePriorityDate:compares two priority dates for a PriorityQueue,the higher priority is given to the earlier date
* @param date1 - a priority element from a priority queue that is a Date
* @param date2 - a priority element from a priority queue that is a Date
* @return
* a positive integer if date1 is earlier
* 0 if they're equal
* a negative integer if date2 is earlier
*/
static int comparePriorityDate(PQElementPriority date1, PQElementPriority date2);


/**
* compareElementEventId:compares two element events for a PriorityQueue,the element events are equal if their id's are
* @param event1 - a element from a priority queue that is an Event
* @param event2 - a element from a priority queue that is an Event
* @return
* true if the event id's are equal
* false if the id's are different
*/
static bool compareElementEventId(PQElement event1, PQElement event2);


/**
* copyElementEvent: copies a priority element date for a PriorityQueue
* @param date - the date out of a priority queue that will be copied
* @return
* a copied date casted for the PriorityQueue
*/
static PQElementPriority copyPriorityDate(PQElementPriority date);


/**
* copyElementEvent: copies an element event for a PriorityQueue
* @param element_event - the event out of a priority queue that will be copied
* @return
* a copied event casted for the PriorityQueue
*/
static void destroyPriorityDate(PQElementPriority date);


/**
* copyElementMember: copies an element for the members PriorityQueue, where the element is a Member struct so the 
*                       function casts the parameter and calls the function that copies the member
* @param member - target member
* @return
* a PQElement copy of the member
*/
static PQElement copyElementMember(PQElement member);


/**
* freeElementMember: deallocates an element for the members PriorityQueue, the element is a Member struct so the 
*                       function casts the parameter and calls the function that destroys the member
* @param member - target member
*/
static void freeElementMember(PQElement member);


/**
* compareElementMemberId: compares two elements for the members PriorityQueue, two member elements are equal if
*                           their id's are equal
* @param member1 - first member to compare
* @param member2 - second member to compare
* @return
* true if the id's of the two members are equal
* false if the id's are not equal or one of the parameters is NULL
*/
static bool compareElementMemberId(PQElement member1, PQElement member2);


/**
* copyPriorityMemberId: copies a priority element of an int pointer for a PriorityQueue,to be used in the members
*                       priority queue where all the members are sorted by the size of their id
* @param member_id - target member id
* @return
* priority element copy of "member_id"
*/
static PQElementPriority copyPriorityMemberId(PQElementPriority member_id);


/**
* freePriorityMemberId: frees a priority element of an int pointer in a PriorityQueue, to be used in the members
*                       priority queue where all the members are sorted by the size of their id 
* @param member_id - target member id
*/
static void freePriorityMemberId(PQElementPriority member_id);


/**
* comparePriorityMemberId: compares priorities for a member PriorityQueue, where the higher priority is give to the
*                           member with the smallest id
* @param id1 - first member id to compare
* @param id2 - second member id to compare
* @return
* a positive integer if id1 is smaller
* 0 if they're equal
* a negative integer if id2 is bigger
*/
static int comparePriorityMemberId(PQElementPriority id1, PQElementPriority id2);


/**
* removeLinkBetweenAllMembersToEvent: remove the link between all members an to event, by going over every member
*                               in a member_log and searching his linked list of event id's.
* @param member_log - priority queue of members
* @param event_id - id of the event to unlink
*/
static void removeLinkBetweenAllMembersToEvent(PriorityQueue member_log, int event_id);


/**
* checkIfEventAlreadyExists: checks if there already exists an event in the event log with the same date and name as
*                                       "event_date" and "event_name"
* @param event_log - priority queue of events
* @param event_date - identify event by date
* @param event_name- identify event by event_name
* @return
* true  if an event with "event_date" and "event_name" exists
* flase if no such event exists in the event_log
*/
static bool checkIfEventAlreadyExists(PriorityQueue event_log, Date event_date, char* event_name);

//end declarations




EventManager createEventManager(Date date)
{
    if (date == NULL)
    {
        return NULL;
    }
    EventManager new_manager = malloc(sizeof(*new_manager));
    if (new_manager == NULL)
    {
        return NULL;
    }
    new_manager->system_date = dateCopy(date);
    if (new_manager->system_date == NULL)
    {
        free(new_manager);
        return NULL;
    }
    new_manager->event_log = pqCreate(copyElementEvent, freeElementEvent, compareElementEventId, copyPriorityDate,
        destroyPriorityDate, comparePriorityDate);
    if (new_manager->event_log == NULL)
    {
        dateDestroy(new_manager->system_date);
        free(new_manager);
        return NULL;
    }
    new_manager->member_log = pqCreate(copyElementMember, freeElementMember, compareElementMemberId,
        copyPriorityMemberId, freePriorityMemberId, comparePriorityMemberId);
    if (new_manager->member_log == NULL)
    {
        pqDestroy(new_manager->event_log);
        dateDestroy(new_manager->system_date);
        free(new_manager);
        return NULL;
    }
    return new_manager;
}

EventManagerResult emAddEventByDate(EventManager em, char* event_name, Date date, int event_id)
{
    if (em == NULL || event_name == NULL || date == NULL)
    {
        return EM_NULL_ARGUMENT;
    }
    if (dateCompare(date, em->system_date) < 0)
    {
        return EM_INVALID_DATE;
    }

    EventManagerResult validation_function_result = checkIfEventNameOrIdExist(em, date, event_name, event_id);
    if (validation_function_result != EM_SUCCESS)
    {
        return validation_function_result;
    }

    Event new_event = eventCreate(event_name, date, event_id);
    if (new_event == NULL)
    {
        destroyEventManager(em);
        return EM_OUT_OF_MEMORY;
    }

    if (pqInsert(em->event_log, (PQElement*)new_event, (PQElementPriority*)date) == PQ_OUT_OF_MEMORY)
    {
        destroyEventManager(em);
        eventDestroy(new_event);
        return EM_OUT_OF_MEMORY;
    }

    eventDestroy(new_event);
    return EM_SUCCESS;
}

EventManagerResult emRemoveEvent(EventManager em, int event_id)
{
    if (em == NULL)
    {
        return EM_NULL_ARGUMENT;
    }
    if (event_id < 0)
    {
        return EM_INVALID_EVENT_ID;
    }

    Event event_to_remove = findEventByEventId(em->event_log, event_id);
    if (event_to_remove == NULL)
    {
        return EM_EVENT_NOT_EXISTS;
    }

    removeLinkBetweenAllMembersToEvent(em->member_log, event_id);

    pqRemoveElement(em->event_log, event_to_remove);

    return EM_SUCCESS;
}

EventManagerResult emAddMember(EventManager em, char* member_name, int member_id)
{
    if (em == NULL || member_name == NULL)
    {
        return EM_NULL_ARGUMENT;
    }
    if (member_id < 0)
    {
        return EM_INVALID_MEMBER_ID;
    }

    Member new_member = memberCreate(member_name, member_id);
    if (new_member == NULL)
    {
        destroyEventManager(em);
        return EM_OUT_OF_MEMORY;
    }

    if (pqContains(em->member_log, new_member))
    {
        memberDestroy(new_member);
        return EM_MEMBER_ID_ALREADY_EXISTS;
    }

    if (pqInsert(em->member_log, new_member, &(member_id)) == PQ_OUT_OF_MEMORY)
    {
        destroyEventManager(em);
        memberDestroy(new_member);
        return EM_OUT_OF_MEMORY;
    }

    memberDestroy(new_member);
    return EM_SUCCESS;
}

EventManagerResult emRemoveMemberFromEvent(EventManager em, int member_id, int event_id)
{
    if (em == NULL)
    {
        return EM_NULL_ARGUMENT;
    }
    if (event_id < 0)
    {
        return EM_INVALID_EVENT_ID;
    }
    if (member_id < 0)
    {
        return EM_INVALID_MEMBER_ID;
    }

    if (findEventByEventId(em->event_log, event_id) == NULL)
    {
        return EM_EVENT_ID_NOT_EXISTS;
    }

    Member member_to_remove = findMemberById(em->member_log, member_id);
    if (member_to_remove == NULL)
    {
        return EM_MEMBER_ID_NOT_EXISTS;
    }

    if (!memberRemoveEventLink(member_to_remove, event_id))
    {
        return EM_EVENT_AND_MEMBER_NOT_LINKED;
    }

    return EM_SUCCESS;
}

int emGetEventsAmount(EventManager em)
{
    if (em == NULL)
    {
        return -1;
    }
    return pqGetSize(em->event_log);
}

void emPrintAllEvents(EventManager em, const char* file_name)
{
    if (em == NULL || file_name == NULL)
    {
        return;
    }
    
    FILE* stream = fopen(file_name, "w");
    if (stream == NULL)
    {
        return;
    }

    Event current_event = pqGetFirst(em->event_log);
    int day, month, year;

    while (current_event != NULL)
    {
        dateGet(eventGetDate(current_event), &day, &month, &year);
        fprintf(stream, "%s,%d.%d.%d", eventGetName( current_event), day, month, year);
        printMembersInEventToFile(stream, em->member_log, current_event);
        current_event = pqGetNext(em->event_log);
        fprintf(stream,"\n");
    }

    fclose(stream);
}

void destroyEventManager(EventManager em)
{
    if (em == NULL)
    {
        return;
    }

    pqDestroy(em->event_log);
    pqDestroy(em->member_log);
    dateDestroy(em->system_date);
    free(em);
}

EventManagerResult emAddEventByDiff(EventManager em, char* event_name, int days, int event_id)
{

    if (em == NULL || event_name == NULL)
    {
        return EM_NULL_ARGUMENT;
    }
    else if (days < 0)
    {
        return EM_INVALID_DATE;
    }
    else if (event_id < 0)
    {
        return EM_INVALID_EVENT_ID;
    }

    Date new_date = dateCopy(em->system_date); //Creates a copy of current_date.
    if (new_date == NULL)
    {
        destroyEventManager(em);
        return EM_OUT_OF_MEMORY;
    }

    for (int i = 0; i < days; i++) //set the date of new event
    {
        dateTick(new_date);
    }

    EventManagerResult insertion_result = emAddEventByDate(em, event_name, new_date, event_id);
    dateDestroy(new_date);

    if (insertion_result == EM_OUT_OF_MEMORY)
    {
        destroyEventManager(em);
        return EM_OUT_OF_MEMORY;
    }
    else if (insertion_result != EM_SUCCESS)
    {
        return insertion_result;
    }
   
    return EM_SUCCESS;
}

EventManagerResult emChangeEventDate(EventManager em, int event_id, Date new_date)
{
    if (em == NULL || new_date == NULL)
    {
        return EM_NULL_ARGUMENT;
    }
    else if (dateCompare(new_date, em->system_date) < 0)
    {
        return EM_INVALID_DATE;
    }
    else if (event_id < 0)
    {
        return EM_INVALID_EVENT_ID;
    }

    Event event = findEventByEventId(em->event_log, event_id); //find event by ID and get the event pointer
    if (event == NULL)
    {
        return EM_EVENT_ID_NOT_EXISTS;
    }

    if (checkIfEventAlreadyExists(em->event_log,new_date,eventGetName(event)))
    {
        return EM_EVENT_ALREADY_EXISTS;
    }

    Date current_event_date = eventGetDate(event);
    Date old_date = dateCopy(current_event_date);
    if (old_date == NULL)
    {
        destroyEventManager(em);
        return EM_OUT_OF_MEMORY;
    }

    if (!eventChangeDate(event, new_date))
    {
        dateDestroy(old_date);
        destroyEventManager(em);
        return EM_OUT_OF_MEMORY;
    }

    PriorityQueueResult change_priority = pqChangePriority(em->event_log, event, old_date, new_date);
    dateDestroy(old_date);
    if (change_priority == PQ_OUT_OF_MEMORY)
    {
        destroyEventManager(em);
        return EM_OUT_OF_MEMORY;
    }

    return EM_SUCCESS;
}

EventManagerResult emAddMemberToEvent(EventManager em, int member_id, int event_id)
{
    if (em == NULL)
    {
        return EM_NULL_ARGUMENT;
    }
    else if (event_id < 0)
    {
        return EM_INVALID_EVENT_ID;
    }
    else if (member_id < 0)
    {
        return EM_INVALID_MEMBER_ID;
    }

    Event event = findEventByEventId(em->event_log, event_id);
    if (event == NULL)
    {
        return EM_EVENT_ID_NOT_EXISTS;
    }

    Member member = findMemberById(em->member_log, member_id);
    if (member == NULL)
    {
        return EM_MEMBER_ID_NOT_EXISTS;
    }

    if (memberCheckIfEventIsLinked(eventGetId(event), member) == true)
    {
        return EM_EVENT_AND_MEMBER_ALREADY_LINKED;
    }

    if (!memberLinkEvent(member, eventGetId(event)))
    {
        destroyEventManager(em);
        return EM_OUT_OF_MEMORY;
    }

    return EM_SUCCESS;
}


EventManagerResult emTick(EventManager em, int days)
{
    if (em == NULL)
    {
        return EM_NULL_ARGUMENT;
    }
    else if (days <= 0)
    {
        return EM_INVALID_DATE;
    }

    Date system_date = em->system_date;
    for (int i = 0; i < days; i++)
    {
        dateTick(system_date);
    }

    EventManagerResult delete_former_events_result = deleteFormerEvents(em, system_date);

    switch (delete_former_events_result)
    {
    case EM_OUT_OF_MEMORY:
        destroyEventManager(em);
        return EM_OUT_OF_MEMORY;
        break;
    default: return delete_former_events_result;
    }
}

char* emGetNextEvent(EventManager em)
{
    if (em == NULL)
    {
        return NULL;
    }

    Event next_event = pqGetFirst(em->event_log);
    if (next_event == NULL) //if there are no events
    {
        return NULL;
    }

    char* next_event_name = eventGetName(next_event);
    return next_event_name;
}

void emPrintAllResponsibleMembers(EventManager em, const char* file_name)
{
    if (file_name != NULL && em != NULL)
    {
        FILE* stream = fopen(file_name, "w");
        if (stream == NULL) 
        {
            return;
        }
        else
        {
            int max_number_of_events = pqGetSize(em->event_log);
            if (max_number_of_events > 0) //there are no events
            {
                Member current_member;
                for (; max_number_of_events > 0; max_number_of_events--)
                {
                    current_member = pqGetFirst(em -> member_log);
                    while (current_member != NULL)
                    {
                        if (memberGetNumberOfLinkedEvents(current_member) == max_number_of_events)
                        {
                            fprintf(stream,"%s,%d\n",memberGetName(current_member),max_number_of_events);
                        }
                        current_member = pqGetNext(em->member_log);
                    }

                }
            }

            fclose(stream);
        }
    }
}


//static functions

static void printMembersInEventToFile(FILE* stream, PriorityQueue member_log, Event event)
{
    Member current_member = pqGetFirst(member_log);
    while (current_member != NULL)
    {
        if (memberCheckIfEventIsLinked(eventGetId(event), current_member))
        {
            fprintf(stream, ",%s", memberGetName(current_member));
        }

        current_member = pqGetNext(member_log);
    }
}

static EventManagerResult checkIfEventNameOrIdExist(EventManager em, Date date, char* event_name, int event_id)
{
    if (event_id < 0)
    {
        return EM_INVALID_EVENT_ID;
    }
    Event current_event = pqGetFirst(em->event_log);
    while (current_event != NULL)
    {
        if (dateCompare(eventGetDate(current_event), date) == 0)
        {
            if (strcmp(event_name, eventGetName(current_event)) == 0)
            {
                return EM_EVENT_ALREADY_EXISTS;
            }
        }
        if (eventGetId(current_event) == event_id)
        {
            return EM_EVENT_ID_ALREADY_EXISTS;
        }
        current_event = pqGetNext(em->event_log);
    }
    return EM_SUCCESS;
}

static PQElement copyElementEvent(PQElement element_event)
{
    if (element_event == NULL)
    {
        return NULL;
    }
    Event cast_event = (struct event_struct_t*)element_event;
    Event copy_event = eventCreate(eventGetName(cast_event),eventGetDate(cast_event), eventGetId(cast_event));
    return (PQElement*)copy_event;
}


static void freeElementEvent(PQElement event)
{
    if (event == NULL)
    {
        return;
    }
    Event cast_event = (struct event_struct_t*)event;
    eventDestroy(cast_event);
}



static int comparePriorityDate(PQElementPriority date1, PQElementPriority date2)
{
    return dateCompare((struct Date_t*)date2, (struct Date_t*)date1);
}

static bool compareElementEventId(PQElement event1, PQElement event2)
{
    if (event1 == NULL || event2 == NULL)
    {
        return false;
    }
    int event1_id = eventGetId((struct event_struct_t*)event1);
    int event2_id = eventGetId((struct event_struct_t*)event2);

    return (event1_id == event2_id);
}

static PQElementPriority copyPriorityDate(PQElementPriority date)
{
    if (date == NULL)
    {
        return NULL;
    }
    Date cast_date = (struct Date_t*)date;
    return (PQElementPriority*)dateCopy(cast_date);
}

static void destroyPriorityDate(PQElementPriority date)
{
    if (date == NULL)
    {
        return;
    }
    Date cast_date = (struct Date_t*)date;
    dateDestroy(cast_date);
}

static PQElement copyElementMember(PQElement member) 
{
    if (member == NULL)
    {
        return NULL;
    }
    Member cast_member = (struct member_struct_t*)member;
    return (PQElement*)memberCreate(memberGetName(cast_member), memberGetId(cast_member));
}

static void freeElementMember(PQElement member)
{
    if (member == NULL)
    {
        return;
    }
    memberDestroy((struct member_struct_t*)member);
}



static bool compareElementMemberId(PQElement member1, PQElement member2)
{
    if (member1 == NULL || member2 == NULL)
    {
        return false;
    }
    int member1_id = memberGetId((struct member_struct_t*)member1);
    int member2_id = memberGetId((struct member_struct_t*)member2);

    return (member1_id == member2_id);
}

static PQElementPriority copyPriorityMemberId(PQElementPriority member_id)
{
    if (member_id == NULL)
    {
        return NULL;
    }

    int* new_id = malloc(sizeof(*new_id));
    if (new_id == NULL)
    {
        return NULL;
    }

    *new_id = *(int*)member_id;
    return (PQElementPriority*)new_id;
}

static void freePriorityMemberId(PQElementPriority member_id)
{
    free(member_id);
}

static int comparePriorityMemberId(PQElementPriority id1, PQElementPriority id2)
{
    if (id1 == NULL || id2 == NULL)
    {
        return 0;
    }

    if (*(int*)id1 < *(int*)id2)
    {
        return 1;
    }
    else if (*(int*)id1 == *(int*)id2)
    {
        return 0;
    }
    return -1;

}



static Member findMemberById(PriorityQueue member_log, int member_id)
{
    if (member_id < 0)
    {
        return NULL;
    }

    Member member = pqGetFirst(member_log);
    while (member != NULL)
    {
        if (memberGetId(member) != member_id)
        {
            member = pqGetNext(member_log);

        }
        else
        {
            return member;
        }
    }

    return NULL;
}


static Event findEventByEventId(PriorityQueue event_log, int event_id)
{
    if (event_id < 0)
    {
        return NULL;
    }

    Event event = pqGetFirst(event_log);
    while (event != NULL)
    {
        if (eventGetId(event) != event_id)
        {
            event = pqGetNext(event_log);
        }
        else
        {
            return event;
        }
    }

    return NULL;
}

static EventManagerResult deleteFormerEvents(EventManager em, Date system_date)
{
    EventManagerResult remove_event;
    Date event_date;
    PriorityQueue event_log = em->event_log;

    Event event = pqGetFirst(event_log);
    while (event != NULL)
    {
        event_date = eventGetDate(event);

        if (dateCompare(event_date, system_date) < 0)
        {
            remove_event = emRemoveEvent(em, eventGetId(event));
            if (remove_event != EM_SUCCESS)
            {
                return remove_event;
            }

            event = pqGetFirst(event_log);
        }
        else
        {
            event = pqGetNext(event_log);
        }
    }

    return EM_SUCCESS;
}

static void removeLinkBetweenAllMembersToEvent(PriorityQueue member_log, int event_id)
{
    Member current_member = pqGetFirst(member_log);
    while (current_member != NULL)
    {
        memberRemoveEventLink(current_member, event_id);
        current_member = pqGetNext(member_log);
    }
}

static bool checkIfEventAlreadyExists(PriorityQueue event_log, Date event_date, char * event_name)
{
    Event current_event = pqGetFirst(event_log);
    while (current_event != NULL)
    {
        if (dateCompare(eventGetDate(current_event),event_date) == 0)
        {
            if (strcmp(eventGetName(current_event), event_name) == 0)
            {
                return true;
            }
        }

        current_event = pqGetNext(event_log);
    }
    return false;
}