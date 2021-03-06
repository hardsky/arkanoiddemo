#ifndef HSG_BAT_H_
#define HSG_BAT_H_

#include "Context.h"
#include "GameLayout.h"
#include "IEventListener.h"
#include "PhysicsObject.h"

namespace hsg {

    class GraphicsSprite;
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
	PhysicsObject::ptr m_physics;
	GraphicsSprite* m_sprite;
	BatLayout m_layout;
	EventDispatcher* m_gameQueue;
	b2PolygonShape m_shapeDef;
    };

} /* namespace hsg */
#endif /* HSG_BAT_H_ */
