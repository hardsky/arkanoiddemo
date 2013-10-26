#include "Ball.h"

namespace hsg {

    Ball::Ball(Context* context, BallLayout* layout):
	m_graphicsService(context->graphicsService){

        m_physics = context->m_physicsService->registerEntity(
	    0X1, 0x2, layout->diameter, 1.0f);

	m_sprite=m_graphicsService->registerSprite(
	    m_graphicsService->registerTexture("ball.png"),
	    layout->diameter, layout->diameter, &m_physics->m_location);

	m_layout = *layout;

    }

    Ball::~Ball() {
	// TODO Auto-generated destructor stub
    }

    void Ball::spawn(){
	m_physics->initialize(m_layout.center.x, m_layout.center.y, 0.0f, 0.0f);
    }

    void Ball::update(){
    }

} /* namespace hsg */
