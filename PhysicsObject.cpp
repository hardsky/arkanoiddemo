#include "PhysicsObject.h"
#include "Log.h"

namespace hsg {

    PhysicsObject::PhysicsObject(b2Shape* shapeDef, uint16 pCategory, uint16 pMask, float pRestitution, b2World* pWorld):
      m_location(), m_collide(false), m_world(pWorld),
      m_bodyDef(), m_bodyObj(NULL), m_fixtureDef() {

        m_bodyDef.type = b2_dynamicBody;
        m_bodyDef.userData = this;
        m_bodyDef.awake = true;
        m_bodyDef.fixedRotation = true;

        m_fixtureDef.shape = shapeDef;
        m_fixtureDef.density = 1.0f;
        m_fixtureDef.friction = 0.0f;
        m_fixtureDef.restitution = pRestitution;
        m_fixtureDef.filter.categoryBits = pCategory;
        m_fixtureDef.filter.maskBits = pMask;
        m_fixtureDef.userData = this;

        m_bodyObj = m_world->CreateBody(&m_bodyDef);
        m_bodyObj->CreateFixture(&m_fixtureDef);
        m_bodyObj->SetUserData(this);
    }

    void PhysicsObject::initialize(float pX, float pY,
        float pVelocityX, float pVelocityY) {
        m_location.set(pX, pY, 0);
        b2Vec2 lPosition(pX, pY);
        m_bodyObj->SetTransform(lPosition, 0.0f);
        m_bodyObj->SetLinearVelocity(b2Vec2(pVelocityX, pVelocityY));
    }

    void PhysicsObject::setVelocity(float velocityX, float velocityY){
        m_bodyObj->SetLinearVelocity(b2Vec2(velocityX, velocityY));
    }

    void PhysicsObject::update() {
        m_location.set(m_bodyObj->GetPosition().x,
            m_bodyObj->GetPosition().y, 0);
    }

} /* namespace hsg */
