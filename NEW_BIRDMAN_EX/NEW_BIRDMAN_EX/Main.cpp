#include"DxLib.h"
#include"Main.h"
#include"Base.h"
#include"Scene.h"
#include"SceneTitle.h"
#include"SceneGMain.h"
#include"DebugMode.h"

#include<stdio.h>

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										�萔									   //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
#define _MENU_TITLE "BIRDMAN EX C++"

//#define _DEBUG

//���̓L�[�e�[�u��
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
//									�O���[�o��									�@ //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
GAME_WORK GameWork;//�Q�[���Ǘ�
Scene* nowScene = NULL;//���s�V�[��
Scene* nextScene = NULL;//���̃V�[��

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//									�L�[���͍X�V								�@ //
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
//								�L�[���̓`�F�b�N								�@ //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
int iKey_Check(int iMode,int iKey)
{	
	int iResult = 0;

	switch (iMode){
	case _KEY_MODE_NOW: //������Ă���
	default:
		iResult = GameWork.iNowKey[iKey];
		break;
	case _KEY_MODE_TRG://�����ꂽ�u��
		if((GameWork.iOldKey[iKey] == 0)&&(GameWork.iNowKey[iKey] == 1))
		{
				iResult = 1;	
		}
		break;
	}
	return(iResult);

}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//									�V�[���؂�ւ�								�@ //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
void vChangeScene(Scene* scene)
{
	if(scene == NULL)return;
	nextScene = scene;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//								�C���[�W�ǂݍ���								�@ //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
void ipLoadImage(int** workimg,char* FileName,int AllNum,int XNum,int YNum,int XSize,int YSize)
{
	if(AllNum<=0)return; //�������̃G���[����

	*workimg = new int[AllNum]; //�̈�m��

	//�������ɉ����ēǂݍ��݊֐��̐؂�ւ�
	if(AllNum == 1)*workimg[0] = LoadGraph(FileName);
	else LoadDivGraph(FileName,AllNum,XNum,YNum,XSize,YSize,*workimg);

}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										�T�E���h								�@ //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
void ipLoadSound(int** workSnd,char* FileName)
{
	*workSnd = new int[1];//�̈�m��
	*workSnd[0] = LoadSoundMem(FileName);//�T�E���h�ǂݍ��݊֐�
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//									�摜�`��									�@ //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
int sscDrawGraph(int x,int y,double mag, double angle,int graph , bool transFlg , bool turnFlg )//x��,y��,�g��,�p�x,�摜,����,���]
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
//								�f�o�b�O�e�L�X�g								�@ //
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
void DebugText(){
#ifdef _DEBUG
	SetFontSize(10);
	int y = 10;
	//DrawFormatString(5,y,0xFFFFFFFF,"LIFE:%d",0); y+=15;

#endif//_DEBUG
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
//										���C��									�@ //
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
		//�V�[���؂�ւ�
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


	//���C������
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