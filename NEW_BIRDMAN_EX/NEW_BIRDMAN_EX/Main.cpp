#include"DxLib.h"
#include"Main.h"
#include"Base.h"
#include"Scene.h"
#include"SceneTitle.h"
#include"SceneGMain.h"
#include"DebugMode.h"

#include<stdio.h>

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										定数									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
#define _MENU_TITLE "BIRDMAN EX C++"

//#define _DEBUG

//入力キーテーブル
const int IKEY_INPUT_TBL[] = 
{
	KEY_INPUT_UP,
	KEY_INPUT_DOWN,
	KEY_INPUT_LEFT,
	KEY_INPUT_RIGHT,
	KEY_INPUT_SPACE,
	KEY_INPUT_BACK,
	KEY_INPUT_1,
	KEY_INPUT_2,
	KEY_INPUT_3,
	KEY_INPUT_4,
	KEY_INPUT_5,
};
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//									グローバル									　 //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
GAME_WORK GameWork;//ゲーム管理
Scene* nowScene = NULL;//現行シーン
Scene* nextScene = NULL;//次のシーン

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//									キー入力更新								　 //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
void vKey_Update()
{
	char Buf[256];
	GetHitKeyStateAll(Buf); 

	int iCnt;

	for(iCnt = 0; iCnt<_NUM_KEY;iCnt++){
		GameWork.iOldKey[iCnt] = GameWork.iNowKey[iCnt];
		GameWork.iNowKey[iCnt] = Buf[IKEY_INPUT_TBL[iCnt]];
	}
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//								キー入力チェック								　 //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
int iKey_Check(int iMode,int iKey)
{	
	int iResult = 0;

	switch (iMode){
	case _KEY_MODE_NOW: //押されている
	default:
		iResult = GameWork.iNowKey[iKey];
		break;
	case _KEY_MODE_TRG://押された瞬間
		if((GameWork.iOldKey[iKey] == 0)&&(GameWork.iNowKey[iKey] == 1))
		{
				iResult = 1;	
		}
		break;
	}
	return(iResult);

}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//									シーン切り替え								　 //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
void vChangeScene(Scene* scene)
{
	if(scene == NULL)return;
	nextScene = scene;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//								イメージ読み込み								　 //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
void ipLoadImage(int** workimg,char* FileName,int AllNum,int XNum,int YNum,int XSize,int YSize)
{
	if(AllNum<=0)return; //分割数のエラー処理

	*workimg = new int[AllNum]; //領域確保

	//分割数に応じて読み込み関数の切り替え
	if(AllNum == 1)*workimg[0] = LoadGraph(FileName);
	else LoadDivGraph(FileName,AllNum,XNum,YNum,XSize,YSize,*workimg);

}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										サウンド								　 //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
void ipLoadSound(int** workSnd,char* FileName)
{
	*workSnd = new int[1];//領域確保
	*workSnd[0] = LoadSoundMem(FileName);//サウンド読み込み関数
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//									画像描画									　 //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
int sscDrawGraph(int x,int y,double mag, double angle,int graph , bool transFlg , bool turnFlg )//x軸,y軸,拡大,角度,画像,透過,反転
{
	//int iw,ih;	
	//GetGraphSize(graph,&iw,&ih);

	x *= (int)((double)_NOW_SCREEN_X / (double)_DEF_SCREEN_X);
	y *= (int)((double)_NOW_SCREEN_Y / (double)_DEF_SCREEN_Y);
	mag *= ((double)_NOW_SCREEN_X / (double)_DEF_SCREEN_X);
	angle = angle * 3.14159265359 / 180;

	return DrawRotaGraph(x, y, mag, angle,graph,transFlg,turnFlg);
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//								デバッグテキスト								　 //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
void DebugText(){
#ifdef _DEBUG
	SetFontSize(10);
	int y = 10;
	//DrawFormatString(5,y,0xFFFFFFFF,"LIFE:%d",0); y+=15;

#endif//_DEBUG
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										メイン									　 //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevinstance,LPSTR ipCmdLine,int nCmdShow)
{
	SetGraphMode(_NOW_SCREEN_X,_NOW_SCREEN_Y,16);
	SetMainWindowText(_MENU_TITLE);
	ChangeWindowMode(TRUE);

	if(DxLib_Init() ==-1)
	{
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);
	SetBackgroundColor(0,0,40);

	vChangeScene(new DEBUG_MODE());

	while(ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//シーン切り替え
		if(nextScene)
		{
			if(nowScene)
			{
				nowScene->Release();
				delete nowScene;
			}
		if(!nextScene->initialize())break;
		nowScene = nextScene;
		nextScene = NULL;
	}


	//メイン処理
	vKey_Update();
	if(nowScene->Update()){
		ClearDrawScreen();

		nowScene->Render();

		DebugText();

		ScreenFlip();
	 }
	}
	DxLib_End();

	return 0;
}