#ifndef _HSG_GRAPHICSTEXTURE_H_
#define _HSG_GRAPHICSTEXTURE_H_

#include "IImageLoader.h"
#include "Types.h"

#include <GL/gl.h>
#include <libpng/png.h>
#include <boost/shared_ptr.hpp>
#include <vector>

namespace hsg {
    class GraphicsTexture {
    public:
        typedef boost::shared_ptr<GraphicsTexture> ptr;
        typedef std::vector<ptr> vec;
        typedef vec::iterator vec_it;

    public:
        GraphicsTexture(const char* sName);
        GraphicsTexture(const char* sName, const Size_i& desiredSize);

        const char* getName();
        int32_t getHeight();
        int32_t getWidth();

        status load(IImageLoader* pImgLoader);
        void unload();
        void apply();

    protected:
        uint8_t* loadImage();

    private:
        static void callback_read(png_structp pStruct,
            png_bytep pData, png_size_t pSize);

    private:
        GLuint mTextureId;
        int32_t mWidth, mHeight;
        GLint mFormat;
        const char* m_sName;
        Size_i m_desiredSize;
    };

    struct TextureNameEqual : public std::binary_function<GraphicsTexture::ptr, const char*, bool> {
      bool operator() (GraphicsTexture::ptr& tex, const char* sName)const {return strcmp(sName, tex->getName()) == 0;}
    };
}
#endif
