#ifndef RECURRING_EVENT_H
#define RECURRING_EVENT_H

#include "event_container.h"


namespace mtm
{
    template<class EventType>
    class RecurringEvent : public EventContainer
    {

    public:

        RecurringEvent(const DateWrap first_date,const string name,const int num_occurrences,const int interval_days);

        void add(const BaseEvent& event) override { throw NotSupported(); }
    };

    template<class EventType>
    RecurringEvent<EventType>::RecurringEvent(const DateWrap first_date, const string name, 
                                               const int num_occurrences, const int interval_days)
    {
        if (num_occurrences <= 0)
        {
            throw InvalidNumber();
        }

        if (interval_days <= 0)
        {
            throw InvalidInterval();
        }

        DateWrap event_date = first_date;

        for (int interval = 0; interval < num_occurrences; interval++)
        {
            EventType recurring_event(event_date, name);
            event_list.addElementToEndOfList(*recurring_event.clone());
            event_date += interval_days;
        }

    }


}



#endif