#ifndef HSG_EVENTLOOP_H_
#define HSG_EVENTLOOP_H_

#include "EventDispatcher.h"

namespace hsg {

    class EventLoop {
    public:
	EventLoop(EventDispatcher* appQueue, EventDispatcher* gameQueue);
	virtual ~EventLoop();

	void operator()();
    private:
	EventDispatcher* m_eventDispatcher;
	ScreenMaster m_screenMaster;
    };

} /* namespace hsg */
#endif /* HSG_EVENTLOOP_H_ */
