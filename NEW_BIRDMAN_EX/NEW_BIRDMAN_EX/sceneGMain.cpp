#include "Main.h"
#include "Base.h"
#include "SceneTitle.h"
#include "SceneGMain.h"
#include "DebugMode.h"

#include <stdio.h>
#include <string.h>

#define UPPER_UI_Y 35
#define UPPER_UI_LR 160

SCENE_GMAIN SceneGMain;
//
//èâä˙âª
//
bool SCENE_GMAIN::initialize()
{
	if(_IMG_MAX != 0)
	{
		iImage = new int *[_IMG_MAX];

		ipLoadImage(&iImage[_SCENE_GMAIN_STAGE],initCandM("../images/gamemain/main_stage",GameWork.iNowStage, ".png"));//îwåi
		ipLoadImage(&iImage[_SCENE_GMAIN_C1P],initCandM("../images/gamemain/character/",GameWork.iNowChar1P+1, "charactor1P.png"),120,8,15,160,160);//1PÇÃâÊëú
		ipLoadImage(&iImage[_SCENE_GMAIN_C2P],initCandM("../images/gamemain/character/",GameWork.iNowChar2P+1, "charactor2P.png"),120,8,15,160,160);//2PÇÃâÊëú
		ipLoadImage(&iImage[_SCENE_GMAIN_UPPER_1],"../images/gamemain/UI/Frame_Upper1.png");//è„âÊñ ÇÃUI1
		ipLoadImage(&iImage[_SCENE_GMAIN_UPPER_2],"../images/gamemain/UI/Frame_Upper2.png");//è„âÊñ ÇÃUI2
		ipLoadImage(&iImage[_SCENE_GMAIN_FOOTER_1],"../images/gamemain/UI/Frame_Footer1.png");//â∫âÊñ ÇÃUI1
		ipLoadImage(&iImage[_SCENE_GMAIN_FOOTER_2],"../images/gamemain/UI/Frame_Footer2.png");//â∫âÊñ ÇÃUI2

	}

	if(_SE_MAX != 0)
	{
		iSe = new int *[_SE_MAX];


	}

	GameWork.iState = _GAME_ROUND;

	return true;
}

char *SCENE_GMAIN::initCandM(char* HEAD_ADDRESS,int NOWNUM,char* FOOT_ADDRESS){

	static char cImageLoad[254];

	char buf[12];
	int i = NOWNUM;

	sprintf_s(buf, 12, "%d", i);
	puts(buf);

	strcpy_s(cImageLoad, HEAD_ADDRESS);
	strcat_s(cImageLoad, buf);
	strcat_s(cImageLoad, FOOT_ADDRESS);

	return cImageLoad;
}

//
//âï˙
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
//çXêV
//
bool SCENE_GMAIN :: Update()
{
	switch(GameWork.iState)
	{
	case _GAME_ROUND:
		break;
	case _GAME_PLAY:
		break;
	case _GAME_RESULT:
		break;
	}
	return true;
}
//
//ï`âÊ
//
void SCENE_GMAIN::Render()
{
	sscDrawGraph(_DEF_SCREEN_X / 2, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_SCENE_GMAIN_STAGE][0], FALSE, FALSE );	
	sscDrawGraph(100, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_SCENE_GMAIN_C1P][0], TRUE, FALSE );	
	sscDrawGraph(500, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_SCENE_GMAIN_C2P][0], TRUE, TRUE );	
//	sscDrawGraph(UPPER_UI_LR, 35, 1.0, 0.0,iImage[_SCENE_GMAIN_UPPER_1][0], TRUE, FALSE );//è„âÊñ ÇÃUI1ç∂
//	sscDrawGraph(_DEF_SCREEN_X / 2, UPPER_UI_Y, 1.0, 0.0,iImage[_SCENE_GMAIN_UPPER_2][0], TRUE, FALSE );//è„âÊñ ÇÃUI2íÜ
	//sscDrawGraph(_DEF_SCREEN_X - UPPER_UI_LR, UPPER_UI_Y, 1.0, 0.0,iImage[_SCENE_GMAIN_UPPER_1][0], TRUE, TRUE );//è„âÊñ ÇÃUI1âE
	//sscDrawGraph(500, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_SCENE_GMAIN_FOOTER_1][0], TRUE, FALSE );	
	//sscDrawGraph(500, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_SCENE_GMAIN_FOOTER_2][0], TRUE, FALSE );	
}