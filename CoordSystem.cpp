#include "CoordSystem.h"

#include <algorithm>
#include <functional>

namespace hsg {

    using namespace gameplay;

    CoordSystem::CoordSystem():
	m_Listeners(0),
	m_ScreenSz(),
	m_fLeft(0.0f),
	m_fRight(0.0f),
	m_fTop(0.0f),
	m_fBottom(0.0f),
	m_ViewSz(0.0f, 0.0f),
	m_ViewFactor(),
	m_ScreenFactor(),
	m_Center(0.0f, 0.0f, 0.0f){
    }

    CoordSystem::~CoordSystem() {
    }

    Vector3 CoordSystem::toGameCoords(int x, int y) {
	float fX = (float)x;
	fX = fX - m_ScreenSz.Width / 2.0f;
	float fY = (float)(m_ScreenSz.Height - y);
	fY = fY - m_ScreenSz.Height / 2.0f;
	return Vector3(m_ViewFactor.Width * fX, m_ViewFactor.Height * fY, 0);
    }

    Size_i CoordSystem::toScreenSize(float fWidth, float fHeight) {
	return Size_i(fWidth * m_ScreenFactor.Width, fHeight * m_ScreenFactor.Height);
    }

    void CoordSystem::registerListerner(ICoordListener* pListener) {
	m_Listeners.push_back(pListener);
    }

    void CoordSystem::operator()(ICoordListener* pListener){
	pListener->onCoordsUpdate(this);
    }

    void CoordSystem::update(int nScreenWidth, int nScreenHeight) {
	m_ScreenSz.Height = nScreenHeight;
	m_ScreenSz.Width = nScreenWidth;

	m_ViewFactor.Height = m_ViewSz.Height / m_ScreenSz.Height;
	m_ViewFactor.Width = m_ViewSz.Width / m_ScreenSz.Width;

	m_ScreenFactor.Height = m_ScreenSz.Height / m_ViewSz.Height;
	m_ScreenFactor.Width = m_ScreenSz.Width / m_ViewSz.Width;

	std::for_each(m_Listeners.begin(), m_Listeners.end(), *this);
    }

    Rect CoordSystem::getViewPort(){
	Rect tmp = {0, 0, m_ScreenSz.Width, m_ScreenSz.Height};
	return tmp;
    }

    void CoordSystem::setCenter(const Vector3& coords) {
	m_Center = coords;
    }

    void CoordSystem::setEdges(float fLeft, float fRight, float fBottom,
			       float fTop) {
	m_fLeft = fLeft;
	m_fRight = fRight;
	m_fBottom = fBottom;
	m_fTop = fTop;

	m_ViewSz.Width = m_fRight - m_fLeft;
	m_ViewSz.Height = m_fTop - m_fBottom;
    }

} /* namespace hsg */
