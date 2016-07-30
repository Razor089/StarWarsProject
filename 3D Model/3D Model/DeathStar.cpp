#include <assimp\assimp.h>
#include <assimp\aiPostProcess.h>
#include <assimp\aiScene.h>
#include <FreeImage.h>
#include <iostream>
#include "DeathStar.h"

DeathStar::DeathStar(){
	
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->moveBack = false;
	this->moveForward = false;
	this->dimX = 1;
	this->dimY = 1;
	this->dimZ = 1;
}

DeathStar::~DeathStar(){

}

void DeathStar::movement(float velocity){
	if(this->moveForward){
		this->setZ(this->getZ() + velocity);
	}
	if(this->moveBack){
		this->setZ(this->getZ() - velocity);
	}
}

void DeathStar::setX(float posX){
	this->x = posX;
}

void DeathStar::setY(float posY){
	this->y = posY;
}

void DeathStar::setZ(float posZ){
	this->z = posZ;
}

float DeathStar::getX(){
	return this->x;
}

float DeathStar::getY(){
	return this->y;
}

float DeathStar::getZ(){
	return this->z;
}

void DeathStar::draw(Modello *model){
	glTranslated(this->getX(), this->getY(), this->getZ());
	glScaled(dimX, dimY, dimZ);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);	
	model->prepare(1);
	glDisable(GL_NORMALIZE);
	glDisable(GL_LIGHTING);
}

void DeathStar::setDimX(float dimX0){
	this->dimX = dimX0;
}

void DeathStar::setDimY(float dimY0){
	this->dimY = dimY0;
}

void DeathStar::setDimZ(float dimZ0){
	this->dimZ = dimZ0;
}

float DeathStar::getDimX(){
	return this->dimX;
}

float DeathStar::getDimY(){
	return this->dimY;
}

float DeathStar::getDimZ(){
	return this->dimZ;
}

void DeathStar::setSpeed(float sp){
	this->speed= sp;
}

float DeathStar::getSpeed(){
	return this->speed;
}

void DeathStar::controlPlane(){
	if(this->z > 140){
		this->z = -218;
	}
}

void DeathStar::setForward(bool flag){
	this->moveForward = flag;
}

void DeathStar::setBack(bool flag){
	this->moveBack = flag;
}