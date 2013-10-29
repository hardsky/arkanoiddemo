#include "StartScreen.h"
#include "GraphicsService.h"
#include "EventClick.h"
#include "EventDispatcher.h"
#include "Log.h"

namespace hsg {

    using namespace gameplay;

    StartScreen::StartScreen(Context* context):
	m_appQueue(context->appQueue),
	m_gameQueue(context->gameQueue),
	m_layout(context->coordSystem),
	m_graphics(context->graphicsService),
	m_coordSystem(context->coordSystem),
	m_background(context, &m_layout.background),
	m_buttonSprite(m_graphics->registerSprite(m_graphics->registerTexture(m_layout.button.fileName.c_str()),
						  m_layout.button.width, m_layout.button.height,
						  m_layout.button.center)){

	m_gameQueue->subscribe(SYSTEM_MOUSE_CLICK, this);
    }

    StartScreen::~StartScreen(){
	m_gameQueue->unsubscribe(SYSTEM_MOUSE_CLICK, this);
	m_graphics->unregisterSprite(m_buttonSprite);
    }

    void StartScreen::update(){
    }

    void StartScreen::activate(){
	m_appQueue->postEvent(Event::ptr(new Event(SYSTEM_VIDEO_UPDATE)));
    }

    void StartScreen::deactivate(){
    }
    
    void StartScreen::onEvent(const Event::ptr& event){
	HSG_DEBUG("StartScreen::onEvent");
	switch(event->getEventType()){
	case SYSTEM_MOUSE_CLICK:
	{
	    EventClick* clickEvent = (EventClick*)event.get();

	    Vector3 gameCoords = m_coordSystem->toGameCoords(clickEvent->x, clickEvent->y);
	    float left = m_buttonSprite->getLocation().x - m_buttonSprite->getWidth() / 2;
	    float right = m_buttonSprite->getLocation().x  + m_buttonSprite->getWidth() / 2;
	    float top = m_buttonSprite->getLocation().y  + m_buttonSprite->getHeight() / 2;
	    float bottom = m_buttonSprite->getLocation().y  - m_buttonSprite->getHeight() / 2;

	    if(gameCoords.x > left && gameCoords.x < right
	       && gameCoords.y < top && gameCoords.y > bottom){

		m_gameQueue->postEvent(Event::ptr(new Event(GAME_START)));
	    }
	}
	break;
	}
    }
}
