#ifndef _MAIN_H_
#define _MAIN_H_

#include"DxLib.h"
using namespace std;

class Scene;


//
//定数
//
#define _PI (3.141592653589f)
#define _DEF_SCREEN_X (640)
#define _DEF_SCREEN_Y (480)

#define _NOW_SCREEN_X (640)//S320 M640 L860
#define _NOW_SCREEN_Y (480)//S240 M480 L720

#define _FONTSIZE_S (16)
#define _FONTSIZE_M (32)
#define _FONTSIZE_L (64)

#define _COLOR_WHITE (0xFFFFFF)
#define _COLOR_RED (0xFF0000)
enum {
	_GAME_START_PLAY,
	_GAME_START_OVER,
	_GAME_START_CLEAR,
};

enum{
	_KEY_MODE_NOW,
	_KEY_MODE_TRG,

	_NUM_KEY_MODE,
};

enum{
	_KEY_UP,
	_KEY_DOWN,
	_KEY_LEFT,
	_KEY_RIGHT,
	_KEY_SPACE,
	_KEY_1,
	_KEY_2,
	_KEY_3,
	_KEY_4,
	_KEY_5,

	_NUM_KEY,
};

enum{
	_ALIGN_LEFT,
	_ALIGN_CENTER,
	_ALIGN_RIGHT,
};

//
//構造体
//

typedef struct{
	int iState;
	
	int iNowKey[_NUM_KEY];
	int iOldKey[_NUM_KEY];

}GAME_WORK;

//
//グローバル
//
extern GAME_WORK stGameW;

//
//関数宣言
//
void vKey_Update();
int iKey_Check(int iMode,int iKey);
int sscDrawGraph(int x,int y,double mag, double angle,int graph , bool transFlg , bool turnFlg );

void vChangeScene(Scene* scene);
void ipLoadImage(int** working,char* FileName, int AllNum = 1, int XNum = 0,int YNum = 0, int XSize = 0, int YSize = 0);
void ipLoadSound(int** workSnd,char* FileName);

#endif //_MAIN_H_