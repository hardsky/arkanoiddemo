#include "EventLoop.h"

namespace hsg {

    EventLoop::EventLoop(EventDispatcher* eventDispatcher):
	m_eventDispatcher(eventDispatcher),
	m_screenMaster(eventDispatcher){

    }

    void EventLoop::operator()(){
	while(true){
	    m_eventDispatcher->processEvents();
	    if(m_eventDispatcher.isExit())
		return;
	    
	    m_screenMaster.update();
	}
    }
} /* namespace hsg */
