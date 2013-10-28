#ifndef HSG_IIMAGELOADER_H_
#define HSG_IIMAGELOADER_H_

#include "Types.h"
#include <GL/gl.h>

namespace hsg {

class IImageLoader{
public:
	virtual status load(const char* sPath, int32_t nDesiredWidth, int32_t nDesiredHeight) = 0;
	virtual uint8_t* getData() = 0;
	virtual GLint getFormat() = 0;
	virtual int32_t getWidth() = 0;
	virtual int32_t getHeight() = 0;

	virtual ~IImageLoader(){}
};


}  // namespace hsg

#endif /* HSG_IIMAGELOADER_H_ */
