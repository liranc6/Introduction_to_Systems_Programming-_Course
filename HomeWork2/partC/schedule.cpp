#include "schedule.h"
#include "open_event.h"


namespace mtm
{

	Schedule::Schedule() : schedule_list() {}

	Schedule::~Schedule()
	{
		GenericNode<BaseEvent&>* current_node = schedule_list.getFirstNode();
		while (current_node != NULL)
		{
			delete &(current_node->element);
			current_node = current_node->next;
		}
	}

	Schedule::Schedule(const Schedule& schedule)
	{
		GenericList<BaseEvent&> new_list;
        const GenericNode<BaseEvent&>* current_node = schedule.schedule_list.getFirstNode();
        while (current_node != NULL)
        {
            new_list.addElementToEndOfList(*(current_node->element.clone()));
            current_node = current_node->next;
        }
        schedule_list = new_list;
	}

	Schedule& Schedule::operator=(const Schedule& schedule)
	{
		if (this == &schedule)
        {
            return *this;
        }
        GenericList<BaseEvent&> new_list;
        const GenericNode<BaseEvent&>* current_node = schedule.schedule_list.getFirstNode();
        while (current_node != NULL)
        {
            new_list.addElementToEndOfList(*(current_node->element.clone()));
            current_node = current_node->next;
        }

        current_node = schedule_list.getFirstNode();
        while (current_node != NULL)
        {
            delete &(current_node->element);
            current_node = current_node->next;
        }
        schedule_list = new_list;
        return *this; 
	}

	void Schedule::addEvents(const EventContainer& event_container)
	{
		typedef EventContainer::ConstEventIterator iterator;
		if (checkIfEventsAreAlreadyInSchedule(event_container) == true)
		{
			throw EventAlreadyExists();
		}
		for (iterator iter = event_container.begin(); iter != event_container.end(); ++iter)
		{
			schedule_list.addElementToGenericListSortedByRising(*(*iter).clone());
		}
	}


	void Schedule::registerToEvent(const DateWrap date, const string event_name, const int student_id)
	{
		OpenEvent temp_event(date, event_name);
		BaseEvent& event_for_registering = getSpecificEventInSchedule(temp_event);
		event_for_registering.registerParticipant(student_id);
	}


	void Schedule::unregisterFromEvent(const DateWrap date, const string event_name, const int student_id)
	{
		OpenEvent temp_event(date, event_name);
		BaseEvent& event_for_unregistering = getSpecificEventInSchedule(temp_event);
		event_for_unregistering.unregisterParticipant(student_id);
	}


	void Schedule::printAllEvents() const
	{
		const GenericNode<BaseEvent&>* current_node = schedule_list.getFirstNode();
		while (current_node != NULL)
		{
			current_node->element.printShort(std::cout);
			std::cout << std::endl;
			current_node = current_node->next;
		}
	}


	void Schedule::printMonthEvents(const int month, const int year) const
	{
		const GenericNode<BaseEvent&>* current_node = schedule_list.getFirstNode();
		while (current_node != NULL)
		{
			DateWrap current_date = current_node->element.getDate();
			if (current_date.month() == month && current_date.year() == year)
			{
				current_node->element.printShort(std::cout);
				std::cout << std::endl;
			}
			current_node = current_node->next;
		}
	}

	void Schedule::printEventDetails(const DateWrap date, const string event_name) const
	{
		OpenEvent temp_comparison_event(date,event_name);
		const GenericNode<BaseEvent&>* current_node = schedule_list.getFirstNode();
		while (current_node != NULL)
		{
			if ((current_node->element) == temp_comparison_event)
			{
				current_node->element.printLong(std::cout);
				std::cout << std::endl;
				return;
			}
			current_node = current_node->next;
		}

		throw EventDoesNotExist();
	}

	//private helper functions
	bool Schedule::checkIfEventsAreAlreadyInSchedule(const EventContainer& event_container) const
	{
		typedef EventContainer::ConstEventIterator iterator;
		for (iterator iter = event_container.begin(); iter != event_container.end(); ++iter)
		{
			BaseEvent* compare = (*iter).clone();
			if (schedule_list.checkIfElementIsInList(*compare) == true)
			{
				delete compare;
				return true;
			}
			delete compare;
		}
		return false;
	}

	BaseEvent& Schedule::getSpecificEventInSchedule(BaseEvent& comparison_event)
	{
		GenericNode<BaseEvent&>* current_node = schedule_list.getFirstNode();
		while (current_node != NULL)
		{
			if ((current_node->element) == comparison_event)
			{
				return current_node->element;
			}
			current_node = current_node->next;
		}

		throw EventDoesNotExist();
	}
}
	

