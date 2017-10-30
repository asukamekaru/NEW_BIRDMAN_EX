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

#define _UI_SHUTTER_X (160)

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										初期化									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
bool SCENE_TITLE :: initialize()
{
	ShutterX = _UI_SHUTTER_X;
	ShutterFlg = TRUE;

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

	//TitleLogo.initialize();
	TitleSelect.initialize();

	return true;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										解放									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
void SCENE_TITLE::Release()
{
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

	//TitleLogo.Release();
	TitleSelect.Release();
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										更新									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
bool SCENE_TITLE::Update()
{
	//TitleLogo.Update();
	TitleSelect.Update();

	//↓↓↓↓↓↓//シャッター//↓↓↓↓↓↓//
	
	if(ShutterFlg == TRUE){//シャッター開く
		if(ShutterX > -_UI_SHUTTER_X){
			ShutterX -= 10;
		}
	}else{//シャッター閉じる
		if(ShutterX < _UI_SHUTTER_X){
			ShutterX += 10;
		}
	}

	//↑↑↑↑↑↑//シャッター//↑↑↑↑↑↑//

	if(iKey_Check(_KEY_MODE_TRG,_KEY_SPACE))ShutterFlg = !ShutterFlg;
	return true;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										描画									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
void SCENE_TITLE::Render()
{
	//TitleLogo.Render();
	TitleSelect.Render();

	//↓↓↓↓↓↓//画像//↓↓↓↓↓↓//

	//シャッター
	sscDrawGraph(ShutterX, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_IMG_TITLE_LSHUTTER][0], FALSE, FALSE );
	sscDrawGraph(_DEF_SCREEN_X - ShutterX, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_IMG_TITLE_RSHUTTER][0], FALSE, FALSE );

	//↑↑↑↑↑↑//画像//↑↑↑↑↑↑//
}