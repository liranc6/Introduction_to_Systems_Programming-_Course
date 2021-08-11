#ifndef CLOSED_EVENT_H
#define CLOSED_EVENT_H

#include "base_event.h"
#include "generic_list.h"

namespace mtm
{
    class ClosedEvent : public BaseEvent
    {
        GenericList<int> invitee_list;

    public:
        ClosedEvent(const DateWrap date, const string name);
        void addInvitee(const int student_id);
        void registerParticipant(const int student_id) override;
        BaseEvent* clone() const override;
    };
}


#endif //CLOSED_EVENT_H