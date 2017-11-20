#ifndef _BASE_H_
#define _BASE_H_

class BASE_WORK{
protected:




public:
	BASE_WORK()
	{
		//ZeroMemory(this,sizeof(BASE_WORK));
	}

	virtual bool Update() = 0;
	virtual void Render(){};
};

#endif //!_BASE_H_
