#include "PhysicsService.hpp"
#include "Log.hpp"

namespace hsg {

    PhysicsService::PhysicsService(TimeService* pTimeService) :
	mTimeService(pTimeService),
	mColliders(), mWorld(b2Vec2_zero) {
        mWorld.SetContactListener(this);
    }

    PhysicsObject::ptr PhysicsService::registerEntity(
        uint16 pCategory, uint16 pMask, int32_t pDiameter,
        float pRestitution) {
        PhysicsObject::ptr lCollider(new PhysicsObject(pCategory,
						       pMask, pDiameter, pRestitution, &mWorld));
        mColliders.push_back(lCollider);
        return mColliders.back();
    }

    PhysicsObject::ptr PhysicsService::registerEntity(uint16 pCategory,
						      uint16 pMask, int32_t width, int32_t height, float pRestitution){
        PhysicsObject::ptr lCollider(new PhysicsObject(pCategory,
						       pMask, width, height, pRestitution, &mWorld));
        mColliders.push_back(lCollider);
        return mColliders.back();
    }


    status PhysicsService::update() {
        // Clears collision flags.
        PhysicsObject::vec_it iCollider = mColliders.begin();
        for (; iCollider < mColliders.end() ; ++iCollider) {
            (*iCollider)->mCollide = false;
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
            ((PhysicsObject*)(lUserDataA))->mCollide = true;
        }
        void* lUserDataB = pContact->GetFixtureB()->GetUserData();
        if (lUserDataB != NULL) {
            ((PhysicsObject*)(lUserDataB))->mCollide = true;
        }
    }
}
