#ifndef _MAIN_GROUND_H_
#define _MAIN_GROUND_H_

#include"Base.h"

class GMAIN_ROUND : public BASE_WORK
{

private:

	enum{
		_GMAIN_ROUND_RBALL1,//���E���h�{�[��1
		_GMAIN_ROUND_RBALL2,//���E���h�{�[��2
		_GMAIN_ROUND_REFFECT1,//���E���h�G�t�F�N�g

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