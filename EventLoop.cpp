#include "EventLoop.h"
#include "EventDispatcher.h"
#include "Log.h"

namespace hsg {

    EventLoop::EventLoop(Context* context):
	m_gameQueue(context->gameQueue),
	m_screenMaster(context),
	m_run(true){

    }

    EventLoop::~EventLoop(){}

    void EventLoop::operator()(){
	HSG_DEBUG("EventLoop: started");
	m_screenMaster.startScreen();
	while(m_run){
	    m_gameQueue->processEvents();	    
	    m_screenMaster.update();
	}
    }

    void EventLoop::onEvent(const Event::ptr& event){
	switch(event->getEventType()){
	case SYSTEM_EXIT:
	    m_run = false;
	    break;
	}
    }
} /* namespace hsg */
