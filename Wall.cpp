#include "Wall.h"

#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/range/algorithm_ext/push_back.hpp>
#include <boost/bind.hpp>

namespace hsg {
    using namespace boost;
    using namespace boost::adaptors;

    Wall::Wall(Context* context, WallLayout* layout):
	m_context(context),
	m_graphicsService(context->graphicsService){

	push_back(m_bricks, layout->bricks | transformed(bind(&Wall::createBreak, this, _1)));
	m_layout = *layout;
    }

    void Wall::spawn(){
	for_each(m_bricks, bind(&Brick::spawn, _1));
    }

    void Wall::update(){
	for_each(m_bricks, bind(&Brick::update, _1));
	m_bricks.erase(std::remove_if(m_bricks.begin(), m_bricks.end(), bind(&Brick::collided, _1)), m_bricks.end());
    }

    Brick::ptr Wall::createBreak(BrickLayout& brickLayout){
	return Brick::ptr(new Brick(m_context, brickLayout));
    }

    Wall::~Wall() {
    }

} /* namespace hsg */
