#include "closed_event.h"
#include "exceptions.h"


namespace mtm
{
    ClosedEvent::ClosedEvent(const DateWrap date, const string name) : BaseEvent(date, name) {}


    void ClosedEvent::addInvitee(const int student_id)
    {
        if (validateStudentId(student_id) == false)
        {
            throw InvalidStudent();
        }
        if (invitee_list.checkIfElementIsInList(student_id) == true)
        {
            throw AlreadyInvited();
        }
        invitee_list.addElementToGenericListSortedByRising(student_id);
    }


    void ClosedEvent::registerParticipant(const int student_id)
    {
        if (validateStudentId(student_id) == false)
        {
            throw InvalidStudent();
        }
        if (invitee_list.checkIfElementIsInList(student_id) == false)
        {
            throw RegistrationBlocked();
        }
        if (student_list.checkIfElementIsInList(student_id) == true)
        {
            throw AlreadyRegistered();
        }
        student_list.addElementToGenericListSortedByRising(student_id);
    }


    BaseEvent* ClosedEvent::clone() const
    {
        ClosedEvent* copy = new ClosedEvent(*this);
        return copy;
    }
}