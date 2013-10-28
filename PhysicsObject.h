#ifndef HSG_PHYSICSOBJECT_H_
#define HSG_PHYSICSOBJECT_H_

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
    PhysicsObject(uint16 pCategory, uint16 pMask,
        int32_t pDiameter, float pRestitution, b2World* pWorld);

    void initialize(float pX, float pY,
        float pVelocityX, float pVelocityY);
    void update();
    void setVelocity(float velocityX, float velocityY);

    bool m_collide;
    Vector3 m_location;

private:
    b2World* m_world;
    b2BodyDef m_bodyDef;
    b2Body* m_bodyObj;
    b2Shape* m_shapeDef;
    b2FixtureDef m_fixtureDef;
};

} /* namespace hsg */
#endif /* HSG_PHYSICSOBJECT_H_ */
