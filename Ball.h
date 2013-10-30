#ifndef HSG_BALL_H_
#define HSG_BALL_H_

#include "Context.h"
#include "GameLayout.h"
#include "PhysicsObject.h"
#include "GraphicsSprite.h"
#include "IEventListener.h"

namespace hsg {

    class Ball: public IEventListener {
    public:
	Ball(Context* context, BallLayout* layout);
	~Ball();
	
	void spawn();
	void update();

	void onEvent(const Event::ptr& event);

    private:
	CoordSystem* m_coordSystem;
	GraphicsService* m_graphics;
	PhysicsService* m_physicsService;
	EventDispatcher* m_gameQueue;
	PhysicsObject::ptr m_physics;
	GraphicsSprite* m_sprite;
	BallLayout m_layout;
	b2CircleShape m_shapeDef;
	float m_worldEdge;
    };

} /* namespace hsg */
#endif /* HSG_BALL_H_ */
