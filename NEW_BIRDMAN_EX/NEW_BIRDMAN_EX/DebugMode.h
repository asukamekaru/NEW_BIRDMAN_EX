#ifndef _DEBUG_MODE_H_
#define _DEBUG_MODE_H_

#include"Base.h"

class DEBUG_MODE : public Scene
{

private:



protected:



public:

	int select1p;
	int select2p;
	int selectstage;

	bool initialize();
	void Release();
	bool Update();
	void Render();
	void SceneSelect();
	void CharSelectP1();
	void CharSelectP2();
	void StageSelect();
};

class DEBUG_MODE_SELECT : public GAME_WORK
{
public:
	int P1;
	int P2;
	int STAGE;

	void SELECT();

};

extern DEBUG_MODE DebugMode;

#endif //!_DEBUG_MODE_H_