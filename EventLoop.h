#ifndef HSG_EVENTLOOP_H_
#define HSG_EVENTLOOP_H_

#include "Context.h"
#include "ScreenMaster.h"
#include "IEventListener.h"

#include <boost/atomic.hpp>

namespace hsg {

    class EventDispatcher;

    class EventLoop: IEventListener {
    public:
	EventLoop(Context* context);
	~EventLoop();

	void operator()();	
	void onEvent(const Event::ptr& event);

    private:
	EventDispatcher* m_gameQueue;
	ScreenMaster m_screenMaster;
	
	boost::atomic<bool> m_run;
    };

} /* namespace hsg */
#endif /* HSG_EVENTLOOP_H_ */
