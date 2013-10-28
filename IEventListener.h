#ifndef HSG_IEVENTLISTENER_H
#define HSG_IEVENTLISTENER_H

namespace hsg {
    class IEventListener {
    public:
	virtual ~IEventListener(){}
	
	virtual void onEvent(const Event::ptr& event) = 0;
    }
}

#endif
