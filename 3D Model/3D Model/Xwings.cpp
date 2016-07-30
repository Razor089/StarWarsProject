#include <Windows.h>
#include <gl\glew.h>
#include <assimp\assimp.h>
#include <assimp\aiPostProcess.h>
#include <assimp\aiScene.h>
#include <FreeImage.h>
#include <iostream>
#include "Xwings.h"
#include "explosion.h"


Xwings::Xwings(){
	
	this->x = 0;
	this->y = 0;
	this->z = 0;
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
	this->life = 5;
	this->death = false;
	this->angle = 0;
	this->exploded = false;
}

Xwings::~Xwings(){

}

int Xwings::getLive(){
	return this->life;
}

void Xwings::movement(float limitRight, float limitLeft, float limitUp, float limitDown, float velocity){
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
		if(this->getY() < limitUp){
			this->setY(this->getY() + velocity);
		}
	}
	if(this->moveForward){
		this->setZ(this->getZ() + velocity);
	}
	if(this->moveBack){
		this->setZ(this->getZ() - velocity);
	}
}

void Xwings::setX(float posX){
	this->x = posX;
}

void Xwings::setY(float posY){
	this->y = posY;
}

void Xwings::setZ(float posZ){
	this->z = posZ;
}

float Xwings::getX(){
	return this->x;
}

float Xwings::getY(){
	return this->y;
}

float Xwings::getZ(){
	return this->z;
}

void Xwings::setLeft(bool flag){
	this->moveLeft = flag;
}

void Xwings::setRight(bool flag){
	this->moveRight = flag;
}

void Xwings::setDown(bool flag){
	this->moveDown = flag;
}

void Xwings::setUp(bool flag){
	this->moveUp = flag;
}


void Xwings::goOut(){
	this->moveUp = true;
	if(this->angle > -50){
		this->angle -= 0.5;
	}
		this->moveRight = true;
		this->moveBack = true;
		this->moveLeft = false;
		this->moveDown = false;
	}


void Xwings::setAngle(float x){
	this->angle = x;
}

void Xwings::draw(Modello *model){
	if(this->death == false){
		glTranslated(this->getX(), this->getY(), this->getZ());
		glScaled(dimX, dimY, dimZ);
		glEnable(GL_LIGHTING);
		glEnable(GL_NORMALIZE);
		rolling();
		glRotatef(angle,-1,1,0);
		model->prepare(1);
		glDisable(GL_NORMALIZE);
		glDisable(GL_LIGHTING);
	}
}

void Xwings::drawSahdow(Modello *model){
	if(this->death == false){
		glTranslated(this->getX(), -3.6, this->getZ());
		glScaled(1, 0.125, 1);
		glScaled(dimX, dimY, dimZ);
		glRotatef(angle,0,1,0);
		glDisable(GL_LIGHTING);
		glDisable(GL_NORMALIZE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_ONE_MINUS_DST_COLOR);
		model->prepare(0);
		glDisable(GL_BLEND);
		glEnable(GL_NORMALIZE);
		glEnable(GL_LIGHTING);
	}
}

void Xwings::setDimX(float dimX0){
	this->dimX = dimX0;
}

void Xwings::setDimY(float dimY0){
	this->dimY = dimY0;
}

void Xwings::setDimZ(float dimZ0){
	this->dimZ = dimZ0;
}

float Xwings::getDimX(){
	return this->dimX;
}

float Xwings::getDimY(){
	return this->dimY;
}

float Xwings::getDimZ(){
	return this->dimZ;
}

void Xwings::setForward(bool flag){
	this->moveForward = flag;
}

void Xwings::setBack(bool flag){
	this->moveBack = flag;
}


void Xwings::jump(DeathStar *death1, DeathStar *death2){

	if(death1->getZ() == 70 || death2->getZ() == 70){
		this->moveUp = true;
		this->moveDown = false;
	}
	if(death1->getZ() >= 85 || death2->getZ() >= 85){
		this->moveUp = false;
		this->moveDown = true;
	}
}

void Xwings::rolling(){

	if(this->moveLeft){
		glRotatef(20,0,0,1);
	}
	if(this->moveRight){
		glRotatef(-20,0,0,1);
	}

}

void Xwings::setLive(int n){
	this->life= n;
}


void Xwings::lose(Explosion *explosion){
	if(this->getLive() == 0){
		this->death=true;
		if(!exploded){
			this->exploded = true;
			explosion->createParticleSystem(this->getX(), this->getY(), this->getZ());
		}
	}
}

void Xwings::setDeath(bool flag){
	this->death = flag;
}

bool Xwings::getDeath(){
	return this->death;
}

void Xwings::setHit(bool flag){
	this->hit = flag;
}

bool Xwings::isHit(){
	return this->hit;
}


void Xwings::explosionWall(DeathStar *death1, DeathStar *death2,Explosion *explosion){
	if(death1->getZ() == 80 || death2->getZ() == 80){
		if(this->y <= -1.20){	
			if(!exploded){
				this->exploded = true;
				explosion->createParticleSystem(this->getX(), this->getY(), this->getZ() + 0.5);	
			}
			this->setDeath(true);
		}
	}
}

void  Xwings::explosionBorder(Explosion *explosion){
	if(this->y < -1.20){
		if((this->x <= - 1.99)|| (this->x >= 1.99)){
			if(!exploded){
				this->exploded = true;
				explosion->createParticleSystem(this->getX(), this->getY(), this->getZ() + 0.5);	
			}
			this->setDeath(true);
		}
	}
	
}