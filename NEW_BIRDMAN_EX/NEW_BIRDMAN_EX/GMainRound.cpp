#include "Main.h"
#include "Base.h"
#include "sceneGMain.h"
#include "GMainRound.h"

#include<math.h>

GMAIN_ROUND GMainRound;

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										�萔									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//

enum{//�X�N���[�����o�̏㉺
	_STANGING_SCROLL_X,
	_STANGING_SCROLL_Y
};

enum {//�X�N���[�����o�̏㉺
	_ROUND_SHUTTER,
	_ROUND_ROUND_ANIME,
	_ROUND_FIGHT_ANIME
};

#define _BALL_SPEED 1//�{�[���X�s�[�h

//�X�N���[�����o�֘A SS = StangingScroll
#define _SS_SPEED 2//�X�N���[�����o�̃X�s�[�h
#define _SS_POSITION_Y 110//�X�N���[�����o�̌Œ�Y���W�i��j
#define _SS_POSITION_SPAWN 960//�X�N���[�����o�̌Œ�Y���W�i��j

//int StagingScrollPosition[x][y] -��1-��2-��1-��2-
int iSSPosition[4][2] = {

	{_DEF_SCREEN_X/2,_DEF_SCREEN_Y/2 - _SS_POSITION_Y},//�ŏ��ɉf���i��j
	{_SS_POSITION_SPAWN,_DEF_SCREEN_Y/2 - _SS_POSITION_Y},//�Ō�ɉf���i��j
	{_DEF_SCREEN_X/2,_DEF_SCREEN_Y/2 + _SS_POSITION_Y},//�ŏ��ɉf���i���j
	{_SS_POSITION_SPAWN,_DEF_SCREEN_Y/2 + _SS_POSITION_Y}};//�Ō�ɉf���i���j


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
		ipLoadImage(&iImage[_GMAIN_ROUND_STANGING_SCROLL],"../images/gamemain/UI/RoundScroll.png");//���E���h�G�t�F�N�g
		ipLoadImage(&iImage[_GMAIN_ROUND_STANGING_ROUND],"../images/gamemain/UI/RoundStaging.png",69,23,3,640,202);//���E���h���o
		ipLoadImage(&iImage[_GMAIN_ROUND_STANGING_FIGHT1],"../images/gamemain/UI/RoundFight.png",10,10,1,640,200);//���E���h���o�i�����j
		ipLoadImage(&iImage[_GMAIN_ROUND_STANGING_FIGHT2],"../images/gamemain/UI/RoundEffect.png",9,9,1,636,480);//���E���h���o�i�{�[���j
	}

	if(_SE_MAX != 0)
	{
		iSe = new int *[_SE_MAX];
	}

	iROUND_STANGING = _ROUND_ROUND_ANIME;//�V���b�^�[���o����n�߂�
	iStagingTime = 0;//���o�̎��Ԃ̏�����

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



	switch(iROUND_STANGING){
	case _ROUND_SHUTTER:
		break;
	case _ROUND_ROUND_ANIME:

		//if(iStaging1 != 22)++iStaging1;
		CHANGE_STAGING_IMG (iStaging1,22);
		//CHANGE_STAGING (120,_ROUND_FIGHT_ANIME);

		break;
	case _ROUND_FIGHT_ANIME:
		if(iStaging1 != 9){
			++iStaging1;
		}else if(iStagingTime != 120){
			++iStagingTime;//���o�̎��Ԃ𑝂₷
		}else{
			iROUND_STANGING = _ROUND_ROUND_ANIME;
			iStaging1 = iStagingTime = 0;
		}
		break;
	}

	return true;
}

void GMAIN_ROUND::CHANGE_STAGING (int iCHANGETIME,int STAGING){

	static int iStagingTime = 0;

	if(iStagingTime != iCHANGETIME){
		++iStagingTime;//���o�̎��Ԃ𑝂₷
	}else{
		iROUND_STANGING = STAGING;
		iStaging1 = iStaging2 = iStagingTime = 0;
	}
}

int GMAIN_ROUND::CHANGE_STAGING_IMG (int A,int IMGNUM){

	if(A != IMGNUM)++A;

	return CHANGE_STAGING_IMG(A,IMGNUM);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										�`��									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
void GMAIN_ROUND::Render()
{

	//������������//iROUND_STANGING�̉e�����󂯂��`��//������������//

	//���E���h�{�[��1
	sscDrawGraph(_DEF_SCREEN_X / 2, _DEF_SCREEN_Y / 2, 1.0, fSpinBallAngle,iImage[_GMAIN_ROUND_RBALL1][0], TRUE, FALSE );
	//���E���h�{�[��2
	sscDrawGraph(_DEF_SCREEN_X / 2, _DEF_SCREEN_Y / 2, 1.0, -fSpinBallAngle,iImage[_GMAIN_ROUND_RBALL2][0], TRUE, FALSE );
	//���E���h���X�N���[��
	for(int i = 0;i < 4;i++){
		sscDrawGraph( iSSPosition[i][_STANGING_SCROLL_X],iSSPosition[i][_STANGING_SCROLL_Y], 1.0, 0.0,iImage[_GMAIN_ROUND_STANGING_SCROLL][0],TRUE,FALSE );

		iSSPosition[i][_STANGING_SCROLL_X] = (iSSPosition[i][_STANGING_SCROLL_X] >= -_DEF_SCREEN_X / 2) ? iSSPosition[i][_STANGING_SCROLL_X] -= _SS_SPEED : _SS_POSITION_SPAWN - 4;
	}
	//������������//iROUND_STANGING�̉e�����󂯂��`��//������������//


	switch(iROUND_STANGING){
	case _ROUND_SHUTTER:

		break;
	case _ROUND_ROUND_ANIME:
		sscDrawGraph(_DEF_SCREEN_X / 2, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_GMAIN_ROUND_STANGING_ROUND][iStaging1 + 2 * 23], TRUE, FALSE );//iStaging + (0�`2�̐����ŕς��) * 23
		break;

	case _ROUND_FIGHT_ANIME:
		sscDrawGraph(_DEF_SCREEN_X / 2, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_GMAIN_ROUND_STANGING_FIGHT1][iStaging1], TRUE, FALSE );
		sscDrawGraph(_DEF_SCREEN_X / 2, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_GMAIN_ROUND_STANGING_FIGHT2][iStaging1], TRUE, FALSE );
		break;
	}

	DrawFormatString( 0 , 0 , 0xFFFFFF ,"%d" , iStaging1) ;

}