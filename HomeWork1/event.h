#ifndef EVENT_H
#define EVENT_H

#include "date.h"
#include <stdbool.h>



/** Type for defining the event */
typedef struct event_struct_t* Event;

/**
* eventGetId: returns an events id
* @param event - event pointer
* @return
* the events id
*/
int eventGetId(Event event);


/**
* eventGetName: returns an events name
* @param event - event pointer
* @return
* a pointer of the events name
*/
char* eventGetName(Event event);


/**
* eventGetDate: returns a pointer of an events date
* @param event - event pointer
* @return
* the events date
*/
Date eventGetDate(Event event);


/**
* eventChangeDate: changes the date of an event with a new date by deleting the old date and copying the new one
* @param event - event pointer
* @param new_date - a date pointer to the new date
* @return
* true if the change succeeds, false if there was a memory error
*/
bool eventChangeDate(Event event, Date new_date);


/**
* eventCreate: creates new event and assigns a name, id, and date
* @param event_name - new name for event
* @param new_date - new date for the event
* @param event_id - new event id
* @return
* NULL if there was a memory error or one of the paramaters was NULL, or a pointer to the event if it is created
*/
Event eventCreate(char* event_name, Date date, int event_id);


/**
* eventDestroy: deallocate an event
* @param event - event pointer
*/
void eventDestroy(Event event);




#endif /* EVENT_H */
#pragma once