#include "App.h"
#include "EventType.h"
#include "EventClick.h"
#include <GL/glut.h>

namespace hsg {

    App::App(int argc, char* argv[]):
    	m_physicsService(&m_timeService){
	
	m_appQueue.subscribe(SYSTEM_VIDEO_INIT, &m_graphicsService);
	m_appQueue.subscribe(SYSTEM_VIDEO_UPDATE, this);
	m_appQueue.subscribe(SYSTEM_EXIT, m_eventLoop.get());

	m_coordSystem.registerListener(&m_graphicsService);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(480, 640);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	
	m_context.coordService = &m_coordSystem;
	m_context.graphicsService = &m_graphicsService;
	m_context.appQueue = &m_appQueue;
	m_context.gameQueue = &m_gameQueue;
	m_context.timeService = &m_timeService;
	m_context.physicsService = &m_physicsService;

	m_eventLoop.reset(new EventLoop(&m_context));

	App::_instance = this;
    }

    App::~App() {
    }


    void App::onEvent(const Event::ptr& event){
	switch(event->getEventType()){
	case SYSTEM_VIDEO_UPDATE:
	    glutPostRedisplay();
	    break;
	}

    }

    void App::run(){

	glutDisplayFunc(draw_callback);
	glutReshapeFunc(resize_callback);
	glutMouseFunc(mouse_callback);
	glutIdleFunc(idle_callback);

	preloadtextures();

	m_gameThread = boost::thread(boost::ref(*m_eventLoop));
	glutMainLoop();
	m_gameQueue.postEvent(Event::ptr(new Event(SYSTEM_EXIT)));
	m_gameThread.join();
    }

    void App::draw(){
	m_graphicsService.update();
    }

    void App::changeSize(int width, int height){
	m_coordSystem.update(width, height);
    }

    void App::click(int button, int state, int x, int y){
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
	    m_gameQueue.postEvent(Event::ptr(new EventClick(x, y)));
	}
    }

    void App::update(){
	m_appQueue.processEvents();
    }

    void App::specialKeyPress(int key, int x, int y){
	if(key == GLUT_KEY_LEFT){
	    m_gameQueue.postEvent(Event::ptr(new Event(SYSTEM_KEY_LEFT_DOWN)));
	}
	else if(key == GLUT_KEY_RIGHT){
	    m_gameQueue.postEvent(Event::ptr(new Event(SYSTEM_KEY_RIGHT_DOWN)));
	}
    }

    void App::specialKeyUp(int key, int x, int y){
	if(key == GLUT_KEY_LEFT){
	    m_gameQueue.postEvent(Event::ptr(new Event(SYSTEM_KEY_LEFT_UP)));
	}
	else if(key == GLUT_KEY_RIGHT){
	    m_gameQueue.postEvent(Event::ptr(new Event(SYSTEM_KEY_RIGHT_UP)));
	}
    }

    void App::draw_callback(){
	App::_instance->draw();
    }

    void App::resize_callback(int width, int height){
	App::_instance->changeSize(width, height);
    }

    void App::mouse_callback(int button, int state, int x, int y){
	App::_instance->click(button, state, x, y);
    }

    void App::idle_callback(){
	App::_instance->update();
    }

    void App::special_key_press_callback(int key, int x, int y){
	App::_instance->specialKeyPress(key, x, y);
    }

    void App::special_key_up_callback(int key, int x, int y){
	App::_instance->specialKeyUp(key, x, y);
    }

    void App::preloadtextures(){
	m_graphicsService.registerTexture("ball.png");
	m_graphicsService.registerTexture("bat.png");
	m_graphicsService.registerTexture("blue.png");
	m_graphicsService.registerTexture("game_screen.png");
	m_graphicsService.registerTexture("green.png");
	m_graphicsService.registerTexture("pink.png");
	m_graphicsService.registerTexture("red.png");
	m_graphicsService.registerTexture("sea.png");
	m_graphicsService.registerTexture("start_button.png");
	m_graphicsService.registerTexture("start_screen.png");
	m_graphicsService.registerTexture("yellow.png");
    }
} /* namespace hsg */
