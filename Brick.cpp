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
	//m_physics->initialize(m_layout.center.x, m_layout.center.y, 0.0f, 0.0f);
	//m_sprite->setLocation(m_physics->m_location);
    }

    void Brick::update(){
	if(m_physics->m_collide){
	    HSG_DEBUG("Brick collide");
	}
	//m_sprite->setLocation(m_physics->m_location);
    }

    Brick::~Brick() {
	m_graphicsService->unregisterSprite(m_sprite);
        m_physicsService->unregisterEntity(m_physics);	
    }
    
    bool Brick::collided()const{
	return m_physics->m_collide;
    }

} /* namespace hsg */
