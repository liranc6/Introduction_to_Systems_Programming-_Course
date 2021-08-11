#include "open_event.h"

namespace mtm
{
    OpenEvent::OpenEvent(const DateWrap date, const string name) : BaseEvent(date, name) {}

    BaseEvent* OpenEvent::clone() const
    {
        OpenEvent* copy = new OpenEvent(*this);
        return copy;
    }
}