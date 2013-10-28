#ifndef HSG_EVENTDISPATCHER_H_
#define HSG_EVENTDISPATCHER_H_

#include "Event.h"
#include <boost/thread/recursive_mutex.hpp>
#include <boost/scoped_ptr.hpp>
#include <map>

namespace hsg {

class EventDispatcher {
public:
	EventDispatcher();
	~EventDispatcher();

	void postEvent(const Event::ptr& event);
	void update();
	void subscribe(EventType enType, IEventListener* listener);

private:
	void swapQueues();

private:
	Event::vec m_firstQueue;
	Event::vec m_secondQueue;

	Event::vec* m_pendingQueue;
	Event::vec* m_workingQueue;

	boost::recursive_mutex m_rmx;
	
	std::map<EventType, IEventListener*> m_listeners;

	bool findSlot(const EventSlot& slot, EventType eventType);
	void updateListeners(const EventSlot& slot);
	
};

} /* namespace hsg */
#endif /* HSG_EVENTDISPATCHER_H_ */
