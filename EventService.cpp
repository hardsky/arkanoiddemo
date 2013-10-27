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
	for_each(m_workingQueue, bind(&IEventListener::onEvent, 
    }

    void EventService::swapQueues() {
	boost::lock_guard<boost::recursive_mutex> guard(m_rmx);
	std::swap(m_pendingQueue, m_workingQueue);
    }

    void EventService::subscribe(EventType enType, IEventListener* listener){
	std::vector<EventSlot::ptr> finded = std::find_if(m_eventSlots.begin(), m_eventSlots.end(), bind(&EventService::findSlot, this, _1, enType));
	if(finded != m_eventSlots.end()){
	    (*finded)->listeners.push_back(listener);
	}
	else{
	
	    EventSlot::ptr slot(new EventSlot());
	    slot->eventType = enType;
	    slot->listeners.push_back(listener);
	}
    }			

    bool EventService::findSlot(const EventSlot& slot, EventType eventType){
	return slot.eventType == eventType;
    }
		 
		 void EventService::updateListeners(const EventSlot& slot){
		     
		 }

} /* namespace hsg */
