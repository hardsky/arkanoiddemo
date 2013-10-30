#include "Edges.h"
#include "CoordSystem.h"
#include "PhysicsService.h"

namespace hsg {
    Edges::Edges(Context* context){
	b2Vec2 vs[4];
	vs[3].Set(context->coordSystem->left(), context->coordSystem->bottom());
	vs[2].Set(context->coordSystem->left(), context->coordSystem->top());
	vs[1].Set(context->coordSystem->right(), context->coordSystem->top());
	vs[0].Set(context->coordSystem->right(), context->coordSystem->bottom());
	
	m_shapeDef.CreateLoop(vs, 4);

        m_physics = context->physicsService->registerStaticEntity(&m_shapeDef);
    }

    Edges::~Edges(){
    }
	
    void Edges::spawn(){
    }

    void Edges::update(){
    }
}
