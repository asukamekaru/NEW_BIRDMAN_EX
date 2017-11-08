#include "Main.h"
#include "Base.h"
#include "SceneTitle.h"
#include "SceneGMain.h"
#include "DebugMode.h"
#include "titleLogo.h"
#include "titleSelect.h"
#include "titleDescribe.h"

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										�萔									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//

#define _UI_SHUTTER_SPEED	10//�V���b�^�[�J�̎���
#define _UI_SHUTTER_TIME	30//�����V���b�^�[���J���܂ł̎���

struct ShutterStatus
{
	const int csX;//CShutterX �V���b�^�[�̌Œ�ʒu
	int sX;//ShutterX �V���b�^�[�摜�̏����ʒuX
	int sT;//ShutterTimer �V���b�^�[�����čēx�J���܂ł̎���
	bool sF;//ShutterFlag //�V���b�^�[�N����
	bool sMF;//ShutterMoveFlag //�V���b�^�[�ړ���
};

struct ShutterStatus YellowS ={160,160,_UI_SHUTTER_TIME,TRUE,FALSE,};
struct ShutterStatus RedS ={173,-173,_UI_SHUTTER_TIME,TRUE,FALSE,};
struct ShutterStatus SpriteS ={_DEF_SCREEN_X / 2,- _DEF_SCREEN_X * 2,_UI_SHUTTER_TIME,TRUE,FALSE,};

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										������									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
bool SCENE_TITLE :: initialize()
{
	iNowTitleMode = _SCENE_TITLE_LOGO;//�^�C�g���V�[��������ʂ����S��ʂɂ���

	if(_IMG_MAX != 0)
	{
		iImage = new int*[_IMG_MAX];

		ipLoadImage(&iImage[_IMG_TITLE_YLSHUTTER],"../images/title/title_shutter1.png");//���V���b�^�[��
		ipLoadImage(&iImage[_IMG_TITLE_YRSHUTTER],"../images/title/title_shutter2.png");//���V���b�^�[�E
		ipLoadImage(&iImage[_IMG_TITLE_RLSHUTTER],"../images/title/VS1.png");//�ԃV���b�^�[��
		ipLoadImage(&iImage[_IMG_TITLE_RRSHUTTER],"../images/title/VS2.png");//�ԃV���b�^�[�E
		ipLoadImage(&iImage[_IMG_TITLE_SSHUTTER],"../images/title/sprite_shutter.png");//�ȃV���b�^�[
	}

	if(_SE_MAX != 0)
	{
		iSe = new int *[_SE_MAX];
	}

	TitleLogo.initialize();
	TitleSelect.initialize();
	TitleDescribe.initialize();

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
	case _SCENE_TITLE_DESCRIBE:
		TitleDescribe.Release();
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
		if(iKey_Check(_KEY_MODE_TRG,_KEY_SPACE)) YellowS.sF = false,iTitleState = NEXT;//�i��
		break;
	case _SCENE_TITLE_SELECT:
		TitleSelect.Update();
		if(iKey_Check(_KEY_MODE_TRG,_KEY_BACK)) YellowS.sF = false,iTitleState = BACK;//�߂�
		if(iKey_Check(_KEY_MODE_TRG,_KEY_SPACE)) RedS.sF = false,iTitleState = NEXT;//�i��
		break;
	case _SCENE_TITLE_DESCRIBE:
		TitleDescribe.Update();
		if(iKey_Check(_KEY_MODE_TRG,_KEY_BACK)) RedS.sF = false,iTitleState = BACK;//�߂�
		if(iKey_Check(_KEY_MODE_TRG,_KEY_SPACE)) SpriteS.sF = false,iTitleState = NEXT;//�i��
		break;
	}

	Shutter(YellowS.sF ,YellowS.sX ,YellowS.sT ,YellowS.csX);//���V���b�^�[
	Shutter(RedS.sF ,RedS.sX ,RedS.sT ,RedS.csX);//�ԃV���b�^�[
	Shutter(SpriteS.sF ,SpriteS.sX ,SpriteS.sT ,SpriteS.csX);//�ȃV���b�^�[


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
	case _SCENE_TITLE_DESCRIBE:
		TitleDescribe.Render();
		break;
	}

	//������������//�摜//������������//

	//���V���b�^�[
	sscDrawGraph(YellowS.sX, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_IMG_TITLE_YLSHUTTER][0], FALSE, FALSE );
	sscDrawGraph(_DEF_SCREEN_X - YellowS.sX, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_IMG_TITLE_YRSHUTTER][0], FALSE, FALSE );

	//�ԃV���b�^�[
	sscDrawGraph(RedS.sX, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_IMG_TITLE_RLSHUTTER][0], TRUE, FALSE );
	sscDrawGraph(_DEF_SCREEN_X - RedS.sX, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_IMG_TITLE_RRSHUTTER][0], TRUE, FALSE );

	//�ȃV���b�^�[
	sscDrawGraph(SpriteS.sX, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_IMG_TITLE_SSHUTTER][0], TRUE, FALSE );
	sscDrawGraph(_DEF_SCREEN_X - SpriteS.sX, _DEF_SCREEN_Y / 2, 1.0, 180.0,iImage[_IMG_TITLE_SSHUTTER][0], TRUE, FALSE );

	//������������//�摜//������������//

}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//									�V���b�^�[ 									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
void SCENE_TITLE::Shutter(bool& shutterFlg,int& shutterX,int& shutterTime,int shutterUIX){

	if(shutterFlg)//�V���b�^�[�J��
	{
		if(shutterX > -shutterUIX)shutterX -= _UI_SHUTTER_SPEED;
	}

	else if(shutterX < shutterUIX){//�V���b�^�[�����

		shutterX += _UI_SHUTTER_SPEED;

		if(shutterX >= shutterUIX)shutterX = shutterUIX;//���ꂽ�玡��

	}else if(--shutterTime <= 0){//��莞�Ԍo�Ă΍ēx�����I�ɊJ��

		switch(iNowTitleMode){
		case _SCENE_TITLE_LOGO:
			iNowTitleMode = (iTitleState == NEXT) ? _SCENE_TITLE_SELECT : NULL;//�i�ނ��߂邩
			break;
		case _SCENE_TITLE_SELECT:
			TitleSelect.fArrowX = _DEF_SCREEN_X;
			iNowTitleMode = (iTitleState == NEXT) ? _SCENE_TITLE_DESCRIBE : _SCENE_TITLE_LOGO;//�i�ނ��߂邩
			break;
		case _SCENE_TITLE_DESCRIBE:
			iNowTitleMode = (iTitleState == NEXT) ? NULL : NULL;//�i�ނ��߂邩
			break;
		}

		//�V���b�^�[���J������Ԃ�
		shutterTime = _UI_SHUTTER_TIME;
		shutterFlg = true;
	}
}