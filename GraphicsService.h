#ifndef _HSG_GRAPHICSSERVICE_H_
#define _HSG_GRAPHICSSERVICE_H_

#include "GraphicsSprite.h"
#include "GraphicsTexture.h"
#include "Types.h"
#include "ICoordListener.h"
#include "IEventListener.h"

namespace hsg {
    class GraphicsService: public ICoordListener, public IEventListener {
    public:
    	GraphicsService();
        ~GraphicsService();

        status start();
        void stop();
        status update();

	void onEvent(void* data);//SYSTEM_VIDEO_INIT is occured

        GraphicsTexture* registerTexture(const char* sName);
        GraphicsTexture* registerTexture(const char* sName, const Size_i& desiredSize);
        GraphicsSprite* registerSprite(const char* sName, int nLayer);
        void unregisterSprite(GraphicsSprite* pSprite);
        void onCoordsUpdate(CoordSystem* pCoords);

    protected:

        status loadResources();
        status unloadResources();
        void setup();
        void setupMatrix(int width, int height, bool scale=false);

    private:

        GraphicsTexture::vec m_Textures;
        GraphicsSprite::mm  m_Sprites; //int key - animation layer

        bool isTextureExisted(const char* sName);
    };
}
#endif
