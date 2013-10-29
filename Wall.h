#ifndef HSG_WALL_H_
#define HSG_WALL_H_

#include "Context.h"
#include "GameLayout.h"
#include "Brick.h"

namespace hsg {

    class Wall {
    public:
	Wall(Context* context, WallLayout* layout);
	~Wall();

	void spawn();
	void update();

    private:
	Context* m_context;
	GraphicsService* m_graphicsService;
	PhysicsObject* m_physics;
	GraphicsSprite* m_sprite;
	WallLayout m_layout;
	Brick::vec m_bricks;
	
	Brick::ptr createBreak(BrickLayout& brickLayout);
    };

} /* namespace hsg */
#endif /* HSG_WALL_H_ */
