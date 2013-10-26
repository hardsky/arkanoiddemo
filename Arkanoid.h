#ifndef HSG_ARKANOID_H_
#define HSG_ARKANOID_H_

#include "TimeService.h"
#include "PhysicsService.h"

#include "GameLayout.h"
#include "Background.h"
#include "Bat.h"
#include "Ball.h"
#include "Wall.h"

#include <vector>

namespace hsg {

    class Arkanoid: public Screen {
    public:
	Arkanoid(EventDispatcher* eventDispatcher, CoordSystem* coordSystem);
	~Arkanoid();
	
	void update();
	void activate();
	void deactivate();
    private:
	TimeService m_timeService;
	PhysicsService m_physicsService;
	EventDispatcher* m_eventDispatcher;
	
	GameLayout m_layout;
	Background m_background;
	Bat m_bat;
	Ball m_ball;
	Wall m_wall;

	void loadLevel(Level* lvl);
    };

} /* namespace hsg */
#endif /* HSG_ARKANOID_H_ */
