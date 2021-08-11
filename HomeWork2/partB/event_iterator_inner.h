#ifndef EVENT_ITERATOR_H
#define EVENT_ITERATOR_H

#include "generic_list.h"
#include "base_event.h"


namespace mtm
{
    class EventIteratorInner
    {
    private:
        GenericNode<BaseEvent&>* event_node;

        friend class EventContainer;

    public:
        EventIteratorInner(GenericNode<BaseEvent&>* event) : event_node(event) {}

        EventIteratorInner& operator++();
        BaseEvent& operator*();

        friend bool operator==(const EventIteratorInner& iter1, const EventIteratorInner& iter2);
    };

    bool operator!=(const EventIteratorInner& iter1, const EventIteratorInner& iter2);
} 


#endif //EVENT_ITERATOR_H