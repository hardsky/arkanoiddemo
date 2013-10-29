#include "Brick.h"
#include "PhysicsService.h"
#include "GraphicsService.h"

namespace hsg {

    Brick::Brick(Context* context, BrickLayout& layout):
	m_graphicsService(context->graphicsService){

	m_sprite=m_graphicsService->registerSprite(
	    m_graphicsService->registerTexture(layout.fileName.c_str()),
	    layout.width, layout.height, layout.center);

	m_layout = layout;

	m_shapeDef.SetAsBox(layout.width, layout.height);
        m_physics = context->physicsService->registerEntity(&m_shapeDef,
	    0X1, 0x2, 0.0f);

    }

    void Brick::spawn(){
	m_physics->initialize(m_layout.center.x, m_layout.center.y, 0.0f, 0.0f);
	m_sprite->setLocation(m_physics->m_location);
    }

    void Brick::update(){
	m_sprite->setLocation(m_physics->m_location);
    }

    Brick::~Brick() {
	m_graphicsService->unregisterSprite(m_sprite);
    }
    
    bool Brick::collided()const{
	return m_physics->m_collide;
    }

} /* namespace hsg */
