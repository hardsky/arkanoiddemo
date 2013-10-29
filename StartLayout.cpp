#include "StartLayout.h"
#include "CoordSystem.h"
#include "Log.h"

namespace hsg {
    StartLayout::StartLayout(CoordSystem* coordSystem){
    	width = coordSystem->right() - coordSystem->left();
	height = coordSystem->top() - coordSystem->bottom();
	center = coordSystem->center();

	button.width = width * 0.3;
	button.height = height * 0.1;
	button.center = center;
	button.center.y =  width / 2 * 0.1;
	button.fileName = "start_button.png";

	background.width = width;
	background.height = height;	
	background.center = center;
	background.fileName = "start_screen.png";	
    }

}
