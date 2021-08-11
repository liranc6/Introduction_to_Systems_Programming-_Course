COMP_FLAG = -Wall -pedantic-errors -Werror -DNDEBUG
PRIORITY_QUEUE_OBJS = priority_queue.o priority_queue_item.o
EVENT_MANAGER_OBJS = event_manager.o $(PRIORITY_QUEUE_OBJS) date.o event.o member.o member_linked_event.o
EXECUTABLES = event_manager priority_queue
DEBUG_FLAG = #now empty, assign -g for debug
EVENT_MANAGER_MAIN = tests/event_manager_tests.c
PRIORITY_QUEUE_MAIN = tests/priority_queue_tests.c


event_manager:  $(EVENT_MANAGER_OBJS)
		gcc -std=c99 -o $@ $(COMP_FLAG) $(DEBUG_FLAG) $(EVENT_MANAGER_MAIN) -L. -lpriority_queue $(EVENT_MANAGER_OBJS)

priority_queue: priority_queue.o
		gcc -std=c99 -o $@ $(COMP_FLAG) $(DEBUG_FLAG) $(PRIORITY_QUEUE_MAIN) $(PRIORITY_QUEUE_OBJS)



date.o: date.c date.h
		gcc -c -std=c99 $(COMP_FLAG) $*.c

event.o: event.c event.h date.h
		gcc -c -std=c99 $(COMP_FLAG) $*.c

member_linked_event.o: member_linked_event.c member_linked_event.h
		gcc -c -std=c99 $(COMP_FLAG) $*.c		

member.o: member.c member.h member_linked_event.h
		gcc -c -std=c99 $(COMP_FLAG) $*.c

priority_queue_item.o: priority_queue_item.c priority_queue_item.h
		gcc -c -std=c99 $(COMP_FLAG) $*.c 

priority_queue.o: priority_queue.c priority_queue.h priority_queue_item.h
		gcc -c -std=c99 $(COMP_FLAG) $*.c 

event_manager.o: event_manager.c event_manager.h date.h priority_queue.h
		gcc -c -std=c99 $(COMP_FLAG) $*.c 

clean:
		rm -f $(EVENT_MANAGER_OBJS)	$(EXECUTABLES)	