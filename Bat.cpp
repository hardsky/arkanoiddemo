#include "Bat.h"

namespace hsg {

    Bat::Bat(Context* context, BatLayout* layout):
	VELOCITY_X(1),
	m_graphicsService(context->graphicsService),
	m_appQueue(context->appQueue){

        m_physics = context->m_physicsService->registerEntity(
	    0X1, 0x2, layout->width, layout->height, 1.0f);

	m_sprite=m_graphicsService->registerSprite(
	    m_graphicsService->registerTexture(layout->fileName.c_str()),
	    layout->width, layout->height, &m_physics->m_location);

	m_layout = *layout;
	
	m_appQueue->subscribe(SYSTEM_KEY_LEFT_DOWN, this);
	m_appQueue->subscribe(SYSTEM_KEY_RIGHT_DOWN, this);
	m_appQueue->subscribe(SYSTEM_KEY_LEFT_UP, this);
	m_appQueue->subscribe(SYSTEM_KEY_RIGHT_UP, this);
    }

    void Bat::spawn(){
	m_physics->initialize(m_layout.center.x, m_layout.center.y, 0.0f, 0.0f);
    }

    void Bat::update(){
    }

    void onEvent(const Event::ptr& event){
	switch(event->getType()){
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

	m_appQueue->unsubscribe(SYSTEM_KEY_LEFT_DOWN, this);
	m_appQueue->unsubscribe(SYSTEM_KEY_RIGHT_DOWN, this);
	m_appQueue->unsubscribe(SYSTEM_KEY_LEFT_UP, this);
	m_appQueue->unsubscribe(SYSTEM_KEY_RIGHT_UP, this);
    }

} /* namespace hsg */
