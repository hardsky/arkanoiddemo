#ifndef HSG_GAMEOVER_H_
#define HSG_GAMEOVER_H_

#include "Interfaces/IAnimator.h"
#include "Context.h"
#include "GraphicsSprite.h"

namespace hsg {

class GameOver {
public:
	GameOver(Context* pContext);

	void win();
	void over();

	virtual ~GameOver();
private:
	IAnimator* m_pAnimator;
	GraphicsSprite* m_pWin;
	GraphicsSprite* m_pOver;
};

} /* namespace hsg */
#endif /* HSG_GAMEOVER_H_ */
