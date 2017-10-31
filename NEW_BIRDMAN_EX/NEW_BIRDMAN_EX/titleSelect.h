#ifndef _TITLE_CHARACTER_H_
#define _TITLE_CHARACTER_H_

#include"Scene.h"

class TITLE_SELECT : public Scene
{

private:

	enum{
		_TITLE_SELECT_BG,
		_TITLE_SELECT_BGNET,
		_TITLE_SELECT_BGBALL1,
		_TITLE_SELECT_BGBALL2,
		_TITLE_SELECT_CHARSELECT,
		_TITLE_SELECT_ARROW,
		_TITLE_SELECT_UPPERTXT,
		_TITLE_SELECT_FOOTERTXT,
		_TITLE_SELECT_CHARFACES,
		_TITLE_SELECT_CHARBODYS,
		_IMG_MAX
	};

	enum{
		_SE_MAX
	};

protected:

	float fSpinBGBall;//îwåiÇÃÉ{Å[ÉãÇÃâÒì]
	
public:

	float fArrowX;//P1,P2ÇÃñÓàÛ

	bool initialize();
	void Release();
	bool Update();
	void Render();
};

extern TITLE_SELECT TitleSelect;


#endif //!_TITLE_CHARACTER_H_