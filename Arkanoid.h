#ifndef HSG_ARKANOID_H_
#define HSG_ARKANOID_H_

#include "Context.h"
#include "TimeService.h"
#include "PhysicsService.h"

#include "Background.h"
#include "Bat.h"
#include "Ball.h"
#include "Wall.h"

#include <boost/scoped_ptr.hpp>
#include <vector>

namespace hsg {

    class GameLayout;

    class Arkanoid: public Screen {
    public:
	Arkanoid(Context* context, GameLayout* layout);
	~Arkanoid();
	
	void update();
	void activate();
	void deactivate();
    private:
	TimeService* m_timeService;
	PhysicsService* m_physicsService;
	EventDispatcher* m_appQueue;
	EventDispatcher* m_gameQueue;
	
	boost::scoped_ptr<Background> m_background;
	boost::scoped_ptr<Bat> m_bat;
	boost::scoped_ptr<Ball> m_ball;
	boost::scoped_ptr<Wall> m_wall;
    };

} /* namespace hsg */
#endif /* HSG_ARKANOID_H_ */
