#ifndef _MAIN_GROUND_H_
#define _MAIN_GROUND_H_

#include"Base.h"

class GMAIN_ROUND : public BASE_WORK
{

private:

	int iRoundStaging;
	int iStaging1;//���o1
	int iStaging2;//���o2
	int iStagingTime;//���o�̎���
	int iROUND_STAGING;//���o�̏���

	float fSpinBallAngle;//���{�[���̊p�x

	enum{
		_GMAIN_ROUND_RBALL1,//���E���h�{�[��1
		_GMAIN_ROUND_RBALL2,//���E���h�{�[��2
		_GMAIN_ROUND_STANGING_SCROLL,//���E���h�X�N���[�����o
		_GMAIN_ROUND_STANGING_ROUND,//���E���h1���o
		_GMAIN_ROUND_STANGING_FIGHT1,//�t�@�C�g!���o
		_GMAIN_ROUND_STANGING_FIGHT2,//���E���h�t�@�C�g���o
		_IMG_MAX
	};

	enum{
		_SE_MAX
	};

protected:

	int** iImage;
	int** iSe;

public:
	bool initialize();
	void Release();
	bool Update();
	void Render();
	int CHANGE_STAGING (int iCHANGETIME,int i,int STAGING);
	int CHANGE_STAGING_IMG (int A,int IMGNUM,bool bHIDDEN_IMG);
};

extern GMAIN_ROUND GMainRound;

#endif //!_MAIN_GROUND_H_