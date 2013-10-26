#include "App.h"
#include <GL/glut.h>

namespace hsg {

    App::App():
	m_eventLoop(&m_eventDispatcher) {
	EventLoop::_instance = this;

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (250, 250);
	glutInitWindowPosition (100, 100);
	glutCreateWindow (argv[0]);
    }

    App::~App() {
	// TODO Auto-generated destructor stub
    }

    App::~App() {
	App::_instance = 0;
    }

    void App::run(){

	glutDisplayFunc(draw_callback);
	glutReshapeFunc(resize_callback);
	glutMouseFunc(mouse_callback);
	glutIdleFunc(idle_callback);

	m_gameThread = boost::thread(boost::ref(m_eventLoop));
	glutMainLoop();
	m_evetDispatcher.postExit();
	m_gameThread.join();
    }

    void App::draw(){

	m_pGraphicsService->draw();
    }

    void App::changeSize(int width, int height){
	m_eventDispatcher.postResize(width, height);
    }

    void App::click(int button, int state, int x, int y){
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
	    m_eventDispatcher.postClick(x, y);
	}
    }

    void App::update(){
	if(m_eventDispatcher.isVideoRequsted()){
	    glutPostRedisplay();
	}
    }

    void App::specialKeyPress(int key, int x, int y){
	if(key == GLUT_KEY_LEFT){
	    m_eventDispatcher.postLeftKeyPress();
	}
	else if(key == GLUT_KEY_RIGHT){
	    m_eventDispatcher.postRightKeyPress();
	}
    }

    void App::specialKeyUp(int key, int x, int y){
	if(key == GLUT_KEY_LEFT){
	    m_eventDispatcher.postLeftKeyUp();
	}
	else if(key == GLUT_KEY_RIGHT){
	    m_eventDispatcher.postRightKeyUp();
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
