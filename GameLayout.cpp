#include "GameLayout.h"
#include "Log.h"

#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <boost/shared_array.hpp>

namespace hsg {

    using namespace rapidxml;

    GameLayout::GameLayout(CoordSystem* coordSystem){
	width = coordSystem->right() - coordSystem->left();
	height = coordSystem->top() - coordSystem->bottom();
	center = coordSystem->center();
			
	wall.width = width * 0.8;
	wall.height = height * 0.5;
			
	ball.diameter = width * 0.05;
			
	bat.width  = width * 0.25;
	bat.height = height * 0.025;

	bat.center.set(coordSystem->center().x,
		       coordSystem->bottom() + bat.height / 2,
		       0);

	ball.center = bat.center;
	ball.center.y += bat.height / 2 + ball.diameter / 2;
			
	wall.center.set(coordSystem->center().x,
			coordSystem->top() - height * 0.1 -  wall.height / 2,
			0);

	background.width = width;
	background.height = height;
	background.center = center;
    }

/*
    void boost::shared_array<char> GameLayout::readFile(const char* fileName){
	std::ifstream ifs(fileName);

	ifs.seekg (0, ifs.end);
	int length = ifs.tellg();
	ifs.seekg (0, ifs.beg);

	boost::shared_array<char> text(new char[length + 1]);
	ifs.read(text.get(), length);
	ifs.close();
	text[length] = '\0';
	
	return text;
    }
*/
    void GameLayout::loadLevel(const char* fileName){
	HSG_DEBUG("GameLayout::loadLevel: %s", fileName);

	boost::shared_array<char> text;

	{
	    std::ifstream ifs(fileName);
	    ifs.seekg (0, ifs.end);
	    int length = ifs.tellg();
	    ifs.seekg (0, ifs.beg);
	    text.reset(new char[length + 1]);
	    ifs.read(text.get(), length);
	    ifs.close();
	    text[length] = '\0';
	    
	    HSG_DEBUG("file length: %d",length);
	    HSG_DEBUG("%s",text.get());
	}

	xml_document<> doc;
	doc.parse<0>(text.get());

	xml_node<> *nodeLevel = doc.first_node("level");

	for(xml_node<> *node = nodeLevel->first_node("background"); node; node = node->next_sibling()){
	    HSG_DEBUG(node->name());
	    xml_attribute<> *attr = node->first_attribute();
	    if(!strcmp(node->name(), "background")){
		HSG_DEBUG(attr->value());
		background.fileName = attr->value();
	    }
	    else if(!strcmp(node->name(), "ball")){
		ball.fileName = attr->value();
	    }
	    else if(!strcmp(node->name(), "bat")){
		bat.fileName = attr->value();
	    }
	    else if(!strcmp(node->name(), "mosaic")){
		parseMosaic(node);
	    }
	}
    }

    void GameLayout::parseMosaic(xml_node<> *mosaicNode){
	HSG_DEBUG("GameLayout::parseMosaic");

	int rowCnt = 0;
	int colCnt = 0;
	std::vector<std::vector<std::string> > wallStr;
	for(xml_node<>* rowNode = mosaicNode->first_node("row"); rowNode; rowNode = rowNode->next_sibling()){
	    wallStr.push_back(std::vector<std::string>());
	    std::vector<std::string>& rowStr = wallStr.back();
	    ++rowCnt;
	    int rowColCnt = 0;
	    for(xml_node<>* brickNode = rowNode->first_node(); brickNode; brickNode = brickNode->next_sibling()){
		++rowColCnt;
		rowStr.push_back(std::string(brickNode->name()));
	    }

	    colCnt = std::max(colCnt, rowColCnt);
	}

	float brickWidth = wall.width / colCnt;
	float brickHeight = wall.height / rowCnt;
	
	float centerX = 0.0f;
	float topEdge = wall.center.y + wall.height / 2;
	
	float brickY = topEdge - brickHeight / 2;
	for(int row  = 0; row < rowCnt; ++row){

	    std::vector<std::string>& rowStr = wallStr[row];
	    float rowWidth = rowStr.size() * brickWidth;
	    float brickX = centerX - rowWidth / 2;

	    for(int col = 0; col < rowStr.size(); ++col){

		if(strcmp(rowStr[col].c_str(), "hole")){ //not a hole
		    BrickLayout brick;
		    brick.width = brickWidth;
		    brick.height = brickHeight;
		    brick.center.set(brickX, brickY, 0.0f);
		    brick.fileName = rowStr[col] + ".png";

		    wall.bricks.push_back(brick);
		}		

		brickX += brickWidth;

	    }

	    brickY -= brickHeight;
	}
    }
}
