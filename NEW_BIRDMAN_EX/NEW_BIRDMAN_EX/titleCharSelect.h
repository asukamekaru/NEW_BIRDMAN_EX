#ifndef _TITLE_CHARACTER_H_
#define _TITLE_CHARACTER_H_

#include"Scene.h"

class TITLE_CHARACTER : public Scene
{

private:

	enum{
		_IMG_TITLE_BG,
		_IMG_TITLE_PtS,
		_IMG_TITLE_LOGO,
		_IMG_TITLE_SCROLL,
		_IMG_TITLE_LSHUTTER,
		_IMG_TITLE_RSHUTTER,
		_IMG_MAX
	};

	enum{
		_BGM_TITLE,
		_SE_MAX
	};

protected:

	int ShutterX;
	bool ShutterFlg;

public:
	bool initialize();
	void Release();
	bool Update();
	void Render();
};

#endif //!_TITLE_CHARACTER_H_