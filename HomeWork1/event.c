#include "date.h"
#include "event.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define NULL_ARGUMENT -1

struct event_struct_t
{
    Date date; 
    char* event_name;
    int event_id;
};


int eventGetId(Event event)
{
    if (event == NULL)
    {
        return NULL_ARGUMENT;
    }
    return event->event_id;
}


char* eventGetName(Event event)
{
    if (event == NULL)
    {
        return NULL;
    }
    return event -> event_name;
}


Date eventGetDate(Event event)
{
    if (event == NULL)
    {
        return NULL;
    }
    return event->date;
}


bool eventChangeDate(Event event,Date new_date)
{
    Date new_copy = dateCopy(new_date);
    if (new_copy == NULL)
    {
        return false;
    }
    dateDestroy(event->date);
    event->date = new_copy;
    return true;
}


Event eventCreate(char* event_name, Date date, int event_id)
{
    if (event_name == NULL || date == NULL || event_id < 0)
    {
        return NULL;
    }

    Event new_event = malloc(sizeof(*new_event));
    if (new_event == NULL)
    {
        return NULL;
    }

    char* new_name = malloc(strlen(event_name) + 1);
    if (new_name == NULL)
    {
        free(new_event);
        return NULL;
    }
    new_event->event_name = strcpy(new_name, event_name);
    
    new_event->date = dateCopy(date);
    if (new_event->date == NULL)
    {
        free(new_event->event_name);
        free(new_event);
        return NULL;
    }

    new_event->event_id = event_id;

    return new_event;
}


void eventDestroy(Event event)
{
    if (event != NULL)
    {
        dateDestroy(event->date);
        free(event->event_name);
        free(event);
    }
}

