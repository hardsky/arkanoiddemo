#ifndef HSG_PHYSICSSERVICE_H_
#define HSG_PHYSICSSERVICE_H_

#include <Box2D.h>

namespace hsg {

class PhysicsService: private b2ContactListener {
public:
public:
    PhysicsService(TimeService* pTimeService);

    PhysicsObject::ptr registerEntity(uint16 pCategory,
        uint16 pMask, int32_t pDiameter, float pRestitution);
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
