#ifndef HSG_STARTSCREEN_H
#define HSG_STARTSCREEN_H

#include "Context.h"
#include "Screen.h"
#include "StartLayout.h"
#include "IEventListener.h"
#include "Background.h"

#include <boost/scoped_ptr.hpp>

namespace hsg {

    class GraphicsSprite;

    class StartScreen: public Screen, public IEventListener {
    public:
	StartScreen(Context* context);
	~StartScreen();

	void update();
	void activate();
	void deactivate();
	
	void onEvent(const Event::ptr& event);

    private:
	EventDispatcher* m_appQueue;
	EventDispatcher* m_gameQueue;
	StartLayout m_layout;
	GraphicsService* m_graphics;
	CoordSystem* m_coordSystem;
	GraphicsSprite* m_buttonSprite;
	
	boost::scoped_ptr<Background> m_background;
    };

}
#endif
