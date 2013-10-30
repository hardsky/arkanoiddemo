#ifndef HSG_PHYSICSSERVICE_H_
#define HSG_PHYSICSSERVICE_H_

#include "Types.h"
#include "PhysicsObject.h"
#include <Box2D.h>

namespace hsg {

    class TimeService;

    class PhysicsService: private b2ContactListener {
    public:
	PhysicsService(TimeService* pTimeService);

	PhysicsObject::ptr registerEntity(b2Shape* shapeDef, b2BodyType bodyType, uint16 pCategory, uint16 pMask, float pRestitution);
	PhysicsObject::ptr registerStaticEntity(b2Shape* shapeDef);
	PhysicsObject::ptr registerKinematicEntity(b2Shape* shapeDef);
	PhysicsObject::ptr registerDynamicEntity(b2Shape* shapeDef, float pRestitution, float density = 1.0f);

	void unregisterEntity(const PhysicsObject::ptr& physicsObject);
	status update();

    private:
	void BeginContact(b2Contact* pContact);

    private:
	TimeService* mTimeService;
	PhysicsObject::vec mColliders;
	b2World mWorld;

	static const int32_t VELOCITY_ITER = 6;
	static const int32_t POSITION_ITER = 2;
    };

} /* namespace hsg */

#endif /* HSG_PHYSICSSERVICE_H_ */
