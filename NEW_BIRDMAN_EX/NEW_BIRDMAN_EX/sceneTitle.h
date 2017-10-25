#ifndef _SCENE_TITLE_H_
#define _SCENE_TITLE_H_

#include"Scene.h"

class SCENE_TITLE : public Scene
{

private:

	enum{
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

#endif //!_SCENE_TITLE_H_