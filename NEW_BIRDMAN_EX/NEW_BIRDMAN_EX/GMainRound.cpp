#include "Main.h"
#include "Base.h"
#include "sceneGMain.h"
#include "GMainRound.h"

#include<math.h>

GMAIN_ROUND GMainRound;

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										定数									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//

enum{//スクロール演出の上下
	_STANGING_SCROLL_X,
	_STANGING_SCROLL_Y
};

enum {//スクロール演出の上下
	_ROUND_SHUTTER,
	_ROUND_ROUND_ANIME,
	_ROUND_FIGHT_ANIME
};

#define _BALL_SPEED 1//ボールスピード

//スクロール演出関連 SS = StangingScroll
#define _SS_SPEED 2//スクロール演出のスピード
#define _SS_POSITION_Y 110//スクロール演出の固定Y座標（上）
#define _SS_POSITION_SPAWN 960//スクロール演出の固定Y座標（上）

//int StagingScrollPosition[x][y] -上1-上2-下1-下2-
int iSSPosition[4][2] = {

	{_DEF_SCREEN_X/2,_DEF_SCREEN_Y/2 - _SS_POSITION_Y},//最初に映るやつ（上）
	{_SS_POSITION_SPAWN,_DEF_SCREEN_Y/2 - _SS_POSITION_Y},//最後に映るやつ（上）
	{_DEF_SCREEN_X/2,_DEF_SCREEN_Y/2 + _SS_POSITION_Y},//最初に映るやつ（下）
	{_SS_POSITION_SPAWN,_DEF_SCREEN_Y/2 + _SS_POSITION_Y}};//最後に映るやつ（下）


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
		ipLoadImage(&iImage[_GMAIN_ROUND_STANGING_SCROLL],"../images/gamemain/UI/RoundScroll.png");//ラウンドエフェクト
		ipLoadImage(&iImage[_GMAIN_ROUND_STANGING_ROUND],"../images/gamemain/UI/RoundStaging.png",69,23,3,640,202);//ラウンド演出
		ipLoadImage(&iImage[_GMAIN_ROUND_STANGING_FIGHT1],"../images/gamemain/UI/RoundFight.png",10,10,1,640,200);//ラウンド演出（文字）
		ipLoadImage(&iImage[_GMAIN_ROUND_STANGING_FIGHT2],"../images/gamemain/UI/RoundEffect.png",9,9,1,636,480);//ラウンド演出（ボール）
	}

	if(_SE_MAX != 0)
	{
		iSe = new int *[_SE_MAX];
	}

	iROUND_STAGING = _ROUND_ROUND_ANIME;//シャッター演出から始める
	//演出1 演出2 演出時間 リセット
	iStaging1 = iStaging2 = iStagingTime = 0;

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



	switch(iROUND_STAGING){
	case _ROUND_SHUTTER:
		break;
	case _ROUND_ROUND_ANIME:

		iStaging1 = CHANGE_STAGING_IMG (iStaging1,22,FALSE);

		if(iStaging1 == 22)iROUND_STAGING = CHANGE_STAGING (120,iROUND_STAGING,_ROUND_FIGHT_ANIME);
		break;
	case _ROUND_FIGHT_ANIME:

		iStaging1 = CHANGE_STAGING_IMG (iStaging1,9,FALSE);
		iStaging2 = CHANGE_STAGING_IMG (iStaging2,8,TRUE);

		if(iStaging1 == 9)iROUND_STAGING = CHANGE_STAGING (120,iROUND_STAGING,_ROUND_ROUND_ANIME);
		break;
	}

	return true;
}

int GMAIN_ROUND::CHANGE_STAGING (int iCHANGETIME,int i,int STAGING){

	static int iStagingTime = 0;

	if(iStagingTime != iCHANGETIME){
		++iStagingTime;//演出の時間を増やす
	}else{
		//指定の演出、シーンに移動
		i = STAGING;
		//演出1 演出2 演出時間 リセット
		iStaging1 = iStaging2 = iStagingTime = 0;

	}
	return i;
}

int GMAIN_ROUND::CHANGE_STAGING_IMG (int iNOWIMGNUM,int iMAXIMGNUM,bool bHIDDEN_IMG){

	if(iNOWIMGNUM != iMAXIMGNUM && iNOWIMGNUM != -1)++iNOWIMGNUM;
	else if(bHIDDEN_IMG)iNOWIMGNUM = -1;//非表示

	return iNOWIMGNUM;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										描画									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
void GMAIN_ROUND::Render()
{

	//↓↓↓↓↓↓//iROUND_STANGINGの影響を受けず描画//↓↓↓↓↓↓//

	//ラウンドボール1
	sscDrawGraph(_DEF_SCREEN_X / 2, _DEF_SCREEN_Y / 2, 1.0, fSpinBallAngle,iImage[_GMAIN_ROUND_RBALL1][0], TRUE, FALSE );
	//ラウンドボール2
	sscDrawGraph(_DEF_SCREEN_X / 2, _DEF_SCREEN_Y / 2, 1.0, -fSpinBallAngle,iImage[_GMAIN_ROUND_RBALL2][0], TRUE, FALSE );
	//ラウンド横スクロール
	for(int i = 0;i < 4;i++){
		sscDrawGraph( iSSPosition[i][_STANGING_SCROLL_X],iSSPosition[i][_STANGING_SCROLL_Y], 1.0, 0.0,iImage[_GMAIN_ROUND_STANGING_SCROLL][0],TRUE,FALSE );

		iSSPosition[i][_STANGING_SCROLL_X] = (iSSPosition[i][_STANGING_SCROLL_X] >= -_DEF_SCREEN_X / 2) ? iSSPosition[i][_STANGING_SCROLL_X] -= _SS_SPEED : _SS_POSITION_SPAWN - 4;
	}
	//↑↑↑↑↑↑//iROUND_STANGINGの影響を受けず描画//↑↑↑↑↑↑//


	switch(iROUND_STAGING){
	case _ROUND_SHUTTER:

		break;
	case _ROUND_ROUND_ANIME:
		sscDrawGraph(_DEF_SCREEN_X / 2, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_GMAIN_ROUND_STANGING_ROUND][iStaging1 + 2 * 23], TRUE, FALSE );//iStaging + (0～2の数字で変わる) * 23
		break;

	case _ROUND_FIGHT_ANIME:
		sscDrawGraph(_DEF_SCREEN_X / 2, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_GMAIN_ROUND_STANGING_FIGHT1][iStaging1], TRUE, FALSE );
		sscDrawGraph(_DEF_SCREEN_X / 2, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_GMAIN_ROUND_STANGING_FIGHT2][iStaging2], TRUE, FALSE );
		break;
	}

	DrawFormatString( 0 , 0 , 0xFFFFFF ,"%d" , iStaging1) ;

}