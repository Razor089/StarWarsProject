#ifndef XWINGS_H
#define XWINGS_H
#include <Windows.h>
#include <gl\glew.h>
#include <glut.h>
#include <map>
#include <assimp/aiVector3D.h>
#include <FreeImage.h>
#include "Modello.h"
#include "DeathStar.h"
#include "explosion.h"



class Xwings{
private:
	float x, y, z,dimX, dimY, dimZ;
	int life;
	float angle;
	bool hit, moveRight, moveLeft, moveUp, moveDown, moveForward, moveBack,death, exploded;
	
public:
	Xwings();
	~Xwings();

	void setLive(int n);
	int getLive();
	void setAngle(float x);
	void setDeath(bool flag);
	bool getDeath();
	void movement(float limitRight, float limitLeft, float limitUp, float limitDown, float velocity);
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
	void setRight(bool flag);
	void setLeft(bool flag);
	void setUp(bool flag);
	void setDown(bool flag);
	void setForward(bool flag);
	void setBack(bool flag);
	void loadScene();
	void setHit(bool flag);
	bool isHit();
	void jump(DeathStar *deth1, DeathStar *death2);
	void rolling();
	void goOut();
	void lose(Explosion *explosion);
	void drawSahdow(Modello *model);
	void explosionWall(DeathStar *death1, DeathStar *death2,Explosion *explosion);
	void explosionBorder(Explosion *explosion);
};

#endif