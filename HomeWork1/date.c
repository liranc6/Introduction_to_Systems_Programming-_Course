#include "date.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX_DAY 30
#define MAX_MONTH 12

struct Date_t{
    int day;
    int month;
    int year;
};

/**
*checkIfDateIsNotValid: checks if the day month and year are illegal values in the calendar
* @param day - the day of the date.
* @param month - the month of the date.
* @param year - the year of the date.
* @return
* 	true - if the day month or year are not valid values.
* 	false - if they are valid.
*/
static bool checkIfDateIsNotValid(int day,int month,int year)
{
    return !((day > 0 && day <= MAX_DAY) && (month > 0 && month <= MAX_MONTH));
}

Date dateCreate(int day, int month, int year)
{
    if(checkIfDateIsNotValid(day,month,year))
    {
        return NULL;
    }

    Date new_date = malloc(sizeof(*new_date));
    if (new_date == NULL)
    {
        return NULL;
    }
    
    new_date -> day = day;
    new_date -> month = month;
    new_date -> year = year;

    return new_date;
}

Date dateCopy(Date date)
{
    if (date == NULL)
    {
        return NULL;
    }

    Date copy_date = dateCreate(date -> day,date -> month,date -> year);
    if (copy_date == NULL)
    {
        return NULL;
    }

    return copy_date;
}

int dateCompare(Date date1, Date date2)
{
    if(date1 == NULL || date2 == NULL)
    {
        return 0;
    }
    if (date1 -> year < date2 -> year)
    {
        return -1;
    }
    else if(date1 -> year == date2 -> year)
    {
        if (date1 -> month < date2 -> month)
        {
            return -1;
        }
        else if(date1 -> month == date2 -> month)
        {
            if(date1 -> day < date2 -> day)
            {
                return -1;
            }
            else if(date1 -> day == date2 -> day)
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 1;
    }
}

void dateDestroy(Date date)
{
    free(date);
}

bool dateGet(Date date, int* day, int* month, int* year)
{
    if (day == NULL || month == NULL || year == NULL)
    {
        return false;
    }
    else
    {
        *day = date->day;
        *month = date->month;
        *year = date->year;

        return true;
    }
}

void dateTick(Date date)
{
    if (date == NULL)
    {
        return;
    }

    (date->day)++;

    if (date->day > MAX_DAY)
    {
        date->day = 1;
        (date->month)++;
    }
    if (date->month > MAX_MONTH)
    {
        date->month = 1;
        (date->year)++;
    }
}