#include "festival.h"


namespace mtm
{

    void Festival::add(const BaseEvent& event)
    {
        if (event.getDate() != festival_date)
        {
            throw DateMismatch();
        }

        event_list.addElementToGenericListSortedByRising(*event.clone());
    }

} // namespace mtm