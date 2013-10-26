#ifndef HSG_GAMELAYOUT_H
#define HSG_GAMELAYOUT_H

#include "Vector3.h"
#include "CoordSystem.h"
#include "rapidxml.hpp"

#include <string>
#include <vector>

namespace hsg {

    using namespace gameplay;

    struct BackgroundLayout {
	float width;
	float height;
	Vector3 center;
	std::string fileName;
    }

    struct BatLayout {
	float width;
	float height;
	Vector3 center;
	std::string fileName;
    }

    struct BallLayout {
	float diameter;
	Vector3 center;
	std::string fileName;
    }

    struct BrickLayout {
	float width;
	float height;
	Vector3 center;
	std::string fileName;
    }

    struct WallLayout {
	float width;
	float height;
	Vector3 center;

	std::vector<BrickLayout> bricks;
    }

    struct GameLayout {
	GameLayout(CoordSystem* coordSystem);
	void loadLevel(const char* fileName);

	BackgroundLayout background;
	BatLayout bat;
	BallLayout ball;
	WallLayout wall;
	
	float width;
	float height;
	Vector3 center;

    private:
	void parseMosaic(xml_node<> *mosaicNode);
    }
}

#endif
