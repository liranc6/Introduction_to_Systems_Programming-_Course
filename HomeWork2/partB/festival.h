#ifndef FESTIVAL_H
#define FESTIVAL_H

#include "event_container.h"

namespace mtm
{
    class Festival : public EventContainer
    {
        DateWrap festival_date;

    public:
        Festival(const DateWrap date) : festival_date(date) {}

        void add(const BaseEvent& event) override;
    };

} // namespace mtm

#endif