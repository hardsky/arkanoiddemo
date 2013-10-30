#include "PhysicsService.h"
#include "TimeService.h"
#include "Log.h"

namespace hsg {

    PhysicsService::PhysicsService(TimeService* pTimeService) :
	mTimeService(pTimeService),
	mColliders(), mWorld(b2Vec2_zero) {
        mWorld.SetContactListener(this);
    }

    PhysicsObject::ptr PhysicsService::registerEntity(b2Shape* shapeDef, b2BodyType bodyType, uint16 pCategory, uint16 pMask, float pRestitution) {

        PhysicsObject::ptr lCollider(new PhysicsObject(shapeDef, bodyType, pCategory, pMask, pRestitution, &mWorld));
        mColliders.push_back(lCollider);
        return mColliders.back();
    }
    PhysicsObject::ptr PhysicsService::registerStaticEntity(b2Shape* shapeDef) {

        PhysicsObject::ptr lCollider(new PhysicsObject(shapeDef, b2_staticBody, &mWorld));
        mColliders.push_back(lCollider);
        return mColliders.back();
    }
    PhysicsObject::ptr PhysicsService::registerKinematicEntity(b2Shape* shapeDef) {

        PhysicsObject::ptr lCollider(new PhysicsObject(shapeDef, b2_kinematicBody, &mWorld));
        mColliders.push_back(lCollider);
        return mColliders.back();
    }
    PhysicsObject::ptr PhysicsService::registerDynamicEntity(b2Shape* shapeDef, float pRestitution, float density) {

        PhysicsObject::ptr lCollider(new PhysicsObject(shapeDef, b2_dynamicBody, pRestitution, &mWorld, density));
        mColliders.push_back(lCollider);
        return mColliders.back();
    }

    void PhysicsService::unregisterEntity(const PhysicsObject::ptr& physicsObject){
	mColliders.erase(std::remove(mColliders.begin(), mColliders.end(), physicsObject), mColliders.end());
    }

    status PhysicsService::update() {
        // Clears collision flags.
        PhysicsObject::vec_it iCollider = mColliders.begin();
        for (; iCollider < mColliders.end() ; ++iCollider) {
            (*iCollider)->m_collide = false;
        }

        // Updates simulation.
        float lTimeStep = mTimeService->elapsed();
        mWorld.Step(lTimeStep, VELOCITY_ITER, POSITION_ITER);

        // Caches the new state.
        iCollider = mColliders.begin();
        for (; iCollider < mColliders.end() ; ++iCollider) {
            (*iCollider)->update();
        }
        return STATUS_OK;
    }

    void PhysicsService::BeginContact(b2Contact* pContact) {
        void* lUserDataA = pContact->GetFixtureA()->GetUserData();
        if (lUserDataA != NULL) {
            ((PhysicsObject*)(lUserDataA))->m_collide = true;
        }
        void* lUserDataB = pContact->GetFixtureB()->GetUserData();
        if (lUserDataB != NULL) {
            ((PhysicsObject*)(lUserDataB))->m_collide = true;
        }
    }
}
