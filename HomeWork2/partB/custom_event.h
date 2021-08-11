#ifndef CUSTOM_EVENT_H
#define CUSTOM_EVENT_H

#include "base_event.h"

namespace mtm 
{

    template<class CanRegister>
    class CustomEvent : public BaseEvent
    {
        CanRegister register_function;

    public:
        CustomEvent(const DateWrap date, const string name, const CanRegister function) : BaseEvent(date, name), 
                                                                                         register_function(function){}
        void registerParticipant(const int student_id) override;
        BaseEvent* clone() const override;
    };

    template<class CanRegister>
    void CustomEvent<CanRegister>::registerParticipant(const int student_id) 
    {
        if (validateStudentId(student_id) == false)
        {
            throw InvalidStudent();
        }
        if (register_function(student_id) == false)
        {
            throw RegistrationBlocked();
        }
        if (student_list.checkIfElementIsInList(student_id) == true)
        {
            throw AlreadyRegistered();
        }
        student_list.addElementToGenericListSortedByRising(student_id);
    }


    template<class CanRegister>
    BaseEvent* CustomEvent<CanRegister>::clone() const
    {
        CustomEvent<CanRegister>* copy = new CustomEvent<CanRegister>(*this);
        return copy;
    }
}


#endif //CUSTOM_EVENT_H