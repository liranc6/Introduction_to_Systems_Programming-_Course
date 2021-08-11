#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <iostream>

namespace mtm
{
    class Exception : public std::exception {};

    class InvalidDate : public Exception {};
    class NegativeDays : public Exception {};

    class InvalidStudent : public Exception {};
    class AlreadyRegistered : public Exception {};
    class NotRegistered : public Exception {};
    class AlreadyInvited : public Exception {};
    class RegistrationBlocked : public Exception {};

    class EventAlreadyExists : public Exception {};
    class EventDoesNotExist : public Exception {};
    class DateMismatch : public Exception {};
    class InvalidNumber : public Exception {};
    class InvalidInterval : public Exception {};
    class NotSupported : public Exception {};
}

#endif //EXCEPTIONS_H_

