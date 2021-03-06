#include "Bat.h"
#include "PhysicsService.h"
#include "GraphicsService.h"
#include "EventDispatcher.h"
#include "Log.h"

namespace hsg {

    Bat::Bat(Context* context, BatLayout* layout):
	VELOCITY_X(3),
	m_graphicsService(context->graphicsService),
	m_gameQueue(context->gameQueue){


	m_sprite=m_graphicsService->registerSprite(
	    m_graphicsService->registerTexture(layout->fileName.c_str()),
	    layout->width, layout->height, layout->center);

	m_layout = *layout;
	m_shapeDef.SetAsBox(layout->width/2, layout->height/2);
	
        m_physics = context->physicsService->registerDynamicEntity(&m_shapeDef, 0.0f);
	
	m_gameQueue->subscribe(SYSTEM_KEY_LEFT_DOWN, this);
	m_gameQueue->subscribe(SYSTEM_KEY_RIGHT_DOWN, this);
	m_gameQueue->subscribe(SYSTEM_KEY_LEFT_UP, this);
	m_gameQueue->subscribe(SYSTEM_KEY_RIGHT_UP, this);
    }

    void Bat::spawn(){
	m_physics->initialize(m_layout.center.x, m_layout.center.y, 0.0f, 0.0f);
	m_sprite->setLocation(m_layout.center);
    }

    void Bat::update(){
	if(m_physics->m_collide){
	    HSG_DEBUG("Bat collide");
	}
	m_sprite->setLocation(m_physics->m_location);
    }

    void Bat::onEvent(const Event::ptr& event){
	switch(event->getEventType()){
	case SYSTEM_KEY_LEFT_DOWN:
	{
	    m_physics->setVelocity(-1 * VELOCITY_X, 0.0f);
	}
	break;
	case SYSTEM_KEY_RIGHT_DOWN:
	{
	    m_physics->setVelocity(VELOCITY_X, 0.0f);
	}
	break;
	case SYSTEM_KEY_LEFT_UP:
	{
	    m_physics->setVelocity(0.0f, 0.0f);
	}
	break;
	case SYSTEM_KEY_RIGHT_UP:
	{
	    m_physics->setVelocity(0.0f, 0.0f);
	}
	break;
	}
    }

    Bat::~Bat() {
	m_graphicsService->unregisterSprite(m_sprite);

	m_gameQueue->unsubscribe(SYSTEM_KEY_LEFT_DOWN, this);
	m_gameQueue->unsubscribe(SYSTEM_KEY_RIGHT_DOWN, this);
	m_gameQueue->unsubscribe(SYSTEM_KEY_LEFT_UP, this);
	m_gameQueue->unsubscribe(SYSTEM_KEY_RIGHT_UP, this);
    }

} /* namespace hsg */
