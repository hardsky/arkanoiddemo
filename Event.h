#ifndef HSG_EVENT_H_
#define HSG_EVENT_H_

#include "EventType.h"
#include <boost/shared_ptr.hpp>
#include <vector>

namespace hsg {

    class Event {
    public:
	typedef boost::shared_ptr<Event> ptr;
	typedef std::vector<ptr> vec;
    public:
    Event(EventType type):m_type(type){};
	virtual ~Event(){};
	EventType getEventType() const{return m_type;};

    private:
	EventType m_type;
    };

} /* namespace hsg */
#endif /* HSG_EVENT_H_ */
