#include "base_event.h"

#define MINIMUM_STUDENT_ID 1
#define MAXIMUM_STUDENT_ID 1234567890

namespace mtm
{
    BaseEvent::BaseEvent(const DateWrap date, const string name) : event_date(date), event_name(name) {}

    void BaseEvent::registerParticipant(const int student_id)
    {
        if (validateStudentId(student_id) == false)
        {
            throw InvalidStudent();
        }
        if (student_list.checkIfElementIsInList(student_id) == true)
        {
            throw AlreadyRegistered();
        }
        student_list.addElementToGenericListSortedByRising(student_id);
    }

    void BaseEvent::unregisterParticipant(const int student_id)
    {
        if (validateStudentId(student_id) == false)
        {
            throw InvalidStudent();
        }
        if (student_list.removeNodeWithElement(student_id) == false)
        {
            throw NotRegistered();
        }
    }

    std::ostream& BaseEvent::printShort(std::ostream& os) const
    {
        return os << event_name << " " << event_date << std::endl;
    }

    std::ostream& BaseEvent::printLong(std::ostream& os) const
    {
        this->printShort(os);
        student_list.printEntireList(os);
        return os;
    }

    bool BaseEvent::validateStudentId(const int student_id)
    {
        return (student_id >= MINIMUM_STUDENT_ID) && (student_id <= MAXIMUM_STUDENT_ID);
    }

    std::ostream& operator<<(std::ostream& os, const BaseEvent& event1)
    {
        return os << event1.event_name << " " << event1.event_date;
    }

    bool operator==(const BaseEvent& event1, const BaseEvent& event2)
    {
        if ((event1.event_date == event2.event_date) && (event1.event_name == event2.event_name))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator<(const BaseEvent& event1, const BaseEvent& event2)
    {
        if (event1.event_date == event2.event_date)
        {
            return event1.event_name < event2.event_name;
        }
        else
        {
            return event1.event_date < event2.event_date;
        }
    }

    DateWrap BaseEvent::getDate() const //const BaseEvent &event
    {
        return event_date;
    }


}
