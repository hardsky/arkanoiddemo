#include "GraphicsTexture.h"
#include "Log.h"

namespace hsg {
    GraphicsTexture::GraphicsTexture(const char* sName) :
        mTextureId(0),
        mWidth(0), mHeight(0),
        mFormat(GL_RGB),
        m_sName(sName),
        m_desiredSize(0, 0)
    {}

    GraphicsTexture::GraphicsTexture(const char* sName, const Size_i& desiredSize):
        mTextureId(0),
        mWidth(0), mHeight(0),
        mFormat(GL_RGB),
        m_sName(sName),
        m_desiredSize(desiredSize){
    }

    const char* GraphicsTexture::getName() {
        return m_sName;
    }

    int32_t GraphicsTexture::getHeight() {
        return mHeight;
    }

    int32_t GraphicsTexture::getWidth() {
        return mWidth;
    }

    status GraphicsTexture::load(IImageLoader* pImgLoader) {
    	status res = pImgLoader->load(m_sName, m_desiredSize.Width, m_desiredSize.Height);
    	if(res != STATUS_OK)
    		return res;

    	uint8_t* imgBuf = pImgLoader->getData();
    	GLint nFormat = pImgLoader->getFormat();
    	mWidth = pImgLoader->getWidth();
    	mHeight = pImgLoader->getHeight();

        // Creates a new OpenGL texture.
        GLenum lErrorResult;
        glGenTextures(1, &mTextureId);
        glBindTexture(GL_TEXTURE_2D, mTextureId);
        // Set-up texture properties.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
            GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
            GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
            GL_CLAMP_TO_EDGE);
        // Loads image data into OpenGL.
        glTexImage2D(GL_TEXTURE_2D, 0, nFormat, mWidth, mHeight, 0,
        		nFormat, GL_UNSIGNED_BYTE, imgBuf);

        delete[] imgBuf;

        if (glGetError() != GL_NO_ERROR) {
            HSG_ERROR("Error loading texture into OpenGL.");
            unload();
            return STATUS_KO;
        }

        HSG_DEBUG("Texture is loaded, width: %d, height: %d", mWidth, mHeight);

        return STATUS_OK;
    }

    void GraphicsTexture::unload() {
        if (mTextureId != 0) {
            glDeleteTextures(1, &mTextureId);
            mTextureId = 0;
        }
        mWidth = 0; mHeight = 0; mFormat = 0;
    }

    void GraphicsTexture::apply() {
        glActiveTexture( GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mTextureId);
    }
}
