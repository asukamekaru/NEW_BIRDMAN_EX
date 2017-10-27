#ifndef _DEBUG_MODE_H_
#define _DEBUG_MODE_H_

#include"Scene.h"

class DEBUG_MODE : public Scene
{

private:

protected:

public:
	bool initialize();
	void Release();
	bool Update();
	void Render();
};

#endif //!_DEBUG_MODE_H_