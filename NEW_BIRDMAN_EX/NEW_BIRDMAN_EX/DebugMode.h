#ifndef _DEBUG_MODE_H_
#define _DEBUG_MODE_H_

#include"Base.h"

class DEBUG_MODE : public Scene
{

private:



protected:



public:
	bool initialize();
	void Release();
	bool Update();
	void Render();
	void SceneSelect();
	void CharSelectP1();
	void CharSelectP2();
	void StageSelect();
};

#endif //!_DEBUG_MODE_H_