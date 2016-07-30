#ifndef DEATHSTAR_H
#define DEATHSTAR_H
#include <Windows.h>
#include <glut.h>
#include <map>
#include <assimp/aiVector3D.h>
#include <FreeImage.h>
#include "Modello.h"

class DeathStar{

private:
	float x, y, z,dimX, dimY, dimZ, speed;
	bool moveForward, moveBack;

public:
	DeathStar();
	~DeathStar();
	void movement(float velocity);
	void draw(Modello *model);
	void setX(float posX);
	void setY(float posY);
	void setZ(float posZ);
	void setDimX(float dimX0);
	void setDimY(float dimY0);
	void setDimZ(float dimZ0);
	float getX();
	float getY();
	float getZ();
	float getDimX();
	float getDimY();
	float getDimZ();
	void setForward(bool flag);
	void setBack(bool flag);
	void loadScene();
	void controlPlane();
	void setSpeed(float sp);
	float getSpeed();
};

#endif