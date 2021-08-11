#include "event_iterator_inner.h"

namespace mtm
{

    EventIteratorInner& EventIteratorInner::operator++()
    {
        event_node = this->event_node->next;

        return *this;
    }

    BaseEvent& EventIteratorInner::operator*()
    {
        return event_node->element;
    }

    bool operator==(const EventIteratorInner& iter1, const EventIteratorInner& iter2)
    {
        return iter1.event_node == iter2.event_node;
    }

    bool operator!=(const EventIteratorInner& iter1, const EventIteratorInner& iter2)
    {
        return !(iter1 == iter2);
    }
} // namespace mtm