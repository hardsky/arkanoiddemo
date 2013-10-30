#include "Brick.h"
#include "PhysicsService.h"
#include "GraphicsService.h"
#include "Log.h"

namespace hsg {

    Brick::Brick(Context* context, BrickLayout& layout):
	m_graphicsService(context->graphicsService),
	m_physicsService(context->physicsService){

	m_sprite=m_graphicsService->registerSprite(
	    m_graphicsService->registerTexture(layout.fileName.c_str()),
	    layout.width, layout.height, layout.center);

	m_layout = layout;

	m_shapeDef.SetAsBox(layout.width/2, layout.height/2, b2Vec2(layout.center.x, layout.center.y), 0);
        m_physics = m_physicsService->registerStaticEntity(&m_shapeDef);

    }

    void Brick::spawn(){
    }

    void Brick::update(){
    }

    Brick::~Brick() {
	m_graphicsService->unregisterSprite(m_sprite);
        m_physicsService->unregisterEntity(m_physics);	
    }
    
    bool Brick::collided()const{
	return m_physics->m_collide;
    }

} /* namespace hsg */
