#include "Main.h"
#include "Base.h"
#include "SceneTitle.h"
#include "SceneGMain.h"
#include "DebugMode.h"

#include <stdio.h>
#include <string.h>

char cImageLoad[254];

char a[254];
char b;
int c = 0;

//
//‰Šú‰»
//
bool SCENE_GMAIN::initialize()
{

	/*initCandM(_SCENE_GMAIN_STAGE,(char)iNowStage);
	initCandM(_SCENE_GMAIN_C1P,(char)iNowChar1P);
	initCandM(_SCENE_GMAIN_C2P,(char)iNowChar2P);*/

	//0:”wŒi‰æ‘œ 1:1P‰æ‘œ 2:2P‰æ‘œ ---- ‘O
	char *cImageHead[3] ={"../images/gamemain/main_stage","../images/gamemain/character","../images/gamemain/character"};
	//0:”wŒi‰æ‘œ 1:1P‰æ‘œ 2:2P‰æ‘œ ---- Œã
	char *cImageFoot[3] ={".png","charactor1P.png","charactor2P.png"};

	//char *a = (char*)iNowStage;

	char a[254];
	char *b;
	int c = 0;

	strcpy_s(a, "../images/gamemain/main_stage");
	strcat_s(a, '0' + c);
	strcat_s(a, ".png");

	if(_IMG_MAX != 0)
	{
		iImage = new int *[_IMG_MAX];


		ipLoadImage(&iImage[_SCENE_GMAIN_STAGE],a);//”wŒi
		//ipLoadImage(&iImage[_SCENE_GMAIN_STAGE],&initCandM("../images/gamemain/main_stage",iNowStage, ".png"));//”wŒi
		//ipLoadImage(&iImage[_SCENE_GMAIN_C1P],initCandM(char *HEAD_ADDRESS,int *NOWNUM,char *FOOT_ADDRESS));//1P‚Ì‰æ‘œ
		//ipLoadImage(&iImage[_SCENE_GMAIN_C2P],initCandM(char *HEAD_ADDRESS,int *NOWNUM,char *FOOT_ADDRESS));//2P‚Ì‰æ‘œ


	}

	if(_SE_MAX != 0)
	{
		iSe = new int *[_SE_MAX];


	}

	//stGameW.iState = _GAME_START_PLAY;

	return true;
}

char& SCENE_GMAIN::initCandM(char* HEAD_ADDRESS,int NOWNUM,char* FOOT_ADDRESS){

	int iChangeVar = NOWNUM;
	char cChangeVar;
	char LoadAddress[254];

	//cChangeVar = '0' + iChangeVar;

	strcpy_s(LoadAddress, "../images/gamemain/main_stage");
	strcat_s(LoadAddress, "0");
	strcat_s(LoadAddress, ".png");
	strcat_s(LoadAddress, "\0");

	return *LoadAddress;
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

	return true;
}
//
//•`‰æ
//
void SCENE_GMAIN::Render()
{
	sscDrawGraph(_DEF_SCREEN_X / 2, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_SCENE_GMAIN_STAGE][0], FALSE, FALSE );	

	DrawString( 0 , 0, a , _COLOR_WHITE ) ;
}