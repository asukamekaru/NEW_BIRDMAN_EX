#include "Main.h"
#include "SceneGMain.h"
#include "SceneTitle.h"
//
//‰Šú‰»
//
bool SceneGMain::initialize()
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
//
//‰ğ•ú
//
void SceneGMain :: Release()
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
bool SceneGMain :: Update()
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
void SceneGMain::Render()
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