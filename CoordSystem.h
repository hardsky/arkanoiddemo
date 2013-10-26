#ifndef HSG_COORDSYSTEM_H_
#define HSG_COORDSYSTEM_H_

#include "Interfaces/ICoordListener.h"
#include "Math/Vector3.h"
#include "Math/Rect.h"
#include "Types.h"

#include <vector>

using namespace gameplay;

namespace hsg {

class CoordSystem {
public:
	CoordSystem();
	virtual ~CoordSystem();

	Vector3 toGameCoords(int x, int y);
	Size_i toScreenSize(float fWidth, float fHeight);
	void registerListerner(ICoordListener* pListener);
	void update(int nScreenWidth, int nScreenHeight);

	float left(){return m_fLeft;}
	float right(){return m_fRight;}
	float top(){return m_fTop;}
	float bottom(){return m_fBottom;}
	const Vector3& center()const{return m_Center;}
	void operator()(ICoordListener* pListener);
	Rect getViewPort();

	void setCenter(const Vector3& coords);
	void setEdges(float fLeft, float fRight, float fBottom, float fTop);

private:
	std::vector<ICoordListener*> m_Listeners;
	Size_i m_ScreenSz;
	float m_fLeft;
	float m_fRight;
	float m_fTop;
	float m_fBottom;
	Vector3 m_Center;
	Size_f m_ViewSz;
	Size_f m_ViewFactor;//ViewCoordinates = m_ViewFactor * ScreenCoordinates;
	Size_f m_ScreenFactor;//ScreenCoordinates = m_ScreenFactor * ViewCoordinates;
};

} /* namespace hsg */
#endif /* HSG_COORDSYSTEM_H_ */
