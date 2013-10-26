#include "Arkanoid.h"

namespace hsg {

    Arkanoid::Arkanoid(EventDispatcher* eventDispatcher, GameLayout* layout):
	m_eventDispatcher(eventDispatcher),
	m_physicsService(&m_timeService),
	m_background(&layout->background),
	m_ball(&layout->ball),
	m_bat(&layout->bat),
	m_wall(&layout->wall){
    }

    Arkanoid::~Arkanoid() {
	// TODO Auto-generated destructor stub
    }
    Arkanoid::update() {
        mTimeService->update();


	m_ball.update();
	m_bat.update();
	m_wall.update();

	m_eventDispatcher.postVideoUpdate();
	mInputService->update();
	mPhysicsService->update();
    }
    Arkanoid::activate() {
	Level lvl;
	loadLevel(&lvl);
	m_background.init(lvl.background);
	m_ball.init(lvl.ball);
	m_bat.init(lvl.bat);
	m_wall.init(lvl.wall);
    }
    Arkanoid::deactivate() {

    }

    Arkanoid::loadLevel(Level* lvl) {

    }

} /* namespace hsg */
