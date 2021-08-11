#ifndef ONE_TIME_EVENT_H
#define ONE_TIME_EVENT_H

#include "event_container.h"

namespace mtm
{

    template<class EventType>
    class OneTimeEvent :public EventContainer
    {

    public:
        OneTimeEvent(const DateWrap date, string name);

        void add(const BaseEvent& event) override { throw NotSupported();}

    };

    template<class EventType>
    OneTimeEvent<EventType>::OneTimeEvent(const DateWrap date, string name)
    {
        EventType one_time_event(date, name);
        event_list.addElementToGenericListSortedByRising(*one_time_event.clone());
    }

} // namespace mtm

#endif