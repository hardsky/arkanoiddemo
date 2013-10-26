#include "GameOver.h"
#include "Field/FieldLayout.h"

#include "Interfaces/IAnimation.h"
#include "AnimationService.h"
#include "Animation/GameWinAnimation.h"
#include "Animation/StubAnimation.h"
#include "GraphicsService.h"

#include "Log.h"

namespace hsg {

GameOver::GameOver(Context* pContext):
	m_pAnimator(pContext->mAnimationService),
	m_pWin(pContext->mGraphicsService->registerSprite("win_label.png", FieldLayout::ANIM_LAYER_OVER)),
	m_pOver(pContext->mGraphicsService->registerSprite("over_label.png", FieldLayout::ANIM_LAYER_OVER)){
	// TODO Auto-generated constructor stub

	m_pWin->setActive(false);
	Vector3 coord(0.0f, 0.0f, 0.0f);
	m_pWin->setLocation(coord);
	m_pWin->setSize(2, 2);

	m_pOver->setActive(false);
	m_pOver->setLocation(coord);
	m_pOver->setSize(2, 2);
}

void GameOver::win() {
	//TODO
	HSG_DEBUG("GameOver::win");

	m_pWin->setActive(true);

	IAnimation::ptr animation(new GameWinAnimation());
	m_pAnimator->postAnimation(animation);
}

void GameOver::over() {
	//TODO
	HSG_DEBUG("GameOver::over");

	m_pOver->setActive(true);

	IAnimation::ptr animation(new StubAnimation());
	m_pAnimator->postAnimation(animation);
}

GameOver::~GameOver() {
	// TODO Auto-generated destructor stub
}

} /* namespace hsg */
