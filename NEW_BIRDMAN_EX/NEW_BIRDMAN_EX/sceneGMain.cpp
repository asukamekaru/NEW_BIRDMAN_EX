#include "Main.h"
#include "SceneGMain.h"
#include "SceneTitle.h"

char *cImageLoad[3];

//
//������
//
bool SCENE_GMAIN::initialize()
{

	for(int i = 0; i < 3; i++)initCandM(i);

	if(_IMG_MAX != 0)
	{
		ipLoadImage(&iImage[_SCENE_GMAIN_STAGE],cImageLoad[_SCENE_GMAIN_STAGE]);//�w�i
		ipLoadImage(&iImage[_SCENE_GMAIN_C1P],cImageLoad[_SCENE_GMAIN_C1P]);//1P�̉摜
		ipLoadImage(&iImage[_SCENE_GMAIN_C2P],cImageLoad[_SCENE_GMAIN_C2P]);//2P�̉摜
		
		iImage = new int *[_IMG_MAX];
	}

	if(_SE_MAX != 0)
	{
		iSe = new int *[_SE_MAX];
	}

	stGameW.iState = _GAME_START_PLAY;

	return true;
}
void SCENE_GMAIN::initCandM(int a){
	char *cImageCandS[3] ={"../images/gamemain","../images/gamemain/character",""};//0:�w�i�摜 1:1P�摜 2:2P�摜 ---- �O
	char *cImageCandS[3] ={".png","",""};//0:�w�i�摜 1:1P�摜 2:2P�摜 ---- ��
	strcpy_s(buf, s1);
	strcat_s(buf, s2);
	strcat_s(buf, s3);
}

//
//���
//
void SCENE_GMAIN::Release()
{
	for (int i = 0;i<_IMG_MAX;i++)
	{
		if(iImage[i])delete iImage[i];
		iImage[i] = NULL;
	}

	for (int i=0; i<_SE_MAX;i++)
	{
		if(iSe[i])delete iSe[i];
		iSe[i] = NULL;
	}
}
//
//�X�V
//
bool SCENE_GMAIN :: Update()
{
	switch (stGameW.iState)
	{
	case _GAME_START_PLAY:
		break;
	case _GAME_START_CLEAR:
		break;
	case _GAME_START_OVER:
		return true;
		break;
	}
	return false;
}
//
//�`��
//
void SCENE_GMAIN::Render()
{

	switch (stGameW.iState)
	{
	case _GAME_START_PLAY:
		break;

	case _GAME_START_CLEAR:
		break;
	case _GAME_START_OVER:
		break;
	}
}