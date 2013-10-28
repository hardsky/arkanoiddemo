#ifndef HSG_BACKGROUND_H_
#define HSG_BACKGROUND_H_

#include "Context.h"
#include "GameLayout.h"
#include "Vector3.h"

namespace hsg {

    class GraphicsSprite;

    class Background {
    public:
	Background(Context* context, BackgroundLayout* layout);
	~Background();
    private:
	gameplay::Vector3 m_location;
	GraphicsService* m_graphics;
	GraphicsSprite* m_sprite;
	BackgroundLayout m_layout;
    };

} /* namespace hsg */

#endif /* HSG_BACKGROUND_H_ */
