#include "Arkanoid.h"

namespace hsg {

    Arkanoid::Arkanoid(Context* context, Gamelayout* layout):
	m_timeService(context->timeService),
	m_physicsService(context->physicsService),
	m_appQueue(context->appQueue),
	m_gameQueue(context->gameQueue){

	m_background.reset(new Background(context, &layout->background));
	m_ball.reset(new Ball(context, &layout->ball));
	m_bat.reset(new Bat(context, &layout->bat));
	m_wall.reset(new Wall(context, &layout->wall));
    }

    Arkanoid::~Arkanoid() {
	// TODO Auto-generated destructor stub
    }
    Arkanoid::update() {
        m_timeService->update();


	m_ball->update();
	m_bat->update();
	m_wall->update();

	m_appQueue.postEvent(EventType::SYSTEM_VIDEO_UPDATE);
	m_physicsService->update();
    }

    Arkanoid::activate() {	
	m_physicsService->start();
	m_timeService->start();

	m_ball->spawn();
	m_bat->spawn();
	m_wall->spawn();
    }

    Arkanoid::deactivate() {
	m_timeService->stop();
	m_physicsService->stop();
    }

} /* namespace hsg */
