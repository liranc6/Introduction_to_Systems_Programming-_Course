#include "event_container.h"

namespace mtm
{
    EventContainer::~EventContainer()
    {
        GenericNode<BaseEvent&>* current_node = event_list.getFirstNode();
        while (current_node != NULL)
        {
            delete &(current_node->element);
            current_node = current_node->next;
        }
    }

    EventContainer::EventContainer(const EventContainer& container)
    {
        GenericList<BaseEvent&> new_list;
        const GenericNode<BaseEvent&>* current_node = container.event_list.getFirstNode();
        while (current_node != NULL)
        {
            new_list.addElementToEndOfList(*(current_node->element.clone()));
            current_node = current_node->next;
        }
        event_list = new_list;
    }

    EventContainer& EventContainer::operator=(const EventContainer& container)
    {
        if (this == &container)
        {
            return *this;
        }
        GenericList<BaseEvent&> new_list;
        const GenericNode<BaseEvent&>* current_node = container.event_list.getFirstNode();
        while (current_node != NULL)
        {
            new_list.addElementToEndOfList(*(current_node->element.clone()));
            current_node = current_node->next;
        }

        current_node = event_list.getFirstNode();
        while (current_node != NULL)
        {
            delete& (current_node->element);
            current_node = current_node->next;
        }
        event_list = new_list;
        return *this;       
    }

    EventIteratorInner EventContainer::begin()
    {
        return EventIteratorInner(event_list.getFirstNode());
    }


    EventIteratorInner EventContainer::end()
    {
        return EventIteratorInner(NULL);
    }

    const ConstEventIteratorInner EventContainer::begin() const
    {
        return  ConstEventIteratorInner(event_list.getFirstNode());
    }


    const ConstEventIteratorInner EventContainer::end() const
    {
        return ConstEventIteratorInner(NULL);
    }

} // namespace mtm