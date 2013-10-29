#include "PhysicsService.h"
#include "TimeService.h"
#include "Log.h"

namespace hsg {

    PhysicsService::PhysicsService(TimeService* pTimeService) :
	mTimeService(pTimeService),
	mColliders(), mWorld(b2Vec2_zero) {
        mWorld.SetContactListener(this);
    }

    PhysicsObject::ptr PhysicsService::registerEntity(b2Shape* shapeDef, uint16 pCategory, uint16 pMask, float pRestitution) {

        PhysicsObject::ptr lCollider(new PhysicsObject(shapeDef, pCategory, pMask, pRestitution, &mWorld));
        mColliders.push_back(lCollider);
        return mColliders.back();
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
