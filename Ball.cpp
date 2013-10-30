#include "Ball.h"
#include "PhysicsService.h"
#include "GraphicsService.h"
#include "EventDispatcher.h"
#include "Log.h"

namespace hsg {

    Ball::Ball(Context* context, BallLayout* layout):
	m_graphics(context->graphicsService),
	m_physicsService(context->physicsService),
	m_gameQueue(context->gameQueue),
	m_worldEdge(context->coordSystem->bottom() - layout->diameter / 2){

	m_sprite=m_graphics->registerSprite(
	    m_graphics->registerTexture(layout->fileName.c_str()),
	    layout->diameter, layout->diameter, layout->center);

	m_layout = *layout;
        m_shapeDef.m_p = b2Vec2_zero;
        m_shapeDef.m_radius = layout->diameter / 2.0f;

	m_physics = m_physicsService->registerDynamicEntity(&m_shapeDef, 1.0f);

	m_gameQueue->subscribe(GAME_LVL_START, this);
    }

    Ball::~Ball() {
	m_gameQueue->unsubscribe(GAME_LVL_START, this);
	m_graphics->unregisterSprite(m_sprite);
	m_physicsService->unregisterEntity(m_physics);
    }

    void Ball::spawn(){
	m_physics->initialize(m_layout.center.x, m_layout.center.y, 0.0f, 0.0f);
	m_sprite->setLocation(m_layout.center);
    }

    void Ball::update(){
	if(m_physics->m_location.y < m_worldEdge){
	    spawn();
	}
	else{
	    m_sprite->setLocation(m_physics->m_location);
	}
    }
    
    void Ball::onEvent(const Event::ptr& event){
	switch(event->getEventType()){
	case GAME_LVL_START:
	    m_physics->applyImpulse(.018f, .018f);
	    break;
	}
    }

} /* namespace hsg */
