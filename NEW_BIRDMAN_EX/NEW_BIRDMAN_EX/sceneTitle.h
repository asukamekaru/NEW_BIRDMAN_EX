#ifndef _SCENE_TITLE_H_
#define _SCENE_TITLE_H_

#include"Scene.h"

class SCENE_TITLE : public Scene
{

private:
	enum{
		_SCENE_TITLE_LOGO,
		_SCENE_TITLE_SELECT
	};

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

	int iNowTitleMode;//�^�C�g���V�[���̕`����(1,���S��� 2,�I�����)

public:
	bool initialize();
	void Release();
	bool Update();
	void Shutter();
	void Render();
};

#endif //!_SCENE_TITLE_H_