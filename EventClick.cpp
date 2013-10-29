#include "EventClick.h"

namespace hsg {

    EventClick::EventClick(float fx, float fy):
	Event(SYSTEM_MOUSE_CLICK),
	x(fx),y(fy){
    }
}
