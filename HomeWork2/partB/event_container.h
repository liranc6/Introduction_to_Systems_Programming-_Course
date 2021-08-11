#ifndef EVENT_CONTAINER_H
#define EVENT_CONTAINER_H

#include "base_event.h"
#include "event_iterator_inner.h"
#include "const_event_iterator_inner.h"

namespace mtm
{
    class EventContainer
    {
    protected:

        GenericList<BaseEvent&> event_list;

    public:

        EventContainer() {}
        /**
        * destructor: the events are saved by reference so we need a destructor to go over the list and delete the
        *               events
        */
        virtual ~EventContainer();
        /**
        * copy constructor: creates a new generic list by using the clone function on each element in the event list,
        *                   and inserts it into the current event_list
        */
        EventContainer(const EventContainer& container);
        /**
        * copy assignment: creates a copy of an event list in the same way the ctor does, and frees all the old
        *               events like the destructor does, and then copy assigns the copy generic list into event_list
        */
        EventContainer& operator=(const EventContainer& container);

        virtual void add(const BaseEvent& event) = 0;

        typedef EventIteratorInner EventIterator;
        EventIteratorInner begin();
        EventIteratorInner end();

        /**
        * ConstEventIterator: a const iterator is needed for the printing functions in the schedule
        */
        typedef ConstEventIteratorInner ConstEventIterator;
        const ConstEventIteratorInner begin() const;
        const ConstEventIteratorInner end() const;

    };
} // namespace mtm

#endif //EVENT_CONTAINER_H