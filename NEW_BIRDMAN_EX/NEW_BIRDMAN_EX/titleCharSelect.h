#ifndef _TITLE_CHARACTER_H_
#define _TITLE_CHARACTER_H_

#include"Scene.h"

class TITLE_SELECT : public Scene
{

private:

	enum{
		_IMG_MAX
	};

	enum{
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

extern TITLE_SELECT TitleSelect;


#endif //!_TITLE_CHARACTER_H_