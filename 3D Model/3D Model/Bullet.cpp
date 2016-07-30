#include <Windows.h>
#include <gl\glew.h>
#include <glut.h>
#include <iostream>
#include "Bullet.h"
#include "TieFighter.h"

Bullet::Bullet(){
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->shooted = false;
	this->speed = 0.02;
	this->stop = true;
}

Bullet::~Bullet(){}

void Bullet::setStop(bool flag){
	this->stop = flag;
}

bool Bullet::getStop(){
	return this->stop;
}

void Bullet::setX(float posX){
	this->x = posX;
}

void Bullet::setY(float posY){
	this->y = posY;
}

void Bullet::setZ(float posZ){
	this->z = posZ;
}

float Bullet::getX(){
	return this->x;
}

float Bullet::getY(){
	return this->y;
}

float Bullet::getZ(){
	return this->z;
}


void Bullet::setShooted(bool flag){
	this->shooted = flag;
}

void Bullet::setSpeed(float fast){
	this->speed = fast;
}

float Bullet::getSpeed(){
	return this->speed;
}

bool Bullet::isShooted(){
	return this->shooted;
}
//draw
void Bullet::prepare(){
	if(this->stop){
		glBegin(GL_LINE_LOOP);
		glVertex3f(0.0, 0.0, -0.7);
		glVertex3f(0.0, 0.0, -1.0);
		glEnd();
	}
}
//movement bullet tiefighter
void Bullet::fireEnemy(TieFighter* modello, Xwings *wing, float speed, float stY, float stZ, float finY, float finZ){
	if(this->shooted){
		this->y = this->getY() + ((finY - stY)/speed);
		this->z = this->getZ() + ((finZ - stZ)/speed);
		if(this->z >= 2){
			this->z = modello->getZ();
			this->y = modello->getY();
			this->x = modello->getX();
			this->shooted = false;
			wing->setHit(false);
		}
	}
}
//follow the tiefighter (per pietro follow = segui)
void Bullet::moveBullet(TieFighter* model){
	if(this->shooted == false){
		this->x = model->getX();
		this->y = model->getY();
		this->z = model->getZ();
	}
}

void Bullet::draw(){
	glTranslated(this->getX(), this->getY(), this->getZ());
	glRotatef(20,1,0,0);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glLineWidth(2.5);
	this->prepare();
	glLineWidth(1);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
}

void Bullet::drawBomb(){
	glTranslated(this->getX(), this->getY(), this->getZ());
	glRotated(90, 1, 0, 0);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glutSolidCone(0.1, 0.3, 10,10);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
}

// hit the tiefighter
void Bullet::destroy(TieFighter* model){
	if((this->x >= model->getX() - model->getDimX()) && ( this->x <=  model->getX() + model->getDimX())){
		if((this->z  <= model->getZ()+ model->getDimZ()) && (this->z  >= model->getZ()- model->getDimZ())){
			if((this->y +0.5 >= model->getY() - model->getDimY()) && (this-> y + 0.5 <= model->getY() + model->getDimY())){
				this->shooted = false;
				model->setHit(true);
				model->setLive(model->getLive() - 1);
			}
        }
    }
}

//tiefighter hit xwing
void Bullet::destroyXwing(Xwings* model,TieFighter* model2){
	if(model2->getLive() < 1){
		this->stop = false;
		this->setShooted(false);
	}
	if(!model->isHit() && !model->getDeath()){
		if((this->x >= model->getX() - model->getDimX()) && ( this->x <=  model->getX() + model->getDimX())){
			if((this->z  <= model->getZ()+ model->getDimZ()) && (this->z  >= model->getZ()- model->getDimZ())){
				this->shooted = false;
				model->setHit(true);
				model->setLive(model->getLive() - 1);
			}
		}
	}
}

void Bullet::reset(Xwings* model, float fixX, float fixY, float fixZ){
	this->x = model->getX() + fixX;
	this->y = model->getY() + fixY;
	this->z = model->getZ() + fixZ;
}
//xwing
void Bullet::fire(float velX, float velY, float velZ){
	this->setX(this->getX() + velX);
	this->setY(this->getY() + velY);
	this->setZ(this->getZ() + velZ);
}