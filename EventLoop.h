#ifndef HSG_EVENTLOOP_H_
#define HSG_EVENTLOOP_H_

#include "EventDispatcher.h"
#include <boost/atomic.hpp>

namespace hsg {

    class EventLoop {
    public:
	EventLoop(EventDispatcher* appQueue, EventDispatcher* gameQueue);
	virtual ~EventLoop();

	void operator()();
    private:
	EventDispatcher* m_gameQueue;
	EventMaster m_eventMaster;
	ScreenMaster m_screenMaster;
	
	boost::atomic<bool> m_run;
    };

} /* namespace hsg */
#endif /* HSG_EVENTLOOP_H_ */
