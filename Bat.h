#ifndef HSG_BAT_H_
#define HSG_BAT_H_

#include "PhysicsObject.h"
#include "GraphicsSprite.h"

namespace hsg {

    class Bat: public IEventListener {
    public:
	Bat(Context* context, BatLayout* layout);
	~Bat();

	void spawn();
	void update();

	void onEvent(const Event::ptr& event);

    private:
	const float VELOCITY_X;

	GraphicsService* m_graphicsService;
	PhysicsObject* m_physics;
	GraphicsSprite* m_sprite;
	BatLayout m_layout;
	EventDispatcher* m_appQueue;
    };

} /* namespace hsg */
#endif /* HSG_BAT_H_ */
