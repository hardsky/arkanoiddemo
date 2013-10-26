#include "GameLayout.h"
#include <fstream>
#include <string.h>

namespace hsg {
using namespace rapidxml;
    GameLayout::GameLayout(CoordSystem* coordSystem){
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

	background.width = width;
	background.height = height;
	background.center = center;
    }

    void GameLayout::loadLevel(const char* fileName){
	std::stringbuf sb;
	std::ifstream fs(fileName);
	fs >> sb;
	xml_document<> doc;
	doc.parse<0>(sb);

	
	for(xml_node<> *node = doc.first_node("background"); node; node = node->next_sibling()){
	    if(!strcmp(node->name(), "background")){
		xml_attribute<> *attr = node->first_attribute();
		background.fileName = attr->value();
	    }
	    else if(!strcmp(node->name(), "ball")){
		ball.fileName = attr->value();
	    }
	    else if(!strcmp(node->name(), "bat")){
		bat.fileName = attr->value();
	    }
	    else if(!strcmp(node->name(), "mosaic")){
		parseMosaic(xml_node<> *mosaicNode);
	    }
	}
    }

    void GameLayout::parseMosaic(xml_node<> *mosaicNode){
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
	
	float topEdge = wall.center.y + wall.height / 2;
	float leftEdge = wall.center.x - wall.width / 2;
	
	float brickY = topEdge - brickHeight / 2;
	for(int row  = 0; row < rowCnt; ++row){
	    std::vector<std::string>& rowStr = wallStr[row];
	    float brickX = leftEdge + wall.width / 2;

	    for(int col = 0; col < colCnt; ++col){
		BrickLayout brick;
		brick.width = brickWidth - 1;
		brick.height = brickHeight - 1;
		brick.center.set(brickX, brickY, 0.0f);
		brick.fileName = rowStr[col];
		
		wall.bricks.push_back(brick);		

		brickX += brickWidth;
	    }

	    brickY += brickHeight;
	}
    }
}
