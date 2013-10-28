#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glut.h>

#include <algorithm>
#include <boost/mem_fn.hpp>

#include "GraphicsService.h"
#include "Log.h"
#include "Resource.h"
#include "Math/Rect.h"
#include "CoordSystem.h"
#include "PngLoader.h"

namespace hsg {

    GraphicsService::GraphicsService() :
	m_Textures(),
	m_Sprites(){
    }

    GraphicsService::~GraphicsService() {
    }

    status GraphicsService::start() {
	// Displays information about OpenGL.
	Log::info("Starting GraphicsService");
	Log::info("Version  : %s", glGetString(GL_VERSION));
	Log::info("Vendor   : %s", glGetString(GL_VENDOR));
	Log::info("Renderer : %s", glGetString(GL_RENDERER));

	if (loadResources() != STATUS_OK) goto ERROR;
	setup();
	return STATUS_OK;

    ERROR:
	Log::error("Error while starting GraphicsService");
	stop();
	return STATUS_KO;
    }

    void GraphicsService::stop() {
	Log::info("Stopping GraphicsService.");
	unloadResources();
    }

    status GraphicsService::loadResources() {
	// Loads all requested textures.

	PngLoader imgLoader;
	for (GraphicsTexture::vec_it it = m_Textures.begin(); it != m_Textures.end(); ++it) {
	    if ((*it)->load(&imgLoader) != STATUS_OK) {
		return STATUS_KO;
	    }
	}

	return STATUS_OK;
    }

    status GraphicsService::unloadResources() {
	for (GraphicsTexture::vec_it it = m_Textures.begin(); it != m_Textures.end(); ++it) {
	    (*it)->unload();
	}

	return STATUS_OK;
    }

    void GraphicsService::setup() {
	// Initializes base GL state.
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	// In a simple 2D game, we have control over the third
	// dimension. So we do not really need a Z-buffer.
	glDisable(GL_DEPTH_TEST);

	glShadeModel (GL_FLAT);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glClearColor (0.0, 0.0, 0.0, 0.0);
    }

    void GraphicsService::unregisterSprite(GraphicsSprite* pSprite) {
	GraphicsSprite::mm_it it = m_Sprites.begin();
	while(it != m_Sprites.end()){
	    const GraphicsSprite::ptr& pSpr = (*it).second;
	    if(pSpr.get() == pSprite)
		break;

	    ++it;
	}

	if(it != m_Sprites.end())
	    m_Sprites.erase(it);
    }

    void GraphicsService::onCoordsUpdate(CoordSystem* pCoords){
	Rect viewPort = pCoords->getViewPort();
	glViewport (0, 0, (GLsizei) viewPort.height, (GLsizei) viewPort.width);

	Log::info("Viewport : %d x %d", viewPort.width, viewPort.height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(pCoords->left(), pCoords->right(),
		pCoords->bottom(), pCoords->top(),
		-1.0, 2.0);
	glMatrixMode( GL_MODELVIEW);
	glLoadIdentity();
    }

    status GraphicsService::update() {
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for(GraphicsSprite::mm_it it = m_Sprites.begin(); it != m_Sprites.end(); ++it)
	    (*it).second->draw();

	glDisable(GL_BLEND);
	glutSwapBuffers();

	return STATUS_OK;
    }

    GraphicsTexture* GraphicsService::registerTexture(
	const char* sName) {
	// Finds out if texture already loaded.
	GraphicsTexture::vec_it it = std::find_if(m_Textures.begin(), m_Textures.end(),
						  std::bind2nd(TextureNameEqual(), sName));
	if(it != m_Textures.end())
	    return it->get();

	// Appends a new texture to the texture array.
	GraphicsTexture::ptr lTexture(new GraphicsTexture(sName));
	m_Textures.push_back(lTexture);

	return lTexture.get();
    }

    GraphicsTexture* GraphicsService::registerTexture(const char* sName,
						      const Size_i& desiredSize) {

	// Finds out if texture already loaded.
	GraphicsTexture::vec_it it = std::find_if(m_Textures.begin(), m_Textures.end(),
						  std::bind2nd(TextureNameEqual(), sName));
	if(it != m_Textures.end())
	    return it->get();

	// Appends a new texture to the texture array.
	GraphicsTexture::ptr lTexture(new GraphicsTexture(sName, desiredSize));
	m_Textures.push_back(lTexture);

	return lTexture.get();
    }

    GraphicsSprite* GraphicsService::registerSprite(const char* sName, int nLayer){
	GraphicsTexture* pTxt = registerTexture(sName);

	GraphicsSprite::ptr lSprite(new GraphicsSprite(pTxt));
	m_Sprites.insert(GraphicsSprite::mm_pair(nLayer, lSprite));

	return lSprite.get();
    }

    bool GraphicsService::isTextureExisted(const char* sName) {
	return std::find_if(m_Textures.begin(), m_Textures.end(), std::bind2nd(TextureNameEqual(), sName))
	    != m_Textures.end();
    }

    void GraphicsService::onEvent(const Event::ptr& event){
	switch(event->getType()){
	case EventType::SYSTEM_VIDEO_INIT:
	    start();
	    break;
	}
    }
}
