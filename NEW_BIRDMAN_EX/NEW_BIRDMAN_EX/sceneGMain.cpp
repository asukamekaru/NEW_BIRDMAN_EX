#include "Main.h"
#include "Base.h"
#include "SceneTitle.h"
#include "SceneGMain.h"
#include "DebugMode.h"

#include <stdio.h>
#include <string.h>

#define UPPER_FRAME_Y 35 //上画面UIの高さ
#define UPPER_FRAME_X 151//上画面UIの横
#define FOOTER_FRAME_Y 450//下画面UIの高さ
#define FOOTER_FRAME_X 139//下画面UIの横

SCENE_GMAIN SceneGMain;
//
//初期化
//
bool SCENE_GMAIN::initialize()
{
	if(_IMG_MAX != 0)
	{
		iImage = new int *[_IMG_MAX];

		ipLoadImage(&iImage[_SCENE_GMAIN_STAGE],initCandM("../images/gamemain/main_stage",GameWork.iNowStage, ".png"));//背景
		ipLoadImage(&iImage[_SCENE_GMAIN_C1P],initCandM("../images/gamemain/character/",GameWork.iNowChar1P+1, "charactor1P.png"),120,8,15,160,160);//1Pの画像
		ipLoadImage(&iImage[_SCENE_GMAIN_C2P],initCandM("../images/gamemain/character/",GameWork.iNowChar2P+1, "charactor2P.png"),120,8,15,160,160);//2Pの画像
		ipLoadImage(&iImage[_SCENE_GMAIN_UPPER_1],"../images/gamemain/UI/Frame_Upper1.png");//上画面のフレーム1
		ipLoadImage(&iImage[_SCENE_GMAIN_UPPER_2],"../images/gamemain/UI/Frame_Upper2.png");//上画面のフレーム2
		ipLoadImage(&iImage[_SCENE_GMAIN_FOOTER_1],"../images/gamemain/UI/Frame_Footer1.png");//下画面のフレーム1
		ipLoadImage(&iImage[_SCENE_GMAIN_FOOTER_2],"../images/gamemain/UI/Frame_Footer2.png");//下画面のフレーム2

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
//解放
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
//更新
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
//描画
//
void SCENE_GMAIN::Render()
{
	sscDrawGraph(_DEF_SCREEN_X / 2, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_SCENE_GMAIN_STAGE][0], FALSE, FALSE );	
	sscDrawGraph(100, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_SCENE_GMAIN_C1P][0], TRUE, FALSE );	
	sscDrawGraph(500, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_SCENE_GMAIN_C2P][0], TRUE, TRUE );	
	
	/*=========================/ 上画面フレーム /=========================*/
	sscDrawGraph(_DEF_SCREEN_X / 2 - UPPER_FRAME_X + 1, UPPER_FRAME_Y + 1, 1.0, 0.0,iImage[_SCENE_GMAIN_UPPER_1][0], TRUE, FALSE );//上画面のフレーム1左
	sscDrawGraph(_DEF_SCREEN_X / 2, UPPER_FRAME_Y, 1.0, 0.0,iImage[_SCENE_GMAIN_UPPER_2][0], TRUE, FALSE );//上画面のフレーム2中
	sscDrawGraph(_DEF_SCREEN_X / 2 + UPPER_FRAME_X, UPPER_FRAME_Y + 1, 1.0, 0.0,iImage[_SCENE_GMAIN_UPPER_1][0], TRUE, TRUE );//上画面のフレーム1右

	/*=========================/ 下画面フレーム /=========================*/
	sscDrawGraph(FOOTER_FRAME_X, FOOTER_FRAME_Y, 1.0, 0.0,iImage[_SCENE_GMAIN_FOOTER_1][0], TRUE, FALSE );//下画面のフレーム1左
	sscDrawGraph(_DEF_SCREEN_X - FOOTER_FRAME_X, FOOTER_FRAME_Y, 1.0, 0.0,iImage[_SCENE_GMAIN_FOOTER_1][0], TRUE, TRUE );//下画面のフレーム1右
	//sscDrawGraph(500, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_SCENE_GMAIN_FOOTER_2][0], TRUE, FALSE );	
}