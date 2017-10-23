#ifndef _SCENE_H_
#define _SCENE_H_

class Scene
{
protected:
	int **iImage;
	int **iSe;

public:
	virtual bool initialize() = 0;
	virtual void Release() = 0;
	virtual bool Update() = 0;
	virtual void Render() = 0;
};

#endif//!_SCENE_H_