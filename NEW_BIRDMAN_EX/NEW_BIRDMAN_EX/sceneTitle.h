#ifndef _SCENE_TITLE_H_
#define _SCENE_TITLE_H_

#include"Scene.h"

class SCENE_TITLE : public Scene
{

private:
	enum{
		_SCENE_TITLE_LOGO,
		_SCENE_TITLE_SELECT
	};

	enum{
		_IMG_TITLE_YLSHUTTER,//黄シャッター（左）
		_IMG_TITLE_YRSHUTTER,//黄シャッター（右）
		_IMG_TITLE_RLSHUTTER,//赤シャッター（左）
		_IMG_TITLE_RRSHUTTER,//赤シャッター（右）
		_IMG_MAX
	};

	enum{
		_BGM_TITLE,
		_SE_MAX
	};

protected:

	int iNowTitleMode;//タイトルシーンの描画画面(1,ロゴ画面 2,選択画面)

public:
	bool initialize();
	void Release();
	bool Update();
	void Shutter(bool& shutterFlg,bool& shutterMoveFlg,int& shutterX,int& shutterTime,int shutterUIX);
	void Render();
};

#endif //!_SCENE_TITLE_H_