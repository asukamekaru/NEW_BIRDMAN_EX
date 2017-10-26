#ifndef _TITLE_LOGO_H_
#define _TITLE_LOGO_H_

#include"Scene.h"

class TITLE_LOGO : public Scene
{

private:

	enum{
		_IMG_TITLE_BG,
		_IMG_TITLE_PtS,
		_IMG_TITLE_LOGO,
		_IMG_TITLE_SCROLL,
		_IMG_MAX
	};

	enum{
		_SE_MAX
	};


public:
	bool initialize();
	void Release();
	bool Update();
	void Render();
};

extern TITLE_LOGO TitleLogo;

#endif //!_TITLE_LOGO_H_