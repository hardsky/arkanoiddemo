#include "StartScreen.h"

namespace hsg {

    StartScreen::StartScreen(Context* context):
	m_appQueue(context->appQueue),
	m_gameQueue(context->gameQueue),
	m_layout(context->coordSystem),
	m_graphics(context->graphicsService),
	m_buttonSprite(m_graphics->registerSprite(m_graphics->registerTexture(m_layout.fileName.c_str()),
						  m_layout.button.width, m_layout.button.height,
						  m_layout.button.center)),
	m_coordSystem(context->coordSystem){

	m_background(new Background(context, &m_layout.background));	
	m_appQueue->subscribe(EventType::SYSTEM_MOUSE_CLICK, this);
    }

    StartScreen::~StartScreen(){
	m_appQueue->unsubscribe(EventType::SYSTEM_MOUSE_CLICK, this);
	m_graphics->unregisterSprite(m_buttonSprite);
    }

    void StartScreen::update(){
    }

    void StartScreen::activate(){
	m_appQueue->postEvent(EventType::SYSTEM_VIDEO_UPDATE);
    }

    void StartScreen::deactivate(){
    }
    
    void StartScreen::onEvent(const Event::ptr& event){
	switch(event->getType()){
	case Eventtype::SYSTEM_MOUSE_CLICK:
	{
	    EventClick* clickEvent = (EventClick)event.get();

	    Vector3 gameCoords = m_coordSystem->toGameCoords(clickEvent.x, clickEvent.y);
	    float left = m_buttonSprite->getLocation().x - m_buttonSprite->getWidth() / 2;
	    float right = m_buttonSprite->getLocation().x  + m_buttonSprite->getWidth() / 2;
	    float top = m_buttonSprite->getLocation().y  + m_buttonSprite->getHeight() / 2;
	    float bottom = m_buttonSprite->getLocation().y  - m_buttonSprite->getHeight() / 2;

	    if(gameCoords.x > left && gameCoords.x < right
	       && gamecoords.y < top && gameCoords.y > bottom){

		m_gameQueue->postEvent(EventType::GAME_START);
	    }
	}
	break;
	}
    }
}
