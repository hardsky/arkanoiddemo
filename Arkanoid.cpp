#include "Arkanoid.h"
#include "GameLayout.h"
#include "TimeService.h"
#include "PhysicsService.h"
#include "EventDispatcher.h"

namespace hsg {

    Arkanoid::Arkanoid(Context* context, GameLayout* layout):
	m_timeService(context->timeService),
	m_physicsService(context->physicsService),
	m_appQueue(context->appQueue),
	m_gameQueue(context->gameQueue){

	m_background.reset(new Background(context, &layout->background));
	m_ball.reset(new Ball(context, &layout->ball));
	m_bat.reset(new Bat(context, &layout->bat));
	m_wall.reset(new Wall(context, &layout->wall));
	m_edges.reset(new Edges(context));
    }

    Arkanoid::~Arkanoid() {
	// TODO Auto-generated destructor stub
    }
    void Arkanoid::update() {
        m_timeService->update();


	m_ball->update();
	m_bat->update();
	m_wall->update();
	m_edges->update();

	m_appQueue->postEvent(Event::ptr(new Event(SYSTEM_VIDEO_UPDATE)));
	m_physicsService->update();
    }

    void Arkanoid::activate() {	
	//m_physicsService->start();
	//m_timeService->start();

	m_ball->spawn();
	m_bat->spawn();
	m_wall->spawn();
	m_edges->spawn();
    }

    void Arkanoid::deactivate() {
	//m_timeService->stop();
	//m_physicsService->stop();
    }

} /* namespace hsg */
