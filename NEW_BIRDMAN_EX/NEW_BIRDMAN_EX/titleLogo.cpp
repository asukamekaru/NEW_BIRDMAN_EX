#include "Main.h"
#include "Base.h"
#include "SceneTitle.h"
#include "titleLogo.h"

TITLE_LOGO TitleLogo;

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										定数									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//

#define _IMG_TITLE_LOGO_Y (160)
#define _UI_SCROLL_MAX	  (6)

struct UI_SCROLL{
	int	x;
	int	y;
	const double size;
	const int radi;
	const int speed;
	const int rand;
};

struct UI_SCROLL ui_scroll[_UI_SCROLL_MAX] = //Xの位置,Yの位置,画像の大きさ,角度,動く速度,初期化の位置
{
	{ 500,  80, 0.2,  0,  1, 120},
	{ 380, 400, 0.6,  0, -2,  72},
	{  30, 300, 1.0,  0,  3,  36},
	{ 500,  80, 0.2, 90,  2, 120},
	{ 380, 400, 0.6, 90,  3,  60},
	{  30, 300, 1.0, 90, -4,  15}
};

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										初期化									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
bool TITLE_LOGO :: initialize()
{
	if(_IMG_MAX != 0)
	{
		iImage = new int*[_IMG_MAX];

		ipLoadImage(&iImage[_IMG_TITLE_BG],"../images/title/title_bg.png");//背景
		ipLoadImage(&iImage[_IMG_TITLE_PtS],"../images/title/title_pts.png");//文字"PUSH TO SPACE"
		ipLoadImage(&iImage[_IMG_TITLE_LOGO],"../images/title/title_logo.png");//ロゴ
		ipLoadImage(&iImage[_IMG_TITLE_SCROLL],"../images/title/title_scroll.png");//動く四角いやつ
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
void TITLE_LOGO::Release()
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
bool TITLE_LOGO::Update()
{
	//↓↓↓↓↓↓//スクロールUIの移動処理//↓↓↓↓↓↓//
	for(int i = 0; i < _UI_SCROLL_MAX; i++){

		if(ui_scroll[i].x - _DEF_SCREEN_X > _DEF_SCREEN_X){
			ui_scroll[i].x = - _DEF_SCREEN_X;
			ui_scroll[i].y = GetRand(_DEF_SCREEN_X - ui_scroll[i].rand);
		}

		if(ui_scroll[i].x + _DEF_SCREEN_X < 0){
			ui_scroll[i].x = _DEF_SCREEN_X * 2;
			ui_scroll[i].y = GetRand(_DEF_SCREEN_X - ui_scroll[i].rand);
		}

		if(ui_scroll[i].y - _DEF_SCREEN_Y > _DEF_SCREEN_X){
			ui_scroll[i].x = GetRand(_DEF_SCREEN_Y - ui_scroll[i].rand);
			ui_scroll[i].y = - _DEF_SCREEN_Y;
		}

		if(ui_scroll[i].y + _DEF_SCREEN_Y < 0){
			ui_scroll[i].x = GetRand(_DEF_SCREEN_Y - ui_scroll[i].rand);
			ui_scroll[i].y = _DEF_SCREEN_Y * 2;
		}

		ui_scroll[i].x += (i < 3) ?	 ui_scroll[i].speed : 0;
		ui_scroll[i].y += (i < 3) ?  0 : ui_scroll[i].speed;

	}
	//↑↑↑↑↑↑//スクロールUIの移動処理//↑↑↑↑↑↑//
	return true;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										描画									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
void TITLE_LOGO::Render()
{
	static int icnt = 0;
	icnt++;

	//↓↓↓↓↓↓//画像//↓↓↓↓↓↓//

	//背景
	sscDrawGraph(_DEF_SCREEN_X / 2, _DEF_SCREEN_Y / 2, 1.0, 0.0,iImage[_IMG_TITLE_BG][0], FALSE, FALSE );

	//動く四角いやつ
	for(int i = 0; i < _UI_SCROLL_MAX; i++)
		sscDrawGraph(ui_scroll[i].x, ui_scroll[i].y, ui_scroll[i].size, ui_scroll[i].radi,iImage[_IMG_TITLE_SCROLL][0], TRUE, FALSE );

	//ロゴ
	sscDrawGraph(_DEF_SCREEN_X / 2, _IMG_TITLE_LOGO_Y, 1.0, 0.0,iImage[_IMG_TITLE_LOGO][0], TRUE, FALSE );

	//文字"PUSH TO SPACE"
	if(icnt & 0x30)sscDrawGraph(320, 360, 1.0, 0.0,iImage[_IMG_TITLE_PtS][0], TRUE, FALSE );

	//↑↑↑↑↑↑//画像//↑↑↑↑↑↑//
}