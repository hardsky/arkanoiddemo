#ifndef HSG_SCREENMASTER_H_
#define HSG_SCREENMASTER_H_

#include "Context.h"

namespace hsg {

    class ScreenMaster {
    public:
	ScreenMaster(Context* context);
	~ScreenMaster();
	
	void update();

	void startScreen();
	void gameScreen();
	    
    private:
	Context* m_context;
	Screen::ptr m_activeScreen;
	InputService m_inputService;
    };

} /* namespace hsg */
#endif /* HSG_SCREENMASTER_H_ */
