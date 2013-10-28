#ifndef HSG_CONTEXT_H_
#define HSG_CONTEXT_H_

namespace hsg{
    class CoordSystem;
    class GraphicsService;
    class TimeService;
    class EventDispatcher;

    struct Context{
	CoordSystem* coordService;
	GraphicsService* graphicsService;
	TimeService* timeService;
	EventDispatcher* appQueue;
	EventDispatcher* gameQueue;
    };
}

#endif /* HSG_CONTEXT_H_ */
