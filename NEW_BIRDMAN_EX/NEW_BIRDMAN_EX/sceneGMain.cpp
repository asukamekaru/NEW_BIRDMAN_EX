#include "Main.h"
#include "SceneGMain.h"
#include "SceneTitle.h"

char *cImageLoad[3];

//
//‰Šú‰»
//
bool SCENE_GMAIN::initialize()
{

	for(int i = 0; i < 3; i++)initCandM(i);

	if(_IMG_MAX != 0)
	{
		ipLoadImage(&iImage[_SCENE_GMAIN_STAGE],cImageLoad[_SCENE_GMAIN_STAGE]);//”wŒi
		ipLoadImage(&iImage[_SCENE_GMAIN_C1P],cImageLoad[_SCENE_GMAIN_C1P]);//1P‚Ì‰æ‘œ
		ipLoadImage(&iImage[_SCENE_GMAIN_C2P],cImageLoad[_SCENE_GMAIN_C2P]);//2P‚Ì‰æ‘œ
		
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
	char *cImageCandS[3] ={"../images/gamemain","../images/gamemain/character",""};//0:”wŒi‰æ‘œ 1:1P‰æ‘œ 2:2P‰æ‘œ ---- ‘O
	char *cImageCandS[3] ={".png","",""};//0:”wŒi‰æ‘œ 1:1P‰æ‘œ 2:2P‰æ‘œ ---- Œã
	strcpy_s(buf, s1);
	strcat_s(buf, s2);
	strcat_s(buf, s3);
}

//
//‰ğ•ú
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
//XV
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
//•`‰æ
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