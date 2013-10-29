#ifndef HSG_CONTEXT_H_
#define HSG_CONTEXT_H_

namespace hsg{
    class CoordSystem;
    class GraphicsService;
    class TimeService;
    class PhysicsService;
    class EventDispatcher;

    struct Context{
	CoordSystem* coordSystem;
	GraphicsService* graphicsService;
	TimeService* timeService;
	PhysicsService* physicsService;
	EventDispatcher* appQueue;
	EventDispatcher* gameQueue;
    };
}

#endif /* HSG_CONTEXT_H_ */
