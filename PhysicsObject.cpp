#include "PhysicsObject.h"
#include "Log.h"

namespace hsg {

    PhysicsObject::PhysicsObject(uint16 pCategory, uint16 pMask,
      int32_t pDiameter, float pRestitution, b2World* pWorld) :
      mLocation(), mCollide(false), mWorld(pWorld),
      mBodyDef(), mBodyObj(NULL), mShapeDef(), mFixtureDef() {
        mBodyDef.type = b2_dynamicBody;
        mBodyDef.userData = this;
        mBodyDef.awake = true;
        mBodyDef.fixedRotation = true;

        // Box2D requires half dimension (from center to borders).
        mShapeDef.m_p = b2Vec2_zero;
        mShapeDef.m_radius = pDiameter / (2.0f * SCALE_FACTOR);

        mFixtureDef.shape = &mShapeDef;
        mFixtureDef.density = 1.0f;
        mFixtureDef.friction = 0.0f;
        mFixtureDef.restitution = pRestitution;
        mFixtureDef.filter.categoryBits = pCategory;
        mFixtureDef.filter.maskBits = pMask;
        mFixtureDef.userData = this;

        mBodyObj = mWorld->CreateBody(&mBodyDef);
        mBodyObj->CreateFixture(&mFixtureDef);
        mBodyObj->SetUserData(this);
    }

    PhysicsObject::PhysicsObject(uint16 pCategory, uint16 pMask,
		  int32_t width, int32_t height, float pRestitution, b2World* pWorld){
    }

    PhysicsTarget::ptr PhysicsObject::createTarget(float pFactor) {
        return PhysicsTarget::ptr(
            new PhysicsTarget(mWorld, mBodyObj, mLocation, pFactor));
    }

    void PhysicsObject::initialize(float pX, float pY,
        float pVelocityX, float pVelocityY) {
        mLocation.setPosition(pX, pY);
        b2Vec2 lPosition(pX / SCALE_FACTOR, pY / SCALE_FACTOR);
        mBodyObj->SetTransform(lPosition, 0.0f);
        mBodyObj->SetLinearVelocity(b2Vec2(pVelocityX, pVelocityY));
    }

    void PhysicsObject::setVelocity(float velocityX, float velocityY){
        mBodyObj->SetLinearVelocity(b2Vec2(velocityX, velocityY));
    }

    void PhysicsObject::update() {
        mLocation.setPosition(
            mBodyObj->GetPosition().x * SCALE_FACTOR,
            mBodyObj->GetPosition().y * SCALE_FACTOR);
    }

} /* namespace hsg */
