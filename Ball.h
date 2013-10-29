#ifndef HSG_BALL_H_
#define HSG_BALL_H_

#include "Context.h"
#include "GameLayout.h"
#include "PhysicsObject.h"
#include "GraphicsSprite.h"

namespace hsg {

    class Ball {
    public:
	Ball(Context* context, BallLayout* layout);
	~Ball();
	
	void spawn();
	void update();

    private:
	GraphicsService* m_graphics;
	PhysicsObject::ptr m_physics;
	GraphicsSprite* m_sprite;
	BallLayout m_layout;
	b2CircleShape m_shapeDef;
    };

} /* namespace hsg */
#endif /* HSG_BALL_H_ */
