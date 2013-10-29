#ifndef HSG_PNGLOADER_H_
#define HSG_PNGLOADER_H_

#include "IImageLoader.h"

#include <libpng/png.h>
#include <GL/gl.h>

namespace hsg {

class PngLoader: public hsg::IImageLoader {
public:
	PngLoader();
	virtual ~PngLoader();

	virtual status load(const char* sPath, int32_t nDesiredWidth, int32_t nDesiredHeight);
	virtual uint8_t* getData();
	virtual GLint getFormat();
	virtual int32_t getWidth();
	virtual int32_t getHeight();


private:
    int32_t m_nWidth;
    int32_t m_nHeight;
    GLint m_nFormat;

    png_byte* m_pImgBuf;

    static void callback_read(png_structp pStruct,
	    png_bytep pData, png_size_t pSize);
};

} /* namespace hsg */
#endif /* HSG_PNGLOADER_H_ */
