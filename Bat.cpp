#include "Bat.h"

namespace hsg {

    Bat::Bat(Context* context, BatLayout* layout):
	m_graphicsService(context->graphicsService){

        m_physics = context->m_physicsService->registerEntity(
	    0X1, 0x2, layout->width, layout->height, 1.0f);

	m_sprite=m_graphicsService->registerSprite(
	    m_graphicsService->registerTexture("bat.png"),
	    layout->width, layout->height, &m_physics->m_location);

	m_layout = *layout;
    }

    void Bat::spawn(){
	m_physics->initialize(m_layout.center.x, m_layout.center.y, 0.0f, 0.0f);
    }

    void Bat::update(){
    }

    Bat::~Bat() {
    }

} /* namespace hsg */
