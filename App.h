#ifndef HSG_APP_H_
#define HSG_APP_H_

#include "Context.h"
#include "CoordSystem.h"
#include "GraphicsService.h"
#include "TimeService.h"
#include "PhysicsService.h"

#include "EventDispatcher.h"
#include "EventLoop.h"

#include <boost/thread.hpp>
#include <boost/scoped_ptr.hpp>

namespace hsg {

    class App: public IEventListener {
    public:
	App(int argc, char* argv[]);
	~App();
	void run();
    private:
	Context m_context;
	CoordSystem m_coordSystem;
	GraphicsService m_graphicsService;
	TimeService m_timeService;
	PhysicsService m_physicsService;
	EventDispatcher m_appQueue;
	EventDispatcher m_gameQueue;
	boost::scoped_ptr<EventLoop> m_eventLoop;
	boost::thread m_gameThread;

	void draw();
	void changeSize(int width, int height);
	void click(int button, int state, int x, int y);
	void update();
	void specialKeyPress(int key, int x, int y);
	void specialKeyUp(int key, int x, int y);
	void keyPress(unsigned char key, int x, int y);

	void preloadtextures();

	void onEvent(const Event::ptr& event);

	static App* _instance;
	static void draw_callback();
	static void resize_callback(int width, int height);
	static void mouse_callback(int button, int state, int x, int y);
	static void idle_callback();
	static void special_key_press_callback(int key, int x, int y);
	static void special_key_up_callback(int key, int x, int y);
	static void key_press_callback(unsigned char key, int x, int y);
    };

} /* namespace hsg */
#endif /* HSG_APP_H_ */
