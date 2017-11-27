#ifndef _MAIN_GROUND_H_
#define _MAIN_GROUND_H_

#include"Base.h"

class GMAIN_ROUND : public BASE_WORK
{

private:

	float fSpinBallAngle;//回るボールの角度

	int iROUND_STANGING;//演出の順番
	int iRoundStaging;
	int iStaging;//演出
	int iStagingTime;//演出の時間

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
};

extern GMAIN_ROUND GMainRound;

#endif //!_MAIN_GROUND_H_