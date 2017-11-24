#include "Main.h"
#include "Base.h"
#include "sceneGMain.h"
#include "GMainRound.h"

GMAIN_ROUND GMainRound;

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										�萔									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//

#define _BALL_SPEED 1

float fSpinBall;

int i = 0;

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										������									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
bool GMAIN_ROUND :: initialize()
{
	if(_IMG_MAX != 0)
	{
		iImage = new int*[_IMG_MAX];
		ipLoadImage(&iImage[_GMAIN_ROUND_RBALL1],"../images/gamemain/UI/RoundBall1.png",10,10,1,514,480);//���E���h�{�[��1
		ipLoadImage(&iImage[_GMAIN_ROUND_RBALL2],"../images/gamemain/UI/RoundBall2.png",10,10,1,332,331);//���E���h�{�[��2
		ipLoadImage(&iImage[_GMAIN_ROUND_REFFECT1],"../images/gamemain/UI/RoundEffect.png");//���E���h�G�t�F�N�g
	}

	if(_SE_MAX != 0)
	{
		iSe = new int *[_SE_MAX];
	}

	return true;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										���									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
void GMAIN_ROUND::Release()
{
	for (int i=0; i<_IMG_MAX;i++)
	{
		if(iImage[i]) delete iImage[i];
		iImage[i] = NULL;
	}
	for (int i=0; i<_SE_MAX; i++)
	{
		if(iSe[i])delete iSe[i];
		iSe[i] = NULL;
	}
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										�X�V									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
bool GMAIN_ROUND::Update()
{
	//�������
	fSpinBall = (fSpinBall <= 360) ? fSpinBall += _BALL_SPEED : fSpinBall -= 360;//�w�i�{�[���̉�]
	return true;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										�`��									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
void GMAIN_ROUND::Render()
{

	//������������//�摜//������������//
	sscDrawGraph(_DEF_SCREEN_X / 2, _DEF_SCREEN_Y / 2, 1.0, fSpinBall,iImage[_GMAIN_ROUND_RBALL1][0], TRUE, FALSE );//���E���h�{�[��1
	sscDrawGraph(_DEF_SCREEN_X / 2, _DEF_SCREEN_Y / 2, 1.0, -fSpinBall,iImage[_GMAIN_ROUND_RBALL2][0], TRUE, FALSE );//���E���h�{�[��2
	
	//sscDrawGraph(_DEF_SCREEN_X / 2, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_GMAIN_ROUND_REFFECT1][0], TRUE, FALSE );//���E���h�G�t�F�N�g

	

	//������������//�摜//������������//
}