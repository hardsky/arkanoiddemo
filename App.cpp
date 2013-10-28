#include "App.h"
#include "EventType.h"
#include <GL/glut.h>

namespace hsg {

    App::App(): m_eventLoop(&m_appQueue, &m_gameQueue) {
	
	m_appQueue.subscribe(EventType::SYSTEM_VIDEO_INIT, &m_graphicsService);
	m_appQueue.subscribe(EventType::SYSTEM_VIDEO_UPDATE, this);

	m_coordSystem.registerListener(&m_graphics);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(480, 640);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);

	App::_instance = this;
    }

    App::~App() {
    }


    void App::OnEvent(const Event::ptr& event){
	switch(event->getType()){
	case EventType::SYSTEM_VIDEO_UPDATE:
	    glutPostRedisplay();
	    break;
	}

    }

    void App::run(){

	glutDisplayFunc(draw_callback);
	glutReshapeFunc(resize_callback);
	glutMouseFunc(mouse_callback);
	glutIdleFunc(idle_callback);

	m_gameThread = boost::thread(boost::ref(m_eventLoop));
	glutMainLoop();
	m_gameQueue.postEvent(Event::ptr(new Event(EventType::SYSTEM_EXIT)));
	m_gameThread.join();
    }

    void App::draw(){
	m_pGraphicsService->update();
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
	m_appQueue.update();
    }

    void App::specialKeyPress(int key, int x, int y){
	if(key == GLUT_KEY_LEFT){
	    m_gameQueue.postEvent(Event::ptr(new Event(EventType::SYSTEM_KEY_LEFT_DOWN)));
	}
	else if(key == GLUT_KEY_RIGHT){
	    m_gameQueue.postEvent(Event::ptr(new Event(EventType::SYSTEM_KEY_RIGHT_DOWN)));
	}
    }

    void App::specialKeyUp(int key, int x, int y){
	if(key == GLUT_KEY_LEFT){
	    m_gameQueue.postEvent(Event::ptr(new Event(EventType::SYSTEM_KEY_LEFT_UP)));
	}
	else if(key == GLUT_KEY_RIGHT){
	    m_gameQueue.postEvent(Event::ptr(new Event(EventType::SYSTEM_KEY_RIGHT_UP)));
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
} /* namespace hsg */
