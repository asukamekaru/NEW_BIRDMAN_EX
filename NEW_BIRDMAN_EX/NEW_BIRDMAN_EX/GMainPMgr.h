#ifndef _G_MAIN_PLAYER_MANAGER_H_
#define _G_MAIN_PLAYER_MANAGER_H_

#include"Base.h"

class PLAYER_WORK:public BASE_WORK{
public:

protected:
	int iCount;
	int iLife;

	int** iImage;
	int** iSe;


public:
	virtual ~PLAYER_WORK(){Release();}

	virtual bool initialize() = 0;
	virtual void Release(){};
	virtual bool Update() = 0;
	virtual void Render(){};
};

class PLAYER_MGR
{

public:
	bool initialize();
	void Release();
	bool Update();
	void Render();
};

extern PLAYER_MGR PlayerManager;


#endif // !_G_MAIN_PLAYER_MANAGER_H_