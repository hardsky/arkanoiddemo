#include "Brick.h"

namespace hsg {

    Brick::Brick(Context* context, BrickLayout* layout):
	m_graphicsService(context->graphicsService){

        m_physics = context->m_physicsService->registerEntity(
	    0X1, 0x2, layout->width, layout->height, 1.0f);

	m_sprite=m_graphicsService->registerSprite(
	    m_graphicsService->registerTexture(layout->fileName.c_str()),
	    layout->width, layout->height, &m_physics->m_location);

	m_layout = *layout;
    }

    void Brick::spawn(){
	m_physics->initialize(m_layout.center.x, m_layout.center.y, 0.0f, 0.0f);
    }

    void Brick::update(){
    }

    Brick::~Brick() {
	m_graphicsService->unregisterSprite(m_sprite);
    }
    
    bool Birck::collided(){
	return m_physics.m_collide;
    }

} /* namespace hsg */
