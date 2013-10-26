#ifndef HSG_GAMELAYOUT_H
#define HSG_GAMELAYOUT_H

#include "Vector3.h"
#include <string>

namespace hsg {

    using namespace gameplay;

    struct BatLayout {
	float width;
	float height;
	Vector3 center;
    }

    struct BallLayout {
	float diameter;
	Vector3 center;
    }

    struct WallLayout {
	float width;
	float height;
	Vector3 center;
    }

    struct GameLayout {
	GameLayout(CoordSystem* coordSystem){
	    width = coorSystem->right() - coorSystem->left();
	    height = coorSystem->top() - coorSystem->bottom();
	    center = coorSystem->center();
	    
	    wall.width = width * 0.8;
	    wall.heiht = height * 0.5;
	    
	    ball.diameter = width * 0.05;
	    
	    bat.width  = width * 0.25;
	    bat.height = height * 0.025;

	    bat.center.set(coorSystem->center().x,
			      coorSystem->bottom() + bat.height / 2,
			      0);

	    ball.center = bat.center;
	    ball.center.y += bat.height / 2 + ball.diameter / 2;
	    
	    wall.center.set(coorSystem->center().x,
			    coorSystem->top() - height * 0.1 -  wall.heiht / 2,
			    0);
	    
	}

	BatLayout bat;
	BallLayout ball;
	WallLayout wall;
	
	float width;
	float height;
	Vector3 center;
    }
}

#endif
