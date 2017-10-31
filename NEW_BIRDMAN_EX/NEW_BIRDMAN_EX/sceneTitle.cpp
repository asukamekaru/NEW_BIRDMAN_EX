#include "Main.h"
#include "Base.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "DebugMode.h"
#include "titleLogo.h"
#include "titleSelect.h"

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										定数									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//

#define _UI_SHUTTER_X 160
#define _UI_SHUTTER_SPEED 10

struct ShutterStatus
{
	int ShutterX;
	int ShutterTimer;
	bool ShutterFlg;
	bool ShutterMoveFlg;
};

struct ShutterStatus Yellow =
{
	_UI_SHUTTER_X,
	30,
	TRUE,
	FALSE,
};

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										初期化									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
bool SCENE_TITLE :: initialize()
{
	iNowTitleMode = _SCENE_TITLE_LOGO;//タイトルシーン初期画面をロゴ画面にする



	if(_IMG_MAX != 0)
	{
		iImage = new int*[_IMG_MAX];

		ipLoadImage(&iImage[_IMG_TITLE_LSHUTTER],"../images/title/title_shutter1.png");//シャッター左
		ipLoadImage(&iImage[_IMG_TITLE_RSHUTTER],"../images/title/title_shutter2.png");//シャッター右
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
//										解放									   //
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
//										更新									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
bool SCENE_TITLE::Update()
{
	switch(iNowTitleMode){
	case _SCENE_TITLE_LOGO:
		TitleLogo.Update();
		if(iKey_Check(_KEY_MODE_TRG,_KEY_SPACE))
		break;
	case _SCENE_TITLE_SELECT:
		TitleSelect.Update();
		if(iKey_Check(_KEY_MODE_TRG,_KEY_SPACE))
		break;
	}

	//↓↓↓↓↓↓//シャッター//↓↓↓↓↓↓//

	Shutter();

	if(iKey_Check(_KEY_MODE_TRG,_KEY_SPACE) && !Yellow.ShutterMoveFlg) Yellow.ShutterFlg = !Yellow.ShutterFlg , Yellow.ShutterMoveFlg = true;

	//↑↑↑↑↑↑//シャッター//↑↑↑↑↑↑//

	return true;
}

void SCENE_TITLE::Shutter(bool shutterFlg,bool shutterMoveFlg){

	if(shutterFlg)//シャッター開く
	{
		if(Yellow.ShutterX > -_UI_SHUTTER_X)Yellow.ShutterX -= _UI_SHUTTER_SPEED;
		else Yellow.ShutterMoveFlg = false;
	}
	else//シャッター閉じる
	{
		if(Yellow.ShutterX < _UI_SHUTTER_X){
			Yellow.ShutterX += _UI_SHUTTER_SPEED;
		}else if(--Yellow.ShutterTimer <= 0){
			Yellow.ShutterTimer = 60;
			iNowTitleMode = _SCENE_TITLE_SELECT;
			Yellow.ShutterFlg = true;
			Yellow.ShutterMoveFlg = false;
		}
	}
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										描画									   //
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

	//↓↓↓↓↓↓//画像//↓↓↓↓↓↓//

	//シャッター
	sscDrawGraph(Yellow.ShutterX, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_IMG_TITLE_LSHUTTER][0], FALSE, FALSE );
	sscDrawGraph(_DEF_SCREEN_X - Yellow.ShutterX, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_IMG_TITLE_RSHUTTER][0], FALSE, FALSE );

	//↑↑↑↑↑↑//画像//↑↑↑↑↑↑//

	DrawFormatString(0,20,_COLOR_WHITE,"%f",_NOW_SCREEN_X);
	DrawFormatString(0,30,_COLOR_WHITE,"%f",_NOW_SCREEN_Y);

}