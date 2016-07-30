#ifndef TIEFIGHTER_H
#define TIEFIGHTER_H
#include <Windows.h>
#include <gl\glew.h>
#include <glut.h>
#include <map>
#include <assimp/aiVector3D.h>
#include <FreeImage.h>
#include "Modello.h"
#include "DeathStar.h"
#include "explosion.h"


class TieFighter{
private:
	float x, y, z,dimX, dimY, dimZ;	
	int life;
	float angle, speed;
	bool hit, moveRight, moveLeft, moveUp, moveDown, moveForward, moveBack, death, exploded;

public:
	TieFighter();
	~TieFighter();
	void setLive(int n);
	int getLive();
	void setSpeed(float v);
	float getSpeed();
	void movement(float limitRight, float limitLeft, float limitUp, float limitDown, float velocity,float limitForward,float limitBack);
	void draw(Modello *model);
	void setX(float posX);
	void setY(float posY);
	void setZ(float posZ);
	void setDimX(float dimX0);
	void setDimY(float dimY0);
	void setDimZ(float dimZ0);
	void setHit(bool flag);
	void setAngle(float spin);
	float getX();
	float getY();
	float getZ();
	float getDimX();
	float getDimY();
	float getDimZ();
	float getAngle();
	void setRight(bool flag);
	void setLeft(bool flag);
	void setUp(bool flag);
	void setDown(bool flag);
	void setForward(bool flag);
	void setBack(bool flag);
	void loadScene();
	void incoming(DeathStar *death1, DeathStar *death2);
	void reset(float posX, float posY, float posZ, Explosion *explosion);
	void rotate(float rotation);
	void destroy();
	bool getLeft();
	bool getRight();
	void setDeath(bool flag);
	bool getDeath();
	void explodeDarth(Explosion *explosion);
	void moveDarth(float avanti,float dietro,float angolo);
	void come(float x);
	void stopDarthVader(float x, float y);
};

#endif

