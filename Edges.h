#ifndef HSG_EDGES_H_
#define HSG_EDGES_H_

#include "Context.h"
#include "PhysicsObject.h"

namespace hsg {

    class Edges {
    public:
	Edges(Context* context);
	~Edges();
	
	void spawn();
	void update();

    private:
	PhysicsObject::ptr m_physics;
	b2ChainShape m_shapeDef;
    };

} 

#endif 
