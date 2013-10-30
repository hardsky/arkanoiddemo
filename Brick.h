#ifndef HSG_BRICK_H_
#define HSG_BRICK_H_

#include "Context.h"
#include "PhysicsObject.h"
#include "GraphicsSprite.h"
#include "GameLayout.h"

#include <boost/shared_ptr.hpp>
#include <vector>

namespace hsg {

class Brick {
public:
	typedef boost::shared_ptr<Brick> ptr;
	typedef std::vector<ptr> vec;
public:
	Brick(Context* context, BrickLayout& layout);
	~Brick();

	void spawn();
	void update();
	bool collided() const;

private:
	GraphicsService* m_graphicsService;
	PhysicsService* m_physicsService;
	PhysicsObject::ptr m_physics;
	GraphicsSprite* m_sprite;
	BrickLayout m_layout;
	b2PolygonShape m_shapeDef;
};

} /* namespace hsg */
#endif /* HSG_BRICK_H_ */
