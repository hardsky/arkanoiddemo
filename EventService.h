#ifndef HSG_EVENTDISPATCHER_H_
#define HSG_EVENTDISPATCHER_H_

#include "Event.h"
#include <boost/thread/recursive_mutex.hpp>

namespace hsg {

class EventService {
public:
	EventService();
	~EventService();

	void postEvent(const Event::ptr& event);
	void update();
	void subscribe();

private:
	void swapQueues();

private:
	Event::vec m_firstQueue;
	Event::vec m_secondQueue;

	Event::vec* m_pendingQueue;
	Event::vec* m_workingQueue;

	boost::recursive_mutex m_rmx;
};

} /* namespace hsg */
#endif /* HSG_EVENTDISPATCHER_H_ */
