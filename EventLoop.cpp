#include "EventLoop.h"

namespace hsg {

    EventLoop::EventLoop(EventDispatcher* appQueue, EventDispatcher* gameQueue):
	m_eventMaster(appQueue, gameQueue),
	m_screenMaster(&m_eventMaster),
	m_run(true){

    }

    void EventLoop::operator()(){
	while(m_run.load(boost::memory_order_accure)){
	    m_gameQueue->processEvents();	    
	    m_screenMaster.update();
	}
    }

    void onEvent(const Event::ptr& event){
	switch(event->getType()){
	case EventType::SYSTEM_EXIT:
	    m_run.store(false, boost::memory_order_release);
	    break;
	}
    }
} /* namespace hsg */
