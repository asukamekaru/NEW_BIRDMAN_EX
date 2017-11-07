#ifndef _SCENE_MAIN_H_
#define _SCENE_MAIN_H_

#include "Scene.h"

class SceneMain : public Scene
{
private:
	enum{
		_IMG_MAX
	};

	enum{
		_SE_MAX
	};

	enum{
		_BGM_GAME_PLAY,
		_BGM_GAME_OVER,
		_BGM_GAME_CLEAR,
	};

	enum {
	_GAME_START_PLAY,
	_GAME_START_OVER,
	_GAME_START_CLEAR,
};

	void Message(char* msg);

public:
	bool initialize();
	void Release();
	bool Update();
	void Render();
};

#endif //!_SCENE_MAIN_H_