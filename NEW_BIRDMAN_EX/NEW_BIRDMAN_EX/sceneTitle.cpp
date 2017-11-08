#include "Main.h"
#include "Base.h"
#include "SceneTitle.h"
#include "SceneGMain.h"
#include "DebugMode.h"
#include "titleLogo.h"
#include "titleSelect.h"
#include "titleDescribe.h"

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										定数									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//

#define _UI_SHUTTER_SPEED	10//シャッター開閉の時間
#define _UI_SHUTTER_TIME	30//閉じたシャッターが開くまでの時間

struct ShutterStatus
{
	const int csX;//CShutterX シャッターの固定位置
	int sX;//ShutterX シャッター画像の初期位置X
	int sT;//ShutterTimer シャッターが閉じて再度開くまでの時間
	bool sF;//ShutterFlag //シャッター起動中
	bool sMF;//ShutterMoveFlag //シャッター移動中
};

struct ShutterStatus YellowS ={160,160,_UI_SHUTTER_TIME,TRUE,FALSE,};
struct ShutterStatus RedS ={173,-173,_UI_SHUTTER_TIME,TRUE,FALSE,};
struct ShutterStatus SpriteS ={_DEF_SCREEN_X / 2,- _DEF_SCREEN_X * 2,_UI_SHUTTER_TIME,TRUE,FALSE,};

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										初期化									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
bool SCENE_TITLE :: initialize()
{
	iNowTitleMode = _SCENE_TITLE_LOGO;//タイトルシーン初期画面をロゴ画面にする

	if(_IMG_MAX != 0)
	{
		iImage = new int*[_IMG_MAX];

		ipLoadImage(&iImage[_IMG_TITLE_YLSHUTTER],"../images/title/title_shutter1.png");//黄シャッター左
		ipLoadImage(&iImage[_IMG_TITLE_YRSHUTTER],"../images/title/title_shutter2.png");//黄シャッター右
		ipLoadImage(&iImage[_IMG_TITLE_RLSHUTTER],"../images/title/VS1.png");//赤シャッター左
		ipLoadImage(&iImage[_IMG_TITLE_RRSHUTTER],"../images/title/VS2.png");//赤シャッター右
		ipLoadImage(&iImage[_IMG_TITLE_SSHUTTER],"../images/title/sprite_shutter.png");//縞シャッター
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
//										更新									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
bool SCENE_TITLE::Update()
{
	switch(iNowTitleMode){
	case _SCENE_TITLE_LOGO:
		TitleLogo.Update();
		if(iKey_Check(_KEY_MODE_TRG,_KEY_SPACE)) YellowS.sF = false,iTitleState = NEXT;//進む
		break;
	case _SCENE_TITLE_SELECT:
		TitleSelect.Update();
		if(iKey_Check(_KEY_MODE_TRG,_KEY_BACK)) YellowS.sF = false,iTitleState = BACK;//戻る
		if(iKey_Check(_KEY_MODE_TRG,_KEY_SPACE)) RedS.sF = false,iTitleState = NEXT;//進む
		break;
	case _SCENE_TITLE_DESCRIBE:
		TitleDescribe.Update();
		if(iKey_Check(_KEY_MODE_TRG,_KEY_BACK)) RedS.sF = false,iTitleState = BACK;//戻る
		if(iKey_Check(_KEY_MODE_TRG,_KEY_SPACE)) SpriteS.sF = false,iTitleState = NEXT;//進む
		break;
	}

	Shutter(YellowS.sF ,YellowS.sX ,YellowS.sT ,YellowS.csX);//黄シャッター
	Shutter(RedS.sF ,RedS.sX ,RedS.sT ,RedS.csX);//赤シャッター
	Shutter(SpriteS.sF ,SpriteS.sX ,SpriteS.sT ,SpriteS.csX);//縞シャッター


	return true;
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
	case _SCENE_TITLE_DESCRIBE:
		TitleDescribe.Render();
		break;
	}

	//↓↓↓↓↓↓//画像//↓↓↓↓↓↓//

	//黄シャッター
	sscDrawGraph(YellowS.sX, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_IMG_TITLE_YLSHUTTER][0], FALSE, FALSE );
	sscDrawGraph(_DEF_SCREEN_X - YellowS.sX, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_IMG_TITLE_YRSHUTTER][0], FALSE, FALSE );

	//赤シャッター
	sscDrawGraph(RedS.sX, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_IMG_TITLE_RLSHUTTER][0], TRUE, FALSE );
	sscDrawGraph(_DEF_SCREEN_X - RedS.sX, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_IMG_TITLE_RRSHUTTER][0], TRUE, FALSE );

	//縞シャッター
	sscDrawGraph(SpriteS.sX, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_IMG_TITLE_SSHUTTER][0], TRUE, FALSE );
	sscDrawGraph(_DEF_SCREEN_X - SpriteS.sX, _DEF_SCREEN_Y / 2, 1.0, 180.0,iImage[_IMG_TITLE_SSHUTTER][0], TRUE, FALSE );

	//↑↑↑↑↑↑//画像//↑↑↑↑↑↑//

}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//									シャッター 									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
void SCENE_TITLE::Shutter(bool& shutterFlg,int& shutterX,int& shutterTime,int shutterUIX){

	if(shutterFlg)//シャッター開く
	{
		if(shutterX > -shutterUIX)shutterX -= _UI_SHUTTER_SPEED;
	}

	else if(shutterX < shutterUIX){//シャッターを閉じる

		shutterX += _UI_SHUTTER_SPEED;

		if(shutterX >= shutterUIX)shutterX = shutterUIX;//ずれたら治す

	}else if(--shutterTime <= 0){//一定時間経てば再度自動的に開く

		switch(iNowTitleMode){
		case _SCENE_TITLE_LOGO:
			iNowTitleMode = (iTitleState == NEXT) ? _SCENE_TITLE_SELECT : NULL;//進むか戻るか
			break;
		case _SCENE_TITLE_SELECT:
			TitleSelect.fArrowX = _DEF_SCREEN_X;
			iNowTitleMode = (iTitleState == NEXT) ? _SCENE_TITLE_DESCRIBE : _SCENE_TITLE_LOGO;//進むか戻るか
			break;
		case _SCENE_TITLE_DESCRIBE:
			iNowTitleMode = (iTitleState == NEXT) ? NULL : NULL;//進むか戻るか
			break;
		}

		//シャッターが開いた状態へ
		shutterTime = _UI_SHUTTER_TIME;
		shutterFlg = true;
	}
}