#ifndef HSG_STARTLAYOUT_H
#define HSG_STARTLAYOUT_H

#include "Context.h"
#include "Vector3.h"
#include "CommonLayout.h"

#include <string>

namespace hsg {

    struct ButtonLayout {
	float width;
	float height;
	gameplay::Vector3 center;
	std::string fileName;
    };

    struct StartLayout {
	StartLayout(CoordSystem* coordSystem);

	BackgroundLayout background;
	ButtonLayout button;
	
	float width;
	float height;
	gameplay::Vector3 center;
    };
}

#endif
