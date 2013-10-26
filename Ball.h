#ifndef HSG_BALL_H_
#define HSG_BALL_H_

#include "GameLayout.h"
#include "PhysicsObject.h"
#include "GraphicsSprite.h"

namespace hsg {

class Ball {
public:
	Ball(BallLayout* layout);
	virtual ~Ball();
	
	void spawn();
	void update();

private:
	GraphicsService* m_graphicsService;
	PhysicsObject* m_physics;
	GraphicsSprite* m_sprite;
	BallLayout m_layout;
};

} /* namespace hsg */
#endif /* HSG_BALL_H_ */
