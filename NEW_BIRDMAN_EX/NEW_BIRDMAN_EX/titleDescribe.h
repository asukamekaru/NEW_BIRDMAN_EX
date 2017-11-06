#ifndef _TITLE_DESCRIBE_H_
#define _TITLE_DESCRIBE_H_

#include"Scene.h"

class TITLE_DESCRIBE : public Scene
{

private:

	enum{
		_TITLE_DESCRIBE_BG,
		_TITLE_DESCRIBE_DESCRIBE,
		_TITLE_DESCRIBE_TXT,
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

extern TITLE_DESCRIBE TitleDescribe;

#endif //!_TITLE_DESCRIBE_H_