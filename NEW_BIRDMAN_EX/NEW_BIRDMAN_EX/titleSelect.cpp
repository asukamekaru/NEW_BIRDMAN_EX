#include "Main.h"
#include "Base.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "titleSelect.h"

TITLE_SELECT TitleSelect;

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										定数									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//

#define _BGBALL_SPEED 1
#define _ARROW_P1Y 120
#define _ARROW_P2Y 220
#define _ARROW_SPEED 20

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										初期化									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
bool TITLE_SELECT :: initialize()
{
	fSpinBGBall = 0.0;
	fArrowX = _DEF_SCREEN_X;

	if(_IMG_MAX != 0)
	{
		iImage = new int*[_IMG_MAX];

		ipLoadImage(&iImage[_TITLE_SELECT_BG],"../images/title/select/select_bg.png");//背景
		ipLoadImage(&iImage[_TITLE_SELECT_BGNET],"../images/title/select/select_background_net.png");//背景ネット
		ipLoadImage(&iImage[_TITLE_SELECT_BGBALL1],"../images/title/select/select_backball1.png");//背景ボール1
		ipLoadImage(&iImage[_TITLE_SELECT_BGBALL2],"../images/title/select/select_backball2.png");//背景ボール1
		ipLoadImage(&iImage[_TITLE_SELECT_CHARSELECT],"../images/title/select/select_char_select.png",2,2,1,319,400);//選択1,2
		ipLoadImage(&iImage[_TITLE_SELECT_ARROW],"../images/title/select/select_arrow.png",2,1,2,240,80);//矢印P1P2
		ipLoadImage(&iImage[_TITLE_SELECT_UPPERTXT],"../images/title/select/stage_upper_txt.png",2,1,2,640,40);//アッパー文字1,2
		ipLoadImage(&iImage[_TITLE_SELECT_FOOTERTXT],"../images/title/select/select_footer_txt.png",2,1,2,560,40);//フッター文字1,2
		ipLoadImage(&iImage[_TITLE_SELECT_CHARFACES],"../images/title/select/select_charaselect.png");//キャラクター顔
		ipLoadImage(&iImage[_TITLE_SELECT_CHARBODYS],"../images/title/select/select_chars.png");//キャラクター全体
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
void TITLE_SELECT::Release()
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
bool TITLE_SELECT::Update()
{
	//↓↓↓↓↓↓//動くやつのスクリプト//↓↓↓↓↓↓//
	fSpinBGBall = (fSpinBGBall <= 360) ? fSpinBGBall +=_BGBALL_SPEED : fSpinBGBall -= 360;//背景ボールの回転
	if(fArrowX > 0)fArrowX -= _ARROW_SPEED;



	return true;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										描画									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
void TITLE_SELECT::Render()
{
	//↓↓↓↓↓↓//画像//↓↓↓↓↓↓//

	//背景
	sscDrawGraph(_DEF_SCREEN_X / 2, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_TITLE_SELECT_BG][0], FALSE, FALSE );//背景
	sscDrawGraph(_DEF_SCREEN_X / 2, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_TITLE_SELECT_BGNET][0], TRUE, FALSE );//背景網
	sscDrawGraph(_DEF_SCREEN_X / 2, _DEF_SCREEN_Y / 2, 1.0, fSpinBGBall,iImage[_TITLE_SELECT_BGBALL1][0], TRUE, FALSE );//背景ボール1
	sscDrawGraph(_DEF_SCREEN_X / 2, _DEF_SCREEN_Y / 2, 1.0, -fSpinBGBall,iImage[_TITLE_SELECT_BGBALL2][0], TRUE, FALSE );//背景ボール2

	//アッパー文字
	sscDrawGraph(_DEF_SCREEN_X / 2, 20, 1.0, 0.0,iImage[_TITLE_SELECT_UPPERTXT][0], FALSE, FALSE );//アッパー文字

	//フッター文字
	sscDrawGraph(_DEF_SCREEN_X / 2, _DEF_SCREEN_Y -20, 1.0, 0.0,iImage[_TITLE_SELECT_FOOTERTXT][0], TRUE, FALSE );//フッター文字

	//キャラ決定のUI
	sscDrawGraph(_DEF_SCREEN_X / 2 - 160, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_TITLE_SELECT_CHARSELECT][0], TRUE, FALSE );//キャラ決定時に出るやつ左
	sscDrawGraph(_DEF_SCREEN_X / 2 + 160, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_TITLE_SELECT_CHARSELECT][1], TRUE, FALSE );//キャラ決定時に出るやつ右


	//矢印
	sscDrawGraph(_DEF_SCREEN_X / 2 + (int)fArrowX, _ARROW_P1Y, 1.0, 0.0,iImage[_TITLE_SELECT_ARROW][0], TRUE, FALSE );//矢印P1
	sscDrawGraph(_DEF_SCREEN_X / 2 - (int)fArrowX, _ARROW_P2Y, 1.0, 0.0,iImage[_TITLE_SELECT_ARROW][1], TRUE, FALSE );//矢印P2

	//キャラクターの画像
	sscDrawGraph(_DEF_SCREEN_X / 2, _DEF_SCREEN_Y / 2 + 100, 1.0, 0.0,iImage[_TITLE_SELECT_CHARFACES][0], FALSE, FALSE );



	//↑↑↑↑↑↑//画像//↑↑↑↑↑↑//

	DrawFormatString(0,0,_COLOR_WHITE,"%f",fSpinBGBall);
	DrawFormatString(0,10,_COLOR_WHITE,"%f",fArrowX);
}