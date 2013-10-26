#include "EventService.h"
#include <boost/thread/locks.hpp>
#include <algorithm>

namespace hsg {

EventService::EventService():
	m_pendingQueue(&m_firstQueue),
	m_workingQueue(&m_secondQueue){

}

EventService::~EventService() {
	// TODO Auto-generated destructor stub
}

void EventService::postEvent(const Event::ptr& event) {
	boost::lock_guard<boost::recursive_mutex> guard(m_rmx);
}

void EventService::update() {
	swapQueues();
}

void EventService::swapQueues() {
	boost::lock_guard<boost::recursive_mutex> guard(m_rmx);
	std::swap(m_pendingQueue, m_workingQueue);
}

} /* namespace hsg */
