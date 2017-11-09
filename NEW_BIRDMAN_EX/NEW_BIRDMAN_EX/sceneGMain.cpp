#include "Main.h"
#include "SceneGMain.h"
#include "SceneTitle.h"

const char *c1PLoadFile = "a";
const char *c2PLoadFile = "a";
const char *cStageLoadFile = "a";
char c1PLoad[245];
char c2PLoad[245];
char cStageLoad[245];
//
//èâä˙âª
//
bool SCENE_GMAIN::initialize()
{
	if(_IMG_MAX != 0)
	{

		iImage = new int *[_IMG_MAX];
	}

	if(_SE_MAX != 0)
	{
		iSe = new int *[_SE_MAX];
	}

	stGameW.iState = _GAME_START_PLAY;

	return true;
}

void
//
//âï˙
//
void SCENE_GMAIN :: Release()
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
//ï`âÊ
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