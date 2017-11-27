#include "Main.h"
#include "Base.h"
#include "sceneGMain.h"
#include "GMainRound.h"

GMAIN_ROUND GMainRound;

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										定数									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//

enum{//スクロール演出の上下
	_STANGING_SCROLL_X,
	_STANGING_SCROLL_Y
};

#define _BALL_SPEED 1//ボールスピード

//スクロール演出関連 SS = StangingScroll
#define _SS_SPEED 2//スクロール演出のスピード
#define _SS_POSITION_Y 105//スクロール演出の固定Y座標（上）



float fSpinBallAngle;//回るボールの角度

//int StagingScrollPosition[x][y] -上1-上2-下1-下2-
int iSSPosition[4][2] = {

	{_DEF_SCREEN_X/2*3,_DEF_SCREEN_Y/2 + _SS_POSITION_Y},
	{_DEF_SCREEN_X/2,_DEF_SCREEN_Y/2 + _SS_POSITION_Y+10},
	{_DEF_SCREEN_X/2*3,_DEF_SCREEN_Y/2 - _SS_POSITION_Y},
	{_DEF_SCREEN_X/2,_DEF_SCREEN_Y/2 - _SS_POSITION_Y+10}};


//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										初期化									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
bool GMAIN_ROUND :: initialize()
{
	if(_IMG_MAX != 0)
	{
		iImage = new int*[_IMG_MAX];
		ipLoadImage(&iImage[_GMAIN_ROUND_RBALL1],"../images/gamemain/UI/RoundBall1.png",10,10,1,514,480);//ラウンドボール1
		ipLoadImage(&iImage[_GMAIN_ROUND_RBALL2],"../images/gamemain/UI/RoundBall2.png",10,10,1,332,331);//ラウンドボール2
		ipLoadImage(&iImage[_GMAIN_ROUND_STANGING1],"../images/gamemain/UI/RoundEffect.png");//ラウンドエフェクト
		ipLoadImage(&iImage[_GMAIN_ROUND_STANGING_SCROLL],"../images/gamemain/UI/RoundScroll.png");//ラウンドエフェクト
	}

	if(_SE_MAX != 0)
	{
		iSe = new int *[_SE_MAX];
	}

	return true;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										解放									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
void GMAIN_ROUND::Release()
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
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										更新									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
bool GMAIN_ROUND::Update()
{
	//動くやつ
	fSpinBallAngle = (fSpinBallAngle <= 360) ? fSpinBallAngle += _BALL_SPEED : fSpinBallAngle -= 360;//背景ボールの回転

	return true;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										描画									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
void GMAIN_ROUND::Render()
{

	//↓↓↓↓↓↓//画像//↓↓↓↓↓↓//
	sscDrawGraph(_DEF_SCREEN_X / 2, _DEF_SCREEN_Y / 2, 1.0, fSpinBallAngle,iImage[_GMAIN_ROUND_RBALL1][0], TRUE, FALSE );//ラウンドボール1
	sscDrawGraph(_DEF_SCREEN_X / 2, _DEF_SCREEN_Y / 2, 1.0, -fSpinBallAngle,iImage[_GMAIN_ROUND_RBALL2][0], TRUE, FALSE );//ラウンドボール2

	for(int i = 0;i < 4;i++){//ラウンド横スクロール
		sscDrawGraph( iSSPosition[i][_STANGING_SCROLL_X],iSSPosition[i][_STANGING_SCROLL_Y], 1.0, 0.0,iImage[_GMAIN_ROUND_STANGING_SCROLL][0],TRUE,FALSE );
		iSSPosition[i][_STANGING_SCROLL_X] = (iSSPosition[i][_STANGING_SCROLL_X] >= -_DEF_SCREEN_X / 2) ? iSSPosition[i][_STANGING_SCROLL_X] -= _SS_SPEED : _DEF_SCREEN_X/2*3;
	}
	//sscDrawGraph(_DEF_SCREEN_X / 2, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_GMAIN_ROUND_REFFECT1][0], TRUE, FALSE );//ラウンドエフェクト



	//↑↑↑↑↑↑//画像//↑↑↑↑↑↑//
}