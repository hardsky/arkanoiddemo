#ifndef HSG_ICOORDLISTENER_H_
#define HSG_ICOORDLISTENER_H_

//#include "../CoordSystem.h"

namespace hsg {
class CoordSystem;

class ICoordListener{
public:
	virtual void onCoordsUpdate(CoordSystem* pCoords) = 0;
	virtual ~ICoordListener(){}
};

}  // namespace hsg


#endif /* HSG_ICOORDLISTENER_H_ */
