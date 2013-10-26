#ifndef INPUTSERVICE_H_
#define INPUTSERVICE_H_

#include <vector>

#include "Types.h"
#include "CoordSystem.h"
#include "Interfaces/IInputListener.h"

namespace hsg {

class InputService {
public:
	InputService(CoordSystem* pCoordSystem);
	virtual ~InputService();

    status start();
    void stop();

	void onClick(int x, int y);
	void addListener(IInputListener* pListener);
	void clearListeners();

private:
	CoordSystem* m_pCoordSystem;
	std::vector<IInputListener*> m_Listeners;
};

} /* namespace hsg */
#endif /* INPUTSERVICE_H_ */
