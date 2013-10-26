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

    ScreenMaster::ScreenMaster(Context* pContext, android_app* pApp):
	m_pContext(pContext),
	m_pApplication(pApp),
	m_loadLayout(pContext, pApp, this),
	m_pauseLayout(pContext, pApp, this),
	m_winLayout(pContext, pApp, this),
	m_overLayout(pContext, pApp, this),
	m_quitLayout(pContext, pApp, this),
	m_startLayout(pContext, pApp, this),
	m_levelLayout(pContext, pApp, this),
	m_gameLayout(pContext, pApp, this),
	//m_helpLayout(pContext, pApp, this),
	//m_scoreLayout(pContext, pApp, this),
	m_curLvlId(0),
	m_gameInfoSaved(true){

	m_gameLayout.setPauseScreenLayout(&m_pauseLayout);
	m_gameLayout.setWinScreenLayout(&m_winLayout);
	m_gameLayout.setOverScreenLayout(&m_overLayout);
	m_gameLayout.setQuitScreenLayout(&m_quitLayout);

	m_startLayout.setQuitScreenLayout(&m_quitLayout);
	m_levelLayout.setQuitScreenLayout(&m_quitLayout);
    }

    ScreenMaster::~ScreenMaster() {
    }

    void ScreenMaster::update(){
	if(m_pActiveScreen){
	    m_pActiveScreen->update();
	}
    }

    void ScreenMaster::startScreen(){
	if(m_pActiveScreen){
	    m_pActiveScreen->deactivate();
	}

	m_pActiveScreen.reset(new StartScreen());
	m_pActiveScreen->activate();
    }

    void ScreenMaster::gameScreen(){
	if(m_pActiveScreen){
	    m_pActiveScreen->deactivate();
	}
	
	GameLayout gameLayout(m_context->coordSystem);
	gameLayout.loadLevel("level.xml");
	m_pActiveScreen.reset(new GameScreen(&gameLayout));
	m_pActiveScreen->activate();
    }

} /* namespace hsg */
