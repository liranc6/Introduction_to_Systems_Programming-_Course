#include "const_event_iterator_inner.h"

namespace mtm
{

    const ConstEventIteratorInner& ConstEventIteratorInner::operator++()
    {
        event_node = this->event_node->next;

        return *this;
    }

    const BaseEvent& ConstEventIteratorInner::operator*()
    {
        return event_node->element;
    }

    bool operator==(const ConstEventIteratorInner& iter1, const ConstEventIteratorInner& iter2)
    {
        return iter1.event_node == iter2.event_node;
    }

    bool operator!=(const ConstEventIteratorInner& iter1, const ConstEventIteratorInner& iter2)
    {
        return !(iter1 == iter2);
    }
} // namespace mtm