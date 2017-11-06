#ifndef _SCENE_TITLE_H_
#define _SCENE_TITLE_H_

#include"Scene.h"

class SCENE_TITLE : public Scene
{

private:
	enum{
		_SCENE_TITLE_LOGO,
		_SCENE_TITLE_SELECT,
		_SCENE_TITLE_DESCRIBE
	};

	enum{
		NEXT,
		BACK
	};

	enum{
		_IMG_TITLE_YLSHUTTER,//���V���b�^�[�i���j
		_IMG_TITLE_YRSHUTTER,//���V���b�^�[�i�E�j
		_IMG_TITLE_RLSHUTTER,//�ԃV���b�^�[�i���j
		_IMG_TITLE_RRSHUTTER,//�ԃV���b�^�[�i�E�j
		_IMG_TITLE_SSHUTTER,//�ȃV���b�^�[�i���j
		_IMG_MAX
	};

	enum{
		_BGM_TITLE,
		_SE_MAX
	};

protected:

	int iNowTitleMode;//�^�C�g���V�[���̕`����(1,���S��� 2,�I�����)
	int iTitleState;

public:

	bool initialize();
	void Release();
	bool Update();
	void Shutter(bool& shutterFlg,int& shutterX,int& shutterTime,int shutterUIX);
	void Render();
};

#endif //!_SCENE_TITLE_H_