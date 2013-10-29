#ifndef HSG_SCREENMASTER_H_
#define HSG_SCREENMASTER_H_

#include "Context.h"
#include "IEventListener.h"
#include "Screen.h"

namespace hsg {

    class ScreenMaster: public IEventListener {
    public:
	ScreenMaster(Context* context);
	~ScreenMaster();
	
	void update();
	
	void onEvent(const Event::ptr& event);
	    
    private:
	Context* m_context;
	Screen::ptr m_activeScreen;

	void startScreen();
	void gameScreen();
    };

} /* namespace hsg */
#endif /* HSG_SCREENMASTER_H_ */
