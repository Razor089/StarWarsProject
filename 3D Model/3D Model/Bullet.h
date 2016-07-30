#ifndef BULLET_H
#define BULLET_H
#include <gl\glew.h>
#include "Xwings.h"
#include "TieFighter.h"

class Bullet{

private:
	float x, y,z;
	bool shooted, stop;
	float speed;

public:
	Bullet();
	~Bullet();
	float getX();
	float getY();
	float getZ();
	float getSpeed();
	bool isShooted();
	void setX(float posX);
	void setY(float posY);
	void setZ(float posZ);
	void setShooted(bool flag);
	void setSpeed(float fast);
	void prepare();
	void draw();
	void fire(float velX, float velY, float velZ);
	void moveBullet(TieFighter* model);
	void fireEnemy(TieFighter* modello, Xwings *wing, float speed, float stY, float stZ, float finY, float finZ);
	void destroy(TieFighter* model);
	void destroyXwing(Xwings* model ,TieFighter* model2);
	void reset(Xwings *model, float fixX, float fixY, float fixZ);
	void setStop(bool flag);
	bool getStop();
	void drawBomb();
};

#endif