#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "generic_list.h"
#include "base_event.h"
#include "event_container.h"

namespace mtm
{
	class Schedule
	{
		GenericList<BaseEvent&> schedule_list;


		/**
		* checkIfEventsAreAlreadyInSchedule: compares all the events in the recieved EventContainer with the events
		*				in the schedule_list, if an event is found that is both in the EventContainer and the 
		*				schedule list the function ends
		*
		* @param event_container - an EventContainer object
		* @return -  true - if an event is found that is in both the EventContainer and the schedule_list
		*			 false - if no such event is found
		*/
		bool checkIfEventsAreAlreadyInSchedule(const EventContainer& event_container) const;

		/**
		* getSpecificEventInSchedule: searches the schedule_list for an event equal to comparison_event, if no such
		*							event is found an exception is thrown
		*
		* @param comparison_event - equal to the event that is searched by the function
		* @return -  BaseEvent& - the event in the schedule_list if it is found
		*			if no event is found the exception EventDoesNotExist is thrown
		*/
		BaseEvent& getSpecificEventInSchedule(BaseEvent& comparison_event);
	public:

		Schedule();

		/**
        * destructor: the events are saved by reference so we need a destructor to go over the list and delete the
        *               events
        */ 
		~Schedule();

		/**
        * copy constructor: creates a new generic list by using the clone function on each element in the event list,
        *                   and inserts it into the current event_list
        */
		Schedule(const Schedule& schedule);

		/**
        * copy assignment: creates a copy of an event list in the same way the ctor does, and frees all the old
        *              events like the destructor does, and then copy assigns the copy generic list into schedule_list
        */
		Schedule& operator=(const Schedule& schedule);

		void addEvents(const EventContainer& event_container);
		void registerToEvent(const DateWrap date, const string event_name, const int student_id);
		void unregisterFromEvent(const DateWrap date, const string event_name, const int student_id);
		void printAllEvents() const;
		void printMonthEvents(const int month,const int year) const;

		template<typename Predicate>
		void printSomeEvents(Predicate predicate,const bool verbose = false) const;
		void printEventDetails(const DateWrap date, const string event_name) const;
	};


	template<typename Predicate>
	void Schedule::printSomeEvents(Predicate predicate,const bool verbose) const
	{
		const GenericNode<BaseEvent&>* current_node = schedule_list.getFirstNode();
		while (current_node != NULL)
		{
			if (predicate(current_node->element) == true)
			{
				if (verbose == true)
				{
					current_node->element.printLong(std::cout);
					std::cout << std::endl;
				} 
				else
				{
					current_node->element.printShort(std::cout);
					std::cout << std::endl;
				}
			}
			current_node = current_node->next;
		}
	}
	
}

#endif //SCHEDULE_H
