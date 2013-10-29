#ifndef HSG_PHYSICSOBJECT_H_
#define HSG_PHYSICSOBJECT_H_

#include "Vector3.h"
#include <Box2D.h>
#include <boost/shared_ptr.hpp>
#include <vector>

namespace hsg {

class PhysicsObject {
public:
    typedef boost::shared_ptr<PhysicsObject> ptr;
    typedef std::vector<ptr> vec;
    typedef vec::iterator vec_it;

public:
    PhysicsObject(b2Shape* shapeDef, uint16 pCategory, uint16 pMask, float pRestitution, b2World* pWorld);

    void initialize(float pX, float pY,
        float pVelocityX, float pVelocityY);
    void update();
    void setVelocity(float velocityX, float velocityY);

    bool m_collide;
    gameplay::Vector3 m_location;

private:
    b2World* m_world;
    b2BodyDef m_bodyDef;
    b2Body* m_bodyObj;
    b2FixtureDef m_fixtureDef;
};

} /* namespace hsg */
#endif /* HSG_PHYSICSOBJECT_H_ */
