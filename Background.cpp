#include "Background.h"

namespace hsg {

    Background::Background(Context* context, BackgroundLayout* layout):
	m_location(layout->center),
	m_graphics(context->graphicsService),
	m_sprite(m_graphics->registerSprite(m_graphics->registerTexture(layout->fileName.c_str()), 
					    layout->width, layout->height, m_location)){

    }

    Background::~Background() {
	m_graphics->unregisterSprite(m_sprite);
    }

} /* namespace hsg */
