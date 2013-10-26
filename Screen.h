#ifndef HSG_SCREEN_H
#define HSG_SCREEN_H

#include <boost/shared_ptr.hpp>

namespace hsg{
    class Screen{
    public:
	typedef boost::shared_ptr<Screen> ptr;
    public:
	Screen();
	virtual ~Screen();
	virtual void update();
	virtual void activate();
	virtual void deactivate();
    }
}

#endif
