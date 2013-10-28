#ifndef HSG_CONTEXT_H_
#define HSG_CONTEXT_H_

namespace hsg{
    class CoordSystem;
    class GraphicsService;
    class InputService;
    class TimeService;
    class EventDispatcher;

    struct Context{
	CoordSystem* coordService;
	GraphicsService* graphicsService;
	InputService* inputService;
	TimeService* timeService;
	EventDispatcher* appQueue;
	EventDispatcher* gameQueue;
    };
}

#endif /* HSG_CONTEXT_H_ */
