#include <Windows.h>
#include <gl\glew.h>
#include <assimp\assimp.h>
#include <assimp\aiPostProcess.h>
#include <assimp\aiScene.h>
#include <FreeImage.h>
#include <iostream>
#include "TieFighter.h"

TieFighter::TieFighter(){
	this->life = 1;
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->angle = 0;
	this->hit = false;
	this->moveLeft = false;
	this->moveRight = false;
	this->moveDown = false;
	this->moveUp = false;
	this->moveBack = false;
	this->moveForward = false;
	this->dimX = 1;
	this->dimY = 1;
	this->dimZ = 1;
	this->death = false;
	this->speed = 0;
	this->exploded = false;
}

TieFighter::~TieFighter(){

}

void TieFighter::movement(float limitRight, float limitLeft, float limitUp, float limitDown, float velocity,float limitForward, float limitBack){
	if(this->moveLeft){
		if(this->getX() > limitLeft){
			this->setX(this->getX() - velocity);
		}
	}
	if(this->moveRight){
		if(this->getX() < limitRight){
			this->setX(this->getX() + velocity);
		}
	}
	if(this->moveDown){
		if(this->getY() > limitDown){
			this->setY(this->getY() - velocity);
		}
	}
	if(this->moveUp){
		this->setY(this->getY() + velocity);
	}
	if(this->moveForward){
		if(this->getZ() < limitForward){
			this->setZ(this->getZ() + velocity);
		}
	}
	if(this->moveBack){
		if(this->getZ() > limitBack){
			this->setZ(this->getZ() - velocity);
		}
	}
}

void TieFighter::setX(float posX){
	this->x = posX;
}

void TieFighter::setY(float posY){
	this->y = posY;
}

void TieFighter::setZ(float posZ){
	this->z = posZ;
}

float TieFighter::getX(){
	return this->x;
}

float TieFighter::getY(){
	return this->y;
}

float TieFighter::getZ(){
	return this->z;
}

void TieFighter::setLeft(bool flag){
	this->moveLeft = flag;
}

void TieFighter::setRight(bool flag){
	this->moveRight = flag;
}

void TieFighter::setDown(bool flag){
	this->moveDown = flag;
}

void TieFighter::setUp(bool flag){
	this->moveUp = flag;
}

void TieFighter::draw(Modello *model){
	if(!this->hit || !this->death){
		glTranslated(this->getX(), this->getY(), this->getZ());
		glRotated(this->getAngle(), 0, 1, 0);
		glScaled(dimX, dimY, dimZ);
		glEnable(GL_NORMALIZE);
		model->prepare(1);
		glDisable(GL_NORMALIZE);
	}
}

void TieFighter::setAngle(float spin){
	this->angle = spin;
}

float TieFighter::getAngle(){
	return this->angle;
}

void TieFighter::setDimX(float dimX0){
	this->dimX = dimX0;
}

void TieFighter::setDimY(float dimY0){
	this->dimY = dimY0;
}

void TieFighter::setDimZ(float dimZ0){
	this->dimZ = dimZ0;
}

float TieFighter::getDimX(){
	return this->dimX;
}

float TieFighter::getDimY(){
	return this->dimY;
}

float TieFighter::getDimZ(){
	return this->dimZ;
}

void TieFighter::setHit(bool flag){
	this->hit = flag;
}

void TieFighter::setForward(bool flag){
	this->moveForward = flag;
}

void TieFighter::setBack(bool flag){
	this->moveBack = flag;
}

void TieFighter::incoming(DeathStar *death1, DeathStar *death2){
	if((death1->getZ() == 0 || death2->getZ() == 0) && (this->getY() >= 0.5)){
		this->moveLeft = true;
		this->moveDown = true;
		this->moveBack = true;
	}
	if(this->getY() <= 0.5){
		this->moveDown = false;
		if(this->getX() >= 2){
			this->moveRight = false;
			this->moveLeft = true;
		}
		if(this->getX() <= -2){
			this->moveLeft = false;
			this->moveRight = true;
		}
	}
}

int TieFighter::getLive(){
	return this->life;
}

void TieFighter::setLive(int n){
	this->life = n;
}

void TieFighter::reset(float posX, float posY, float posZ,Explosion *explosion){
	if(this->hit){
		if(!exploded){
			this->exploded = true;
			explosion->createParticleSystem(this->getX(), this->getY(), this->getZ());	
		}
		this->setAngle(0);
		this->setX(posX);
		this->setY(posY);
		this->setZ(posZ);
		this->hit = false;
		this->exploded = false;
	}
}

//stop when is death
void TieFighter::destroy(){
	if(this->life < 1){
		this->death = true;
		this->moveBack = false;
		this->moveLeft = false;
		this->moveDown = false;
		this->moveRight = false;
		
	}
}

void TieFighter::explodeDarth(Explosion *explosion){
	if(this->getLive() < 1){
		if(!exploded){
			explosion->createParticleSystem(this->getX(), this->getY(), this->getZ());
			this->exploded = true;
		}
	}
}

void TieFighter::setDeath(bool flag){
	this->death = flag;
}
bool TieFighter::getDeath(){
	return this->death;
}

void TieFighter::moveDarth(float avanti,float dietro,float angolo){
	if((this->getX() >= avanti)){
		this->moveRight = false;
		this->moveLeft = true;
	}
	if((this->getX() <= dietro)){
		this->moveRight = true;
		this->moveLeft = false;
		this->setAngle(angolo);
	}
}

void TieFighter::come(float x){
	if(this->x == x){
		this->moveRight = false;
		this->moveLeft = false;
		this->angle = 0;
		this->moveForward = true;
		this->moveDown = true;
		this->speed = 0.1;
	}
}

void TieFighter::stopDarthVader(float x, float y){
	if(this->x == x && this->y == y){
		this->moveRight = false;
		this->moveLeft = false;
		this->angle = 0;
	}
}

float TieFighter::getSpeed(){
	return this->speed;
	}


void TieFighter::setSpeed(float v){
	this->speed = v;
}

bool TieFighter::getLeft(){
	return this->moveLeft;
}

bool TieFighter::getRight(){
	return this->moveRight;
}