#ifndef BASE_EVENT_H
#define BASE_EVENT_H

#include <iostream>
using std::string;


#include "date_wrap.h"
#include "generic_list.h"
#include "exceptions.h"

namespace mtm
{
    class BaseEvent
    {
        DateWrap event_date;
        string event_name;

    protected:
        GenericList<int> student_list;

        /**
        * validateStudentId: Checks if the student id is within the defined threshold.
        *
        * @param student_id - the id that is validated
        * @return
        * 	true - if the id is between 1 and 1234567890
        * 	false -  if it is not in the threshold.
        */
        static bool validateStudentId(const int student_id);

    public:
        BaseEvent(const DateWrap date, const string name);
        virtual ~BaseEvent() = default;

        virtual void registerParticipant(const int student_id);
        void unregisterParticipant(const int student_id);
        std::ostream& printShort(std::ostream& os) const;
        std::ostream& printLong(std::ostream& os) const;
        virtual BaseEvent* clone() const = 0;

        /**
        * getDate: gets and returns the date of the event
        *
        * @return - the date object
        */
        DateWrap getDate() const;


        /**
        * operator<<: prints to the outstream the event in the format "'event_name' 'event_date'"
        */
        friend std::ostream& operator<<(std::ostream& os, const BaseEvent& event1);

        /**
        * operator==: Two events will be equal if their dates and names are equal
        */
        friend bool operator==(const BaseEvent& event1, const BaseEvent& event2);

        /**
        * operator<: The smaller event is the one with the earliest date, if the dates are equal then the
        *            smaller event is the one with the lexicographicly smaller name.
        */
        friend bool operator<(const BaseEvent& event1, const BaseEvent& event2);

    };

}

#endif //BASE_EVENT_H

