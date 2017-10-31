#include "Main.h"
#include "Base.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "DebugMode.h"
#include "titleLogo.h"
#include "titleSelect.h"

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										�萔									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//

#define _UI_SHUTTER_X		160
#define _UI_SHUTTER_SPEED	10
#define _UI_SHUTTER_TIME	60

struct ShutterStatus
{
	int sX;//ShutterX �V���b�^�[�摜�̈ʒuX
	int sT;//ShutterTimer �V���b�^�[�����čēx�J���܂ł̎���
	bool sF;//ShutterFlag //�V���b�^�[�N����
	bool sMF;//ShutterMoveFlag //�V���b�^�[�ړ���
};

struct ShutterStatus YellowS ={_UI_SHUTTER_X,30,TRUE,FALSE,};

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										������									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
bool SCENE_TITLE :: initialize()
{
	iNowTitleMode = _SCENE_TITLE_LOGO;//�^�C�g���V�[��������ʂ����S��ʂɂ���



	if(_IMG_MAX != 0)
	{
		iImage = new int*[_IMG_MAX];

		ipLoadImage(&iImage[_IMG_TITLE_LSHUTTER],"../images/title/title_shutter1.png");//�V���b�^�[��
		ipLoadImage(&iImage[_IMG_TITLE_RSHUTTER],"../images/title/title_shutter2.png");//�V���b�^�[�E
	}

	if(_SE_MAX != 0)
	{
		iSe = new int *[_SE_MAX];
	}

	TitleLogo.initialize();
	TitleSelect.initialize();

	return true;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										���									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
void SCENE_TITLE::Release()
{
	switch(iNowTitleMode){
	case _SCENE_TITLE_LOGO:
		TitleLogo.Release();
		break;
	case _SCENE_TITLE_SELECT:
		TitleSelect.Release();
		break;
	}

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
bool SCENE_TITLE::Update()
{
	switch(iNowTitleMode){
	case _SCENE_TITLE_LOGO:
		TitleLogo.Update();
		if(iKey_Check(_KEY_MODE_TRG,_KEY_SPACE) && !YellowS.sMF) YellowS.sF = false,YellowS.sMF = true;
		break;
	case _SCENE_TITLE_SELECT:
		TitleSelect.Update();
		if(iKey_Check(_KEY_MODE_TRG,_KEY_SPACE) && !YellowS.sMF) YellowS.sF = false, YellowS.sMF = true;
		break;
	}

	//������������//�V���b�^�[//������������//

	Shutter(YellowS.sF ,YellowS.sMF ,YellowS.sX ,YellowS.sT );

	//������������//�V���b�^�[//������������//

	return true;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										�`��									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
void SCENE_TITLE::Render()
{
	switch(iNowTitleMode){
	case _SCENE_TITLE_LOGO:
		TitleLogo.Render();
		break;
	case _SCENE_TITLE_SELECT:
		TitleSelect.Render();
		break;
	}

	//������������//�摜//������������//

	//�V���b�^�[
	sscDrawGraph(YellowS.sX, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_IMG_TITLE_LSHUTTER][0], FALSE, FALSE );
	sscDrawGraph(_DEF_SCREEN_X - YellowS.sX, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_IMG_TITLE_RSHUTTER][0], FALSE, FALSE );

	//������������//�摜//������������//

	DrawFormatString(0,20,_COLOR_WHITE,"%f",_NOW_SCREEN_X);
	DrawFormatString(0,30,_COLOR_WHITE,"%f",_NOW_SCREEN_Y);

}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//									�V���b�^�[ 									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
void SCENE_TITLE::Shutter(bool& shutterFlg,bool& shutterMoveFlg,int& shutterX,int& shutterTime){

	if(shutterFlg)//�V���b�^�[�J��
	{
		if(shutterX > -_UI_SHUTTER_X)shutterX -= _UI_SHUTTER_SPEED;
		else shutterMoveFlg = false;
	}
	else//�V���b�^�[����
	{
		if(shutterX < _UI_SHUTTER_X){//�V���b�^�[�����

			shutterX += _UI_SHUTTER_SPEED;

		}else if(--shutterTime <= 0){//��莞�Ԍo�Ă΍ēx�����I�ɊJ��

			switch(iNowTitleMode){
			case _SCENE_TITLE_LOGO:
				iNowTitleMode = _SCENE_TITLE_SELECT;
				break;
			case _SCENE_TITLE_SELECT:
				TitleSelect.fArrowX = _DEF_SCREEN_X;
				iNowTitleMode = _SCENE_TITLE_LOGO;
				break;
			}

			//�V���b�^�[���J������Ԃ�
			shutterTime = _UI_SHUTTER_TIME;
			shutterFlg = true;
			shutterMoveFlg = false;
		}
	}
}