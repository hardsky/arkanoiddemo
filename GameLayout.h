#ifndef HSG_GAMELAYOUT_H
#define HSG_GAMELAYOUT_H

#include "CommonLayout.h"
#include "Vector3.h"
#include "CoordSystem.h"
#include "rapidxml.hpp"

#include <string>
#include <vector>

namespace hsg {

    struct BatLayout {
	float width;
	float height;
	gameplay::Vector3 center;
	std::string fileName;
	int zindex;
    };

    struct BallLayout {
	float diameter;
	gameplay::Vector3 center;
	std::string fileName;
	int zindex;
    };

    struct BrickLayout {
	float width;
	float height;
	gameplay::Vector3 center;
	std::string fileName;
	int zindex;
    };

    struct WallLayout {
	float width;
	float height;
	gameplay::Vector3 center;

	std::vector<BrickLayout> bricks;
	int zindex;
    };

    struct GameLayout {
	GameLayout(CoordSystem* coordSystem);
	void loadLevel(const char* fileName);

	BackgroundLayout background;
	BatLayout bat;
	BallLayout ball;
	WallLayout wall;
	
	float width;
	float height;
	gameplay::Vector3 center;
	int zindex;

    private:
	void parseMosaic(xml_node<> *mosaicNode);
    };    
}

#endif
