#include "EventLoop.h"
#include "EventDispatcher.h"

namespace hsg {

    EventLoop::EventLoop(Context* context):
	m_gameQueue(context->gameQueue),
	m_screenMaster(context),
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
