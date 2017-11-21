#ifndef _SCENE_GMAIN_H_
#define _SCENE_GMAIN_H_

#include "Scene.h"

class SCENE_GMAIN : public Scene
{
private:

	enum{
		_SCENE_GMAIN_STAGE,//ステージ
		_SCENE_GMAIN_C1P,//プレイヤー1
		_SCENE_GMAIN_C2P,//プレイヤー2
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
	char *initCandM(char* HEAD_ADDRESS,int NOWNUM,char* FOOT_ADDRESS);
	void Release();
	bool Update();
	void Render();
};

extern SCENE_GMAIN SceneGMain;

#endif //!_SCENE_GMAIN_H_