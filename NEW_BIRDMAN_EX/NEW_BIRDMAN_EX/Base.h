#ifndef _BASE_H_
#define _BASE_H_

class BASE_WORK{
protected:
	int iType;
	int iState;
	int iStep;
	float fPosX,fPosY;
	float fVecX,fVecY;
	bool bNoDmg;
	int iNoDmgTimer;

public:
	BASE_WORK()
	{
		//ZeroMemory(this,sizeof(BASE_WORK));
	}

	virtual bool Update() = 0;
	virtual void Render(){};
	virtual void SetDamage(int dmg) = 0;

	float getPosX(){return fPosX;}
	float getPosY(){return fPosY;}
	bool getNoDmg(){return bNoDmg;}

	void setPosX(float x){fPosX = x;}
	void setPosY(float y){fPosY = y;}
	void setVec(float vx,float vy){fVecX = vx;fVecY = vy;}
	void setNoDmgTimer(int t){iNoDmgTimer = t; bNoDmg = true;}
};


#endif //!_BASE_H_
