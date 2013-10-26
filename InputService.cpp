#include "InputService.h"
#include "Math/Vector3.h"
#include "Log.h"

#include <algorithm>
#include <functional>

namespace hsg {

using namespace gameplay;

InputService::InputService(CoordSystem* pCoordSystem):
	m_pCoordSystem(pCoordSystem),
	m_Listeners(){

    Log::info("Creating InputService.");

}

InputService::~InputService() {
}

status InputService::start(){
    HSG_DEBUG("Starting InputService.");

	return STATUS_OK;
}

void InputService::stop(){

}

void InputService::onClick(int x, int y) {
    HSG_DEBUG("InputService::onClick");

	Vector3 pt = m_pCoordSystem->toGameCoords(x, y);
	std::vector<IInputListener*>::iterator it = m_Listeners.begin();
	while(it != m_Listeners.end()){
		(*it)->select(&pt);
		++it;
	}
}

void InputService::addListener(IInputListener* pListener) {
	m_Listeners.push_back(pListener);
}

void InputService::clearListeners() {
	m_Listeners.clear();
}

} /* namespace hsg */
