#ifndef HSG_SCREENMASTER_H_
#define HSG_SCREENMASTER_H_

namespace hsg {

    class ScreenMaster {
    public:
	ScreenMaster(EventDispatcher* eventDispatcher);
	~ScreenMaster();
	
	void update();

	void startScreen();
	void gameScreen();
	    
    private:
	Screen::ptr m_pActiveScreen;
	InputService m_inputService;
    };

} /* namespace hsg */
#endif /* HSG_SCREENMASTER_H_ */
