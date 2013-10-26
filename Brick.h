#ifndef HSG_BRICK_H_
#define HSG_BRICK_H_

#include "PhysicsObject.h"
#include "GraphicsSprite.h"

#include <boost/shared_ptr.hpp>
#include <vector>

namespace hsg {

class Brick {
public:
	typedef boost::shared_ptr<Brick> ptr;
	typedef std::vector<ptr> vec;
public:
	Brick(Context* context, BrickLayout* layout);
	~Brick();

	void spawn();
	void update();

private:
	GraphicsService* m_graphicsService;
	PhysicsObject* m_physics;
	GraphicsSprite* m_sprite;
	BrickLayout m_layout;
};

} /* namespace hsg */
#endif /* HSG_BRICK_H_ */
