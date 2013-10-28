#include "ScreenMaster.h"
#include "StartScreen.h"
#include "Arkanoid.h"

namespace hsg {

    using namespace boost;

    ScreenMaster::ScreenMaster(Context* context):
	m_context(context){
    }

    ScreenMaster::~ScreenMaster() {
    }

    void ScreenMaster::update(){
	if(m_activeScreen){
	    m_activeScreen->update();
	}
    }

    void ScreenMaster::startScreen(){
	if(m_activeScreen){
	    m_activeScreen->deactivate();
	}

	m_activeScreen.reset(new StartScreen(m_context));
	m_activeScreen->activate();
    }

    void ScreenMaster::gameScreen(){
	if(m_activeScreen){
	    m_activeScreen->deactivate();
	}
	
	GameLayout gameLayout(m_context->coordSystem);
	gameLayout.loadLevel("level.xml");
	m_activeScreen.reset(new Arkanoid(m_context, &gameLayout));
	m_activeScreen->activate();
    }

} /* namespace hsg */
