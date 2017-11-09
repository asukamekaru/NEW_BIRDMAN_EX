#ifndef _SCENE_MAIN_H_
#define _SCENE_MAIN_H_

#include "Scene.h"

class SCENE_GMAIN : public Scene
{
private:

	enum{
		_SCENE_GMAIN_C1P,//�v���C���[1
		_SCENE_GMAIN_C2P,//�v���C���[2
		_SCENE_GMAIN_STAGE,//�X�e�[�W
		_IMG_MAX
	};

	enum{
		_SE_MAX
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