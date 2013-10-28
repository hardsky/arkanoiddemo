#ifndef HSG_COMMONLAYOUT_H
#define HSG_COMMONLAYOUT_H

#include "Vector3.h"
#include <string>

namespace hsg {

    struct BackgroundLayout {
	float width;
	float height;
	gameplay::Vector3 center;
	std::string fileName;
    };

}
#endif
