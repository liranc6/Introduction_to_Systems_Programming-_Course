#include "date_wrap.h"


namespace mtm
{

    DateWrap::DateWrap(const int day, const int month, const int year) :
        current_day(day), current_month(month), current_year(year)
    {
        if(day < 1 || day > 30 || month < 1 || month > 12)
        {
            throw InvalidDate();
        }

        date = dateCreate(day, month, year);
        if (date == NULL)  
        {
            throw std::bad_alloc();
        }

    }

    DateWrap::DateWrap(const DateWrap& date1)
    {
        date = dateCopy(date1.date);
        current_day = date1.current_day;
        current_month = date1.current_month;
        current_year = date1.current_year;
    }

    DateWrap::~DateWrap()
    {
        dateDestroy(date);
    }

    DateWrap& DateWrap::operator=(const DateWrap& date1)
    {
        if (this == &date1)
        {
            return *this;
        }
        Date temp = dateCopy(date1.date);
        dateDestroy(date);
        date = temp;
        dateGet(date, &current_day, &current_month, &current_year);
        return *this;
    }

    int DateWrap::day() const
    {
        return current_day;
    }

    int DateWrap::month() const
    {
        return current_month;
    }

    int DateWrap::year() const
    {
        return current_year;
    }

    DateWrap DateWrap::operator++(int)
    {
        DateWrap temp = *this;
        *this += 1;
        return temp;
    }

    DateWrap& DateWrap::operator+=(const int days)
    {
        if (days < 0)
        {
            throw NegativeDays();
        }

        for (int i = 0; i < days; i++)
        {
            dateTick(date);
        }
        dateGet(date, &current_day, &current_month, &current_year);
        return *this;
    }

    ostream& operator<<(ostream& os, const DateWrap& date1)
    {
        return os << date1.current_day << "/" << date1.current_month << "/" << date1.current_year;
    }

    bool operator==(const DateWrap& date1, const DateWrap& date2)
    {
        if (dateCompare(date1.date, date2.date) == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator<(const DateWrap& date1, const DateWrap& date2)
    {
        if (dateCompare(date1.date, date2.date) < 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator!=(const DateWrap& date1, const DateWrap& date2)
    {
        return !(date1 == date2);
    }

    bool operator>(const DateWrap& date1, const DateWrap& date2)
    {
        return date2 < date1;
    }

    bool operator<=(const DateWrap& date1, const DateWrap& date2)
    {
        return !(date2 < date1);
    }

    bool operator>=(const DateWrap& date1, const DateWrap& date2)
    {
        return !(date1 < date2);
    }

    DateWrap operator+(const DateWrap& date1, const int days)
    {
        if (days < 0)
        {
            throw NegativeDays();
        }

        return DateWrap(date1.day(), date1.month(), date1.year()) += days;
    }

    DateWrap operator+(const int days, const DateWrap& date1)
    {
        return date1 + days;
    }

}