#ifndef HSG_EVENT_H_
#define HSG_EVENT_H_

#include <boost/shared_ptr.hpp>
#include <vector>

namespace hsg {

class Event {
public:
	typedef boost::shared_ptr<Event> ptr;
	typedef std::vector<ptr> vec;
public:
	Event();
	virtual ~Event();
	EventType getEventType();
};

} /* namespace hsg */
#endif /* HSG_EVENT_H_ */
