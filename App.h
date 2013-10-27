#ifndef HSG_APP_H_
#define HSG_APP_H_

#include "EventDispatcher.h"
#include "EventLoop.h"

#include <boost/thread.hpp>

namespace hsg {

    class App {
    public:
	App();
	~App();
	void run();
    private:
	CoordSystem m_coordSystem;
	GraphicsService m_graphicsService;
	EventDispatcher m_appQueue;
	EventDispatcher m_gameQueue;
	EventLoop m_eventLoop;
	boost::thread m_gameThread;

	void draw();
	void changeSize(int width, int height);
	void click(int button, int state, int x, int y);
	void update();
	void specialKeyPress(int key, int x, int y);
	void specialKeyUp(int key, int x, int y);

	static App* _instance;
	static void draw_callback();
	static void resize_callback(int width, int height);
	static void mouse_callback(int button, int state, int x, int y);
	static void idle_callback();
	static void special_key_press_callback(int key, int x, int y);
	static void special_key_up_callback(int key, int x, int y);
    };

} /* namespace hsg */
#endif /* HSG_APP_H_ */
