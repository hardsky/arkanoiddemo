#include "EventService.h"
#include <boost/thread/locks.hpp>
#include <algorithm>

namespace hsg {

    EventDispatcher::EventDispatcher():
	m_pendingQueue(&m_firstQueue),
	m_workingQueue(&m_secondQueue){

    }

    EventDispatcher::~EventDispatcher() {
	// TODO Auto-generated destructor stub
    }

    void EventDispatcher::postEvent(const Event::ptr& event) {
	boost::lock_guard<boost::recursive_mutex> guard(m_rmx);
	m_pendingQueue->push_back(event);
    }

    void EventDispatcher::processEvents() {
	swapQueues();
	for_each(*m_workingQueue, bind(&EventDispatcher::processEvent));
	m_workingQueue->clear();
    }

    void EventDispatcher::swapQueues() {
	boost::lock_guard<boost::recursive_mutex> guard(m_rmx);
	std::swap(m_pendingQueue, m_workingQueue);
    }

    void EventDispatcher::subscribe(EventType enType, IEventListener* listener){
	boost::lock_guard<boost::recursive_mutex> guard(m_rmx);

	std::map<EventType, std::vector<IEventListener*> >::iterator finded;
	finded = m_listeners.find(enType);
	if(finded != m_listeners.end()){
	    finded->second.push_back(listener);
	}
	else{
	    std::vector<IEventListener*>& vec = m_listeners[enType];
	    vec.push_back(listener);
	}
	
    }

    void EventDispatcher::unsubscribe(EventType enType, IEventListener* listener){
	boost::lock_guard<boost::recursive_mutex> guard(m_rmx);

	std::map<EventType, std::vector<IEventListener*> >::iterator finded;
	finded = m_listeners.find(enType);
	if(finded != m_listeners.end()){
	    std::vector<IEventListener*>& vec = finded.second;
	    vec.erase(std::remove(vec.begin(), vec.end(), listener), vec.end());
	}
    }			

    void EventDispatcher::processEvent(const Event::ptr& event){
	std::map<EventType, std::vector<IEventListener*> >::iterator finded;
	finded = m_listeners.find(enType);
	if(finded != m_listeners.end()){
	    for_each(finded->second, bind(&IEventListener::onEvent(_1, event)));
	}	
    }

} /* namespace hsg */
