#ifndef HSG_EVENTDISPATCHER_H_
#define HSG_EVENTDISPATCHER_H_

#include "Event.h"
#include <boost/thread/recursive_mutex.hpp>
#include <boost/scoped_ptr.hpp>
#include <map>
#include <vector>

namespace hsg {

    class IEventListener;

    class EventDispatcher {
    public:
	EventDispatcher();
	~EventDispatcher();

	void postEvent(const Event::ptr& event);
	void processEvents();
	void subscribe(EventType enType, IEventListener* listener);
	void unsubscribe(EventType enType, IEventListener* listener);

    private:
	Event::vec m_firstQueue;
	Event::vec m_secondQueue;

	Event::vec* m_pendingQueue;
	Event::vec* m_workingQueue;

	boost::recursive_mutex m_rmx;
	
	std::map<EventType, std::vector<IEventListener*> > m_listeners;

	void swapQueues();
	void processEvent(const Event::ptr& event);
    };

} /* namespace hsg */
#endif /* HSG_EVENTDISPATCHER_H_ */
