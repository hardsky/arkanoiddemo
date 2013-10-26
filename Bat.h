#ifndef HSG_BAT_H_
#define HSG_BAT_H_

#include "PhysicsObject.h"
#include "GraphicsSprite.h"

namespace hsg {

class Bat {
public:
	Bat(Context* context, BatLayout* layout);
	~Bat();

	void spawn();
	void update();

private:
	GraphicsService* m_graphicsService;
	PhysicsObject* m_physics;
	GraphicsSprite* m_sprite;
	BatLayout m_layout;
};

} /* namespace hsg */
#endif /* HSG_BAT_H_ */
