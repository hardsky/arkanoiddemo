#include "GraphicsSprite.h"
#include "Log.h"

#include <GL/gl.h>
#include <GL/glext.h>

namespace hsg {
    GraphicsSprite::GraphicsSprite():
	m_Texture(0),
	m_Location(),
	m_Height(0),
	m_Width(0),
	m_isActive(true)
    {};

    GraphicsSprite::GraphicsSprite(GraphicsTexture* pImage):
	m_Texture(pImage),
	m_Location(),
	m_Height(0),
	m_Width(0),
	m_isActive(true){

    }
    GraphicsSprite::GraphicsSprite(GraphicsTexture* pTexture,
				   float Width, float Height, Vector3 Location) :
        m_Texture(pTexture), m_Location(Location),
        m_Height(Height), m_Width(Width),m_isActive(true)
    {}

    GraphicsSprite::GraphicsSprite(GraphicsTexture* pImage,
				   float x, float y, float height, float width):
        m_Texture(pImage),
	m_Location(x, y, 0),
	m_Height(height),
	m_Width(width),
	m_isActive(true)
    {}

    void GraphicsSprite::draw() {
    	if(!m_isActive || !m_Texture)
	    return;

        m_Texture->apply();

        float left = m_Location.x - m_Width/2;
        float top = m_Location.y + m_Height/2;
        float right = m_Location.x + m_Width/2;
        float bottom = m_Location.y - m_Height/2;

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        GLfloat textur[] = {
	    0.0f, 1.0f,
	    0.0f, 0.0f,
	    1.0f, 0.0f,
	    1.0f, 1.0f
        };
        GLfloat vertex[] = {
	    left, top,
	    left, bottom,
	    right, bottom,
	    right, top,
        };

        glTexCoordPointer(2,GL_FLOAT, 0, textur);
        glVertexPointer(2,GL_FLOAT, 0, vertex);

        glDrawArrays(GL_POLYGON, 0, 4);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }

    void GraphicsSprite::setActive(bool bActive) {
	m_isActive = bActive;
    }

    bool GraphicsSprite::isActive() const {
	return m_isActive;
    }

    const Vector3& GraphicsSprite::getLocation() const {
	return m_Location;
    }

    float GraphicsSprite::getWidth() const {
	return m_Width;
    }

    void GraphicsSprite::setWidth(float fWidth) {
	m_Width = fWidth;
    }

    float GraphicsSprite::getHeight() const {
	return m_Height;
    }

    void GraphicsSprite::setHeight(float fHeight) {
	m_Height = fHeight;
    }

}
