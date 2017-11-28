#ifndef _MAIN_GROUND_H_
#define _MAIN_GROUND_H_

#include"Base.h"

class GMAIN_ROUND : public BASE_WORK
{

private:

	int iRoundStaging;
	int iStaging1;//演出1
	int iStaging2;//演出2
	int iStagingTime;//演出の時間
	int iROUND_STAGING;//演出の順番

	float fSpinBallAngle;//回るボールの角度

	enum{
		_GMAIN_ROUND_RBALL1,//ラウンドボール1
		_GMAIN_ROUND_RBALL2,//ラウンドボール2
		_GMAIN_ROUND_STANGING_SCROLL,//ラウンドスクロール演出
		_GMAIN_ROUND_STANGING_ROUND,//ラウンド1演出
		_GMAIN_ROUND_STANGING_FIGHT1,//ファイト!演出
		_GMAIN_ROUND_STANGING_FIGHT2,//ラウンドファイト演出
		_IMG_MAX
	};

	enum{
		_SE_MAX
	};

protected:

	int** iImage;
	int** iSe;

public:
	bool initialize();
	void Release();
	bool Update();
	void Render();
	int CHANGE_STAGING (int iCHANGETIME,int i,int STAGING);
	int CHANGE_STAGING_IMG (int A,int IMGNUM,bool bHIDDEN_IMG);
};

extern GMAIN_ROUND GMainRound;

#endif //!_MAIN_GROUND_H_