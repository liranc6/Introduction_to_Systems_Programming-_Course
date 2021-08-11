#ifndef DATE_WRAP_H
#define DATE_WRAP_H

#include "exceptions.h"
#include <iostream>
using std::ostream;

extern "C" {
#include "date.h"
}

namespace mtm
{
    class DateWrap {
        Date date;
        int current_day, current_month, current_year;

    public:
        DateWrap(const int day, const int month, const int year);

        DateWrap(const DateWrap& date1);
        ~DateWrap();
        DateWrap& operator=(const DateWrap& date1);

        int day() const;
        int month() const;
        int year() const;
        DateWrap operator++(int);
        DateWrap& operator+=(const int days);

        friend ostream& operator<<(ostream& os, const DateWrap& date1);
        friend bool operator==(const DateWrap& date1, const DateWrap& date2);
        friend bool operator<(const DateWrap& date1, const DateWrap& date2);
    };

    bool operator!=(const DateWrap& date1, const DateWrap& date2);
    bool operator>(const DateWrap& date1, const DateWrap& date2);
    bool operator<=(const DateWrap& date1, const DateWrap& date2);
    bool operator>=(const DateWrap& date1, const DateWrap& date2);
    DateWrap operator+(const DateWrap& date1, const int days);
    DateWrap operator+(const int days, const DateWrap& date1);
}


#endif