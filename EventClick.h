#ifndef HSG_EVENTCLICK_H
#define HSG_EVENTCLICK_H

#include "Event.h"

namespace hsg {
    class EventClick: public Event {
    public:
	EventClick(float fx, float fy);
	float x;
	float y;
    };
}
#endif
