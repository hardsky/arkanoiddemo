#include "Ball.h"
#include "PhysicsService.h"
#include "GraphicsService.h"

namespace hsg {

    Ball::Ball(Context* context, BallLayout* layout):
	m_graphics(context->graphicsService){

	m_sprite=m_graphics->registerSprite(
	    m_graphics->registerTexture(layout->fileName.c_str()),
	    layout->diameter, layout->diameter, layout->center);

	m_layout = *layout;
        // Box2D requires half dimension (from center to borders).
        m_shapeDef.m_p = b2Vec2_zero;
        m_shapeDef.m_radius = layout->diameter / 2.0f;

        m_physics = context->physicsService->registerEntity(&m_shapeDef,
	    0X1, 0x2, 1.0f);

    }

    Ball::~Ball() {
	m_graphics->unregisterSprite(m_sprite);
    }

    void Ball::spawn(){
	m_physics->initialize(m_layout.center.x, m_layout.center.y, 0.0f, 0.0f);
	m_sprite->setLocation(m_layout.center);
    }

    void Ball::update(){
	m_sprite->setLocation(m_physics->m_location);
    }

} /* namespace hsg */
