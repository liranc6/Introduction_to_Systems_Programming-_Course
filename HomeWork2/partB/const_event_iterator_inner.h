#ifndef CONST_EVENT_ITERATOR_H
#define CONST_EVENT_ITERATOR_H

#include "generic_list.h"
#include "base_event.h"


namespace mtm
{
    /**
        * ConstEventIterator: the class is identical to the regular iterator only with a const pointer to the node
        */
    class ConstEventIteratorInner
    {
    private:
        const GenericNode<BaseEvent&>* event_node;

        friend class EventContainer;

    public:
        ConstEventIteratorInner(const GenericNode<BaseEvent&>* event) : event_node(event) {}

        const ConstEventIteratorInner& operator++();
        const BaseEvent& operator*();

        friend bool operator==(const ConstEventIteratorInner& iter1, const ConstEventIteratorInner& iter2);
    };

    bool operator!=(const ConstEventIteratorInner& iter1, const ConstEventIteratorInner& iter2);
}


#endif //CONST_EVENT_ITERATOR_H