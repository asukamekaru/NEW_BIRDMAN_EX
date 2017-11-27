#include "Main.h"
#include "Base.h"
#include "sceneGMain.h"
#include "GMainRound.h"

GMAIN_ROUND GMainRound;

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										�萔									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//

enum{//�X�N���[�����o�̏㉺
	_STANGING_SCROLL_X,
	_STANGING_SCROLL_Y
};

#define _BALL_SPEED 1//�{�[���X�s�[�h

//�X�N���[�����o�֘A SS = StangingScroll
#define _SS_SPEED 2//�X�N���[�����o�̃X�s�[�h
#define _SS_POSITION_Y 105//�X�N���[�����o�̌Œ�Y���W�i��j



float fSpinBallAngle;//���{�[���̊p�x

//int StagingScrollPosition[x][y] -��1-��2-��1-��2-
int iSSPosition[4][2] = {

	{_DEF_SCREEN_X/2*3,_DEF_SCREEN_Y/2 + _SS_POSITION_Y},
	{_DEF_SCREEN_X/2,_DEF_SCREEN_Y/2 + _SS_POSITION_Y+10},
	{_DEF_SCREEN_X/2*3,_DEF_SCREEN_Y/2 - _SS_POSITION_Y},
	{_DEF_SCREEN_X/2,_DEF_SCREEN_Y/2 - _SS_POSITION_Y+10}};


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
		ipLoadImage(&iImage[_GMAIN_ROUND_STANGING1],"../images/gamemain/UI/RoundEffect.png");//���E���h�G�t�F�N�g
		ipLoadImage(&iImage[_GMAIN_ROUND_STANGING_SCROLL],"../images/gamemain/UI/RoundScroll.png");//���E���h�G�t�F�N�g
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
	fSpinBallAngle = (fSpinBallAngle <= 360) ? fSpinBallAngle += _BALL_SPEED : fSpinBallAngle -= 360;//�w�i�{�[���̉�]

	return true;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										�`��									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
void GMAIN_ROUND::Render()
{

	//������������//�摜//������������//
	sscDrawGraph(_DEF_SCREEN_X / 2, _DEF_SCREEN_Y / 2, 1.0, fSpinBallAngle,iImage[_GMAIN_ROUND_RBALL1][0], TRUE, FALSE );//���E���h�{�[��1
	sscDrawGraph(_DEF_SCREEN_X / 2, _DEF_SCREEN_Y / 2, 1.0, -fSpinBallAngle,iImage[_GMAIN_ROUND_RBALL2][0], TRUE, FALSE );//���E���h�{�[��2

	for(int i = 0;i < 4;i++){//���E���h���X�N���[��
		sscDrawGraph( iSSPosition[i][_STANGING_SCROLL_X],iSSPosition[i][_STANGING_SCROLL_Y], 1.0, 0.0,iImage[_GMAIN_ROUND_STANGING_SCROLL][0],TRUE,FALSE );
		iSSPosition[i][_STANGING_SCROLL_X] = (iSSPosition[i][_STANGING_SCROLL_X] >= -_DEF_SCREEN_X / 2) ? iSSPosition[i][_STANGING_SCROLL_X] -= _SS_SPEED : _DEF_SCREEN_X/2*3;
	}
	//sscDrawGraph(_DEF_SCREEN_X / 2, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_GMAIN_ROUND_REFFECT1][0], TRUE, FALSE );//���E���h�G�t�F�N�g



	//������������//�摜//������������//
}