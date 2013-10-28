#include "ScreenMaster.h"
#include "ScreenLoader.h"
#include "ResourceFactory.h"
#include "GameInfoKeeper.h"
#include "SoundService.h"
#include "SettingsKeeper.h"
#include "Screens/GameScreen.h"
#include "Log.h"

#include <boost/scoped_ptr.hpp>
#include <boost/range/algorithm/sort.hpp>
#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

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
	m_activeScreen.reset(new GameScreen(m_context, &gameLayout));
	m_activeScreen->activate();
    }

} /* namespace hsg */
