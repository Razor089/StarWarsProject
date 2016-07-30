#include <Windows.h>
#include <gl\glew.h>
#include <glut.h>
#include <iostream>
#include <stdarg.h>
#include <stdlib.h>
#include "Bullet.h"
#include "main.h"
#include "Modello.h"
#include "DeathStar.h"
#include "Xwings.h"
#include "TieFighter.h"
#include "Audio.h"
#include "explosion.h"

//objects
Modello *model, *modelXwings, *modelTie, *modelDarth, *modelFinal, *modelDestroyer;
DeathStar *deathStar, *deathStar2 ;
Xwings  *xWing;
TieFighter *tieFighter, *tieFighter2, *darthVader, *tieFighter3,*tieFighter4,*tieFighter5,*tieFighter6, *morteNera;
Bullet *bullet0, *bomb,*bullet1, *bullet2, *bullet3, *bulletEnemy, *bulletEnemy2, *bulletEnemy3, *bulletEnemy4, *bulletEnemy5, *bulletEnemy6, *bulletDarth;
Audio *audio; 
Explosion *explosion;

GLuint textureWallpaper;
GLuint textureWin;
GLuint textLose;
GLuint textDeath;

//variable
float dirX, dirY, dirZ, speed, earthSimulation,moveDestroyer;
bool  detonator,scena, win, arrivato, imperialPlay, forcePlay, darthFirePlay, tieFighterFirePlay, fleetPlay, fleetFire, tieFigther2Play, exploded, winPlay, losePlay; 

GLfloat light0_position[4], light1_position[3], light2_position[3];
GLfloat light0_direction[3];

float spin = 0.0;
float t = 0.0;
float explosionControl = -1.0;

GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_24;

GLuint loadTexture(char* nameFile)	
{
    
	// La texture si trova nella cartella superiore di Debug/Release
    GLuint texture;
	// Otteniamo il formato dell'immagine
    FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(nameFile, 0);
    
	// Carichiamo l'immagine
	FIBITMAP *dib = FreeImage_Load(fif, nameFile, 0);
	// L'immagine Ë convertita nel formato GL_RGB
	dib = FreeImage_ConvertTo24Bits(dib);
	if( dib != NULL )
	{
		glGenTextures(1, &texture );
        glBindTexture(GL_TEXTURE_2D, texture);
        
		// Puntatore ai dati dell'immagine
		BYTE *pixels = (BYTE*)FreeImage_GetBits(dib);
        
		// PoichË FreeImage carica le immagini nel formato BGR
		// usiamo l'opzione GL_BGR_EXT per indicare ad OpenGL
		// che il formato dei dati Ë BGR
		// L'alternativa sarebbe stata quella di convertire
		//l'immagine dopo averla caricata da BGR a RGB
		glTexImage2D( GL_TEXTURE_2D, 0, 3, 
                     FreeImage_GetWidth(dib), FreeImage_GetHeight(dib), 0,
                     GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels );
		glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        
		// Deallochiamo l'immagine
		FreeImage_Unload(dib);
	}
    return texture;
}

void wallpaper(){
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glColor3f(1.0, 1.0, 1.0);
	if(!scena){
		glBindTexture(GL_TEXTURE_2D, textureWallpaper);
		glTranslatef(earthSimulation,0,0);
	} else {
		glBindTexture(GL_TEXTURE_2D, textDeath);
	}
	glBegin(GL_QUADS);
	glTexCoord2f(0,0); glVertex3f(-400, -20, -250);
	glTexCoord2f(1,0); glVertex3f(400, -20, -250);
	glTexCoord2f(1,1); glVertex3f(400, 380, -250);
	glTexCoord2f(0,1); glVertex3f(-400, 380, -250);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}


void FinalWallpaper(){
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glColor3f(1.0, 1.0, 1.0);
	if(win){
		glBindTexture(GL_TEXTURE_2D, textureWin);
		if(!winPlay){
			audio->stopAL(6);
			audio->playAL(7);
		}
		winPlay = true;
	}else if(xWing->getDeath()){
		glBindTexture(GL_TEXTURE_2D, textLose);
		if(!losePlay){
			audio->stopAL(1);
			audio->playAL(8);
		}
		losePlay = true;
	}
	glBegin(GL_QUADS);
	glTexCoord2f(0,0); glVertex3f(-1.6, -1, -1.1);
	glTexCoord2f(1,0); glVertex3f(1.6, -1, -1.1);
	glTexCoord2f(1,1); glVertex3f(1.6, 1, -1.1);
	glTexCoord2f(0,1); glVertex3f(-1.6, 1, -1.1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}

//light
void setOnTheLight(){
	GLfloat light_ambient[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat light_diffuse[] = {0.8, 0.8, 0.8, 1.0};

	//Position of the light
	light0_position[0] = 0.0;
	light0_position[1] = 1.0;
	light0_position[2] = 1.0;
	light0_position[3] = 1.0;

	light1_position[0] = 0.0;
	light1_position[1] = -2.0;
	light1_position[2] = -12.0;

	light2_position[0] = 0.0;
	light2_position[1] = -2.0;
	light2_position[2] = -10.0;

	//Direction of the light
	light0_direction[0] = 0.0;
	light0_direction[1] = -0.2;
	light0_direction[2] = -6.0;

	glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightfv(GL_LIGHT2, GL_POSITION, light2_position);

	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_direction);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glShadeModel(GL_SMOOTH);
}

void drawDestroyer(){
	
	glLoadIdentity();
	glTranslatef(20,0,0);
	glTranslatef(moveDestroyer,4,-19);
	glRotatef(-55,0,1,0);
	glRotatef(5,1,0,0);
	glScalef(6,6,6);
	modelDestroyer->prepare(1);
	glLoadIdentity();
	glTranslatef(-14,6,0);
	glTranslatef(moveDestroyer,4.5,-19);
	glRotatef(55,0,1,0);
	glRotatef(17,1,0,0);
	glScalef(6,6,6);
	modelDestroyer->prepare(1);
}

void display(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	wallpaper();

	glLoadIdentity();
	xWing->draw(modelXwings);
	
	glLoadIdentity();
	tieFighter->draw(modelTie);

	glLoadIdentity();
	tieFighter2->draw(modelTie);
	
	drawDestroyer();
	
	glLoadIdentity();
	tieFighter3->draw(modelTie);

	glLoadIdentity();
	tieFighter4->draw(modelTie);
	
	glLoadIdentity();
	tieFighter5->draw(modelTie);
	
	glLoadIdentity();
	tieFighter6->draw(modelTie);

	glLoadIdentity();
	deathStar->draw(model);
	
	glLoadIdentity();
	deathStar2->draw(model);

	glLoadIdentity();
	glColor3f(1,1,1);
	darthVader->draw(modelDarth);

	if(bullet0->isShooted())
	{
		glLoadIdentity();
		glColor3f(1,0,0);
		bullet0->draw();
		glLoadIdentity();
		bullet1->draw();
		glLoadIdentity();
		bullet2->draw();
		glLoadIdentity();
		bullet3->draw();
		glLoadIdentity();	
	}

	if(bulletEnemy->isShooted()){
		glLoadIdentity();
		glColor3f(0,1,0);
		bulletEnemy->draw();
	}
	if(bulletEnemy2->isShooted()){
		glLoadIdentity();
		glColor3f(0,1,0);
		bulletEnemy2->draw();
	}
	if(bulletEnemy3->isShooted()){
		glLoadIdentity();
		glColor3f(0,1,0);
		bulletEnemy3->draw();
	}
	if(bulletEnemy4->isShooted()){
		glLoadIdentity();
			glColor3f(0,1,0);
		bulletEnemy4->draw();
	}
	if(bulletEnemy5->isShooted()){
		glLoadIdentity();
		glColor3f(0,1,0);	
		bulletEnemy5->draw();
	}
	if(bulletEnemy6->isShooted()){
		glLoadIdentity();
		glColor3f(0,1,0);	
		bulletEnemy6->draw();
	}

	if(bulletDarth->isShooted()){
		glLoadIdentity();
		glColor3f(0,1,0);	
		bulletDarth->draw();
	}

	//Stampa delle scritte a video.
	glLoadIdentity();
	displayInfo();
	glLoadIdentity();
	glTranslated(2, 2, -3);
	glScaled(0.25, 0.25, 0.0);
	lifeBar(xWing);

	if(arrivato){
		glLoadIdentity();
		glTranslated(-3.5, 2, -3);
		glScaled(0.25, 0.25, 0.0);
		lifeBar2(darthVader);
	}
	if(bomb->isShooted()){
		glLoadIdentity();
		glColor3f(1.0,0.0,0.0);
		bomb->drawBomb();
	}
	if(win && xWing->getX() >=6){
		scena = true;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		light0_position[2] = 0.0;

		glLoadIdentity();
		glTranslated(-15, -180, 20);
		wallpaper();

		if(!morteNera->getDeath()){
			glLoadIdentity();
			morteNera->draw(modelFinal);
		}
		if(detonator){
			if(explosion->getSystemsSize() == 0){
				glLoadIdentity();
				FinalWallpaper();
			}
		}
	}

	glLoadIdentity();
	xWing->drawSahdow(modelXwings);

	glLoadIdentity();
	explosion->render();

	glFlush();
	glutSwapBuffers();
}

//messagges display
void displayInfo(){
	glLoadIdentity();
	if(xWing->getLive() <= 3){
		if(!forcePlay){
			audio->playAL(2);
		}
		forcePlay = true;
	}
	if(xWing->getDeath()){
		deathStar->setForward(false);
		deathStar2->setForward(false);
		if(explosion->getSystemsSize() == 0){
			FinalWallpaper();
		}
		audio->stopAL(0);
	}
}
//lifebar
void lifeBar(Xwings *model){
	int num = model->getLive();
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	if(num == 1){
		glColor3f(1, 0 , 0);
	} else {
		glColor3f(0.0, 1.0, 0.0);
	}
	for(int i = 0; i < num; i++){
		glVertex2f(0 + i, 0);
		glVertex2f(1 + i, 0);
		glVertex2f(1 + i, 1);
		glVertex2f(0 + i, 1);
	}
	glEnd();
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	
	glVertex2f(-0.1, -0.1);
	glVertex2f(-0.1, 1.1);

	glVertex2f(5.1, -0.1);
	glVertex2f(5.1, 1.1);

	glVertex2f(-0.1, -0.1);
	glVertex2f(5.1, -0.1);

	glVertex2f(-0.1, 1.1);
	glVertex2f(5.1, 1.1);
	glEnd();
	printw(1, -0.7, 0, "X Wing");
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
}

void lifeBar2(TieFighter *model){
	int num = model->getLive();
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	if(num == 1){
		glColor3f(1, 0 , 0);
	} else {
		glColor3f(0.0, 1.0, 0.0);
	}
	for(int i = 0; i < num; i++){
		glVertex2f(0 + i, 0);
		glVertex2f(1 + i, 0);
		glVertex2f(1 + i, 1);
		glVertex2f(0 + i, 1);
	}
	glEnd();
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	
	glVertex2f(-0.1, -0.1);
	glVertex2f(-0.1, 1.1);

	glVertex2f(5.1, -0.1);
	glVertex2f(5.1, 1.1);

	glVertex2f(-0.1, -0.1);
	glVertex2f(5.1, -0.1);

	glVertex2f(-0.1, 1.1);
	glVertex2f(5.1, 1.1);
	glEnd();
	printw(1, -0.7, 0, "Darth Vader");
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
}

//movement bullet xwing
void moveBullets(){
	if(bullet0->getZ() > -30
		&& bullet0->isShooted()){
		bullet0->fire(-0.02, 0.20, -1.25);
		bullet3->fire(-0.02, 0.23, -1.25);
	} else {
		bullet0->setShooted(false);
		bullet3->setShooted(false);
		bullet0->reset(xWing, 0.4, 0.2, 0.4);
		bullet3->reset(xWing, 0.4, -0.2, 0.4);
	}
	if(bullet1->getZ() > -30
		&& bullet1->isShooted()){
		bullet1->fire(0.02, 0.20, -1.25);
		bullet2->fire(0.02, 0.23, -1.25);
	} else {
		bullet1->setShooted(false);
		bullet2->setShooted(false);
		bullet1->reset(xWing, -0.4, 0.2, 0.4);
		bullet2->reset(xWing, -0.4, -0.2, 0.4);
	}
}

void idle(){
	explosion->updateParticleSystems(0.01);
	if(explosionControl >= 1000.0 && !detonator){
		audio->stopAL(1);
		audio->playAL(6);
		explosion->createParticleSystem(morteNera->getX(), morteNera->getY(), morteNera->getZ());
		explosionControl = 0.0;
		detonator = true;
	}
	
	//Movimento dei TieFighter
	tieFighter->movement(2.1, -2.1, 5, 0.5, tieFighter->getSpeed(), 0, -18);
	tieFighter2->movement(2.1, -2.1, 5, 0.5, tieFighter2->getSpeed(), 0, -18);
	tieFighter3->movement(60,-560,0,1.5,tieFighter3->getSpeed(),2,0);
	tieFighter4->movement(60,-60,0,1,tieFighter4->getSpeed(),2,0);
	tieFighter5->movement(60,-60,0,1.5,tieFighter5->getSpeed(),2,0);
	tieFighter6->movement(60,-60,0,1,tieFighter6->getSpeed(),2,0);

	tieFighter3->moveDarth(60,-60,-90);
	tieFighter4->moveDarth(60,-60,-90);
	tieFighter5->moveDarth(60,-60,-90);
	tieFighter6->moveDarth(60,-60,-90);

	//Arrivo dei TieFighter
	tieFighter->incoming(deathStar, deathStar2);
	tieFighter2->incoming(deathStar, deathStar2);

	//rotazione per i TieFighter
	if(tieFighter->getZ() < -11 && tieFighter->getAngle() < 180){
		tieFighter->setAngle(tieFighter->getAngle() + 3.0);
	}
	if(tieFighter2->getZ() < -11 && tieFighter2->getAngle() > -180){
		tieFighter2->setAngle(tieFighter2->getAngle() - 3.0);
	}

	//Reset dei TieFighter dopo che sono stati sparati
	tieFighter->reset(7, 5, -5, explosion);
	tieFighter2->reset(-4, 5, -5, explosion);

	//Distruzione dei TieFighter se colpiti
	tieFighter->destroy();
	tieFighter2->destroy();	

	//Colpi dei TieFighter
	if(tieFighter->getY() <= 0.5 && tieFighter->getZ() <= -17){
		bulletEnemy->setShooted(true);
		if(bulletEnemy->isShooted() && bulletEnemy->getZ() == tieFighter->getZ()){
			audio->playAL(0);
		}
	}
	if(tieFighter2->getY() <= 0.5 && tieFighter2->getZ() <= -17){
		bulletEnemy2->setShooted(true);
		if(bulletEnemy2->isShooted() && bulletEnemy2->getZ() == tieFighter2->getZ()){
			audio->playAL(0);
		}
	}
	if(tieFighter3->getY() <= 1.5){
		bulletEnemy3->setShooted(true);
		if(!fleetFire){
			audio->playAL(0);
		}
		fleetFire = true;
	}
	if(tieFighter4->getY() <= 1){
		bulletEnemy4->setShooted(true);
	}
	if(tieFighter5->getY() <= 1.5){
		bulletEnemy5->setShooted(true);
	}
	if(tieFighter6->getY() <= 1){
		bulletEnemy6->setShooted(true);
	}

	//attack of tiefighters and darthvader
	attack();

	//set bullet
		//Colpi del primo TieFighter
	bulletEnemy->moveBullet(tieFighter);
	bulletEnemy->fireEnemy(tieFighter,xWing, 50, 0.5, -18, -2.15, -5);
	
	bulletEnemy2->moveBullet(tieFighter2);
	bulletEnemy2->fireEnemy(tieFighter2,xWing, 50, 0.5, -18, -2.15, -5);

	bulletEnemy3->moveBullet(tieFighter3);
	bulletEnemy3->fireEnemy(tieFighter3,xWing, 50, 1.5, -11.49, -2.15, -5);

	bulletEnemy4->moveBullet(tieFighter4);
	bulletEnemy4->fireEnemy(tieFighter4,xWing, 50, 1, -8.99, -2.15, -5);

	bulletEnemy5->moveBullet(tieFighter5);
	bulletEnemy5->fireEnemy(tieFighter5,xWing, 50, 1.5, -11.49, -2.15, -5);

	bulletEnemy6->moveBullet(tieFighter6);
	bulletEnemy6->fireEnemy(tieFighter6,xWing, 50, 1, -8.99, -2.15, -5);

	if(bulletEnemy2->isShooted()){
		bulletEnemy2->destroyXwing(xWing,tieFighter2);
	}

	if(bulletEnemy->isShooted()){
		bulletEnemy->destroyXwing(xWing,tieFighter);
	}

	if(bulletEnemy3->isShooted()){
		bulletEnemy3->destroyXwing(xWing,tieFighter3);
	}

	if(bulletEnemy4->isShooted()){
		bulletEnemy4->destroyXwing(xWing,tieFighter4);
	}

	if(bulletEnemy5->isShooted()){
		bulletEnemy5->destroyXwing(xWing,tieFighter5);
	}

	if(bulletEnemy6->isShooted()){
		bulletEnemy6->destroyXwing(xWing,tieFighter6);
	}

	//Controllo sui colpi dell X-Wing
	bullet0->destroy(tieFighter);
	bullet0->destroy(tieFighter2);
	bullet0->destroy(darthVader);

	//Movimento dell corridoio della MorteNera
	deathStar->movement(deathStar->getSpeed());
	deathStar->controlPlane();
	deathStar2->movement(deathStar2->getSpeed());
	deathStar2->controlPlane();
	
	//Movimento di DarthVade
	if(!arrivato){
		darthVader->movement(60, -60, 0, 0.5, darthVader->getSpeed(), -18, 0);
		darthVader->moveDarth(60,-60,-90);
		if(darthVader->getY() < 1){
			arrivato = true;
			darthVader->setLeft(true);
		}
	} else {
		bulletDarth->setShooted(true);
		if(!darthVader->getDeath()){
			if(bulletDarth->isShooted() && bulletDarth->getZ() == darthVader->getZ()){
				audio->playAL(0);
			}
		}
		darthVader->setForward(false);
		darthVader->setBack(false);
		
		if(darthVader->getX() >= 2.1){
			darthVader->setRight(false);
			darthVader->setLeft(true);
		}
		if(darthVader->getX() <= -2.1){
			darthVader->setRight(true);
			darthVader->setLeft(false);
		}
		darthVader->movement(2.1,-2.1,0,0.5,darthVader->getSpeed(),0,0);
	}

	if(bulletDarth->isShooted()){
		bulletDarth->destroyXwing(xWing,darthVader);
	}

	darthVader->explodeDarth(explosion);
	darthVader->destroy();

	bulletDarth->moveBullet(darthVader);
	bulletDarth->fireEnemy(darthVader, xWing, 40, 0.5, -18, -2.15, -5);

	moveBullets();

	//Gestione dei movimenti dell X-Wing
	
	if(win){
		xWing->movement(50,0,30,0,0.05);
		xWing->goOut();
		morteNera->setAngle(morteNera->getAngle() - 0.03);
		if(morteNera->getAngle() <= -50){
			explosionControl = 1000.0;
			morteNera->setDeath(true);
		}
		if(detonator == false){
			explosion->destroyParticleSystems();
		}
	} else {
		xWing->explosionWall(deathStar, deathStar2, explosion);
		//xWing->explosionBorder(explosion);
		xWing->movement(2, -2, -1.15, -2.15, 0.06);
	}
	xWing->lose(explosion);

	if(bomb->isShooted() && bomb->getY() > -5){
		bomb->fire(0,-0.1,0);
	} else {
		bomb->setShooted(false);
		bomb->reset(xWing, 0, 0, 0);
	}
	final();
	if(earthSimulation <= 55){
		earthSimulation += 0.05;
	}
	moveDestroyer -= 0.001;

	finalBomb();

	glutPostRedisplay();
}

void final(){
	if(darthVader->getDeath()){
		if((deathStar->getZ() == 65) || (deathStar2->getZ() == 65)){
			audio->playAL(3);
			deathStar->setSpeed(0.1);
			deathStar2->setSpeed(0.1);
		}
		if(((deathStar->getZ() >= 77) && (deathStar->getZ() <= 78) )||( (deathStar2->getZ() >= 77)  && (deathStar2->getZ() <= 78)) ){
			deathStar->setForward(false);
			deathStar2->setForward(false);
		}
	}
}

void attack(){
	if(tieFighter->getDeath()&&tieFighter2->getDeath()){
		if(tieFighter3->getX() == 1){
			if(!fleetPlay){
				audio->playAL(4);
			}
			fleetPlay = true;
		}
		tieFighter3->come(1);
		tieFighter4->come(0.5);
		tieFighter5->come(-1);
		tieFighter6->come(-0.5);
		if(!arrivato){
			darthVader->stopDarthVader(0, 16);
			
		}
	}
	if(tieFighter6->getZ() >=0){
		tieFighter3->setDeath(true);
		tieFighter4->setDeath(true);
		tieFighter5->setDeath(true);
		tieFighter6->setDeath(true);
		if(!arrivato){
			darthVader->come(0);
		}
	}
}

void finalBomb(){
	if(bomb->isShooted()){
		if((bomb->getX() >= -0.4) && (bomb->getX() <= 0.5) && (bomb->getY() <= -4.9)){
			if((deathStar->getZ() >= 77) && (deathStar->getZ() <= 78) || 
				(deathStar2->getZ() >= 77) && (deathStar2->getZ() <= 78)){
				win = true;
			}
		}
	}
}

void key(unsigned char key, int x, int y){
	switch(key){
	case 'a':
		xWing->setLeft(true);
		break;
	case 'd':
		xWing->setRight(true);
		break;
	case ' ':
		//Se siamo ancora vivi, spariamo.
		if(!win){
			if(xWing->getLive() > 0 && !xWing->getDeath()){
				bullet0->setShooted(true);
				bullet1->setShooted(true);
				bullet2->setShooted(true);
				bullet3->setShooted(true);
				audio->playAL(5);
			}
		}
		break;
	case 'n' :
		if(darthVader->getDeath()){
			bomb->setShooted(true);
		}
		break;
	case 'r':
		restart();
		break;
	case 'p':
		audio->pauseAL(1);
		break;
	case 'y':
		glutLeaveGameMode();
		exit(0);
		break;
	case 'l':
		std::cout << " terra " << earthSimulation << std::endl;
		break;
	case 'w':
		xWing->setUp(true);
		xWing->setDown(false);
		break;
	}
}

void keyUp(unsigned char key, int x, int y){
	switch(key){
	case 'a':
		xWing->setLeft(false);
		break;
	case 'd':
		xWing->setRight(false);
		break;
	case 'w':
		xWing->setUp(false);
		xWing->setDown(true);
		break;
	}
}

void reshape(int w, int h){
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80, (GLfloat)w/(GLfloat)h, 0.1, 700);
    glMatrixMode(GL_MODELVIEW);
}


void init(){
	glutSetCursor(GLUT_CURSOR_NONE);
	earthSimulation = 0;
	exploded = false;
	audio = new Audio();
	audio->initAL();
	explosion = new Explosion();
	explosion->initExp();

	textureWallpaper = loadTexture("immagini/Earth Horizon.jpg");
	textureWin = loadTexture("immagini/Programmatori.jpg");
	textLose = loadTexture("immagini/Darth Vader.jpg");
	textDeath = loadTexture("immagini/Cosmos01.jpg");

	xWing = new Xwings();
	tieFighter = new TieFighter();
	tieFighter2 = new TieFighter();
	tieFighter3 = new TieFighter();
	tieFighter4 = new TieFighter();
	tieFighter5 = new TieFighter();
	tieFighter6 = new TieFighter();
	deathStar = new DeathStar();
	deathStar2 = new DeathStar();
	darthVader = new TieFighter();
	
	modelXwings = new Modello();
	modelXwings->loadasset("modelli/X Wing.dae");
	modelXwings->loadScene();
	xWing->setDimX(0.5);
	xWing->setDimY(0.5);
	xWing->setDimZ(0.5);
	xWing->setX(0);
	xWing->setY(-2.15);
	xWing->setZ(-5);

	modelDestroyer = new Modello();
	modelDestroyer->loadasset("modelli/Destroyer.dae");
	modelDestroyer->loadScene();
	
	modelTie = new Modello();
	modelTie->loadasset("modelli/Tie fighter.dae");
	modelTie->loadScene();
	tieFighter->setDimX(0.5);
	tieFighter->setDimY(0.5);
	tieFighter->setDimZ(0.5);
	tieFighter->setX(7);	
	tieFighter->setY(5);	
	tieFighter->setZ(-5); 
	tieFighter->setHit(false);
	tieFighter->setLive(3);
	tieFighter->setSpeed(0.05);


	tieFighter2->setDimX(0.5);
	tieFighter2->setDimY(0.5);
	tieFighter2->setDimZ(0.5);
	tieFighter2->setX(-4);	
	tieFighter2->setY(5);	
	tieFighter2->setZ(-5); 
	tieFighter2->setHit(false);
	tieFighter2->setLive(3);
	tieFighter2->setSpeed(0.05);

	//flotta
	tieFighter3->setDimX(0.5);
	tieFighter3->setDimY(0.5);
	tieFighter3->setDimZ(0.5);
	tieFighter3->setX(-22);
	tieFighter3->setY(15);	
	tieFighter3->setZ(-25); 
	tieFighter3->setHit(false);
	tieFighter3->setRight(true);
	tieFighter3->setAngle(90);
	tieFighter3->setLive(2);
	tieFighter3->setSpeed(0.5);

	tieFighter4->setDimX(0.5);
	tieFighter4->setDimY(0.5);
	tieFighter4->setDimZ(0.5);
	tieFighter4->setX(-22);
	tieFighter4->setY(17);	
	tieFighter4->setZ(-25); 
	tieFighter4->setHit(false);
	tieFighter4->setRight(true);
	tieFighter4->setAngle(90);
	tieFighter4->setLive(2);
	tieFighter4->setSpeed(0.5);

	tieFighter5->setDimX(0.5);
	tieFighter5->setDimY(0.5);
	tieFighter5->setDimZ(0.5);
	tieFighter5->setX(-24);
	tieFighter5->setY(15);	
	tieFighter5->setZ(-25); 
	tieFighter5->setHit(false);
	tieFighter5->setRight(true);
	tieFighter5->setAngle(90);
	tieFighter5->setLive(2);
	tieFighter5->setSpeed(0.5);

	tieFighter6->setDimX(0.5);
	tieFighter6->setDimY(0.5);
	tieFighter6->setDimZ(0.5);
	tieFighter6->setX(-24);
	tieFighter6->setY(17);	
	tieFighter6->setZ(-25); 
	tieFighter6->setHit(false);
	tieFighter6->setRight(true);
	tieFighter6->setAngle(90);
	tieFighter6->setLive(2);
	tieFighter6->setSpeed(0.5);

	model = new Modello();
	model->loadasset("modelli/corridoio.dae");  
	model->loadScene();
	deathStar->setForward(true);
	deathStar->setX(-9);
	deathStar->setY(-1);
	deathStar->setZ(-70);
	deathStar->setDimX(90);
	deathStar->setDimY(90);
	deathStar->setDimZ(90);
	deathStar->setSpeed(0.5);

	deathStar2->setForward(true);
	deathStar2->setX(-9);
	deathStar2->setY(-1);
	deathStar2->setZ(-250);
	deathStar2->setDimX(90);
	deathStar2->setDimY(90);
	deathStar2->setDimZ(90);
	deathStar2->setSpeed(0.5);

	//darth vader
	modelDarth = new Modello();
	modelDarth->loadasset("modelli/DarthVader.dae");
	modelDarth->loadScene();
	darthVader->setDimX(0.5);
	darthVader->setDimY(0.5);
	darthVader->setDimZ(0.5);
	darthVader->setX(-20);	
	darthVader->setY(16);	
	darthVader->setZ(-25);
	darthVader->setAngle(-90);
	darthVader->setHit(false);
	darthVader->setRight(true);
	darthVader->setLive(5);
	darthVader->setSpeed(0.5);

	/////////////////////////// morte nera//////////////////////////
	morteNera = new TieFighter();
	modelFinal = new Modello();
	modelFinal->loadasset("modelli/morteNera.dae");
	modelFinal->loadScene();
	morteNera->setDimX(0.5);
	morteNera->setDimY(0.5);
	morteNera->setDimZ(0.5);
	morteNera->setX(-1);	
	morteNera->setY(0.6);	
	morteNera->setZ(-2.2);
	morteNera->setHit(false);
	morteNera->setLive(1);
	morteNera->setAngle(-40);
	 
	//Creiamo i colpi da assegnare al x wing
	bullet0 = new Bullet();
	bullet1 = new Bullet();
	bullet2 = new Bullet();
	bullet3 = new Bullet();
	bomb = new Bullet();

	bomb->setX(xWing->getX());
	bomb->setY(xWing->getY());
	bomb->setZ(xWing->getZ());
	
	//bullet darth
	bulletDarth = new Bullet();
	bulletDarth->setX(darthVader->getX());
	bulletDarth->setY(darthVader->getY());
	bulletDarth->setZ(darthVader->getZ());

	//colpi tiefighter
	bulletEnemy = new Bullet();
	bulletEnemy->setX(tieFighter->getX());
	bulletEnemy->setY(tieFighter->getY());
	bulletEnemy->setZ(tieFighter->getZ());

	bulletEnemy2 = new Bullet();
	bulletEnemy2->setX(tieFighter2->getX());
	bulletEnemy2->setY(tieFighter2->getY());
	bulletEnemy2->setZ(tieFighter2->getZ());

	bulletEnemy3 = new Bullet();
	bulletEnemy3->setX(tieFighter3->getX());
	bulletEnemy3->setY(tieFighter3->getY());
	bulletEnemy3->setZ(tieFighter3->getZ());

	bulletEnemy4 = new Bullet();
	bulletEnemy4->setX(tieFighter4->getX());
	bulletEnemy4->setY(tieFighter4->getY());
	bulletEnemy4->setZ(tieFighter4->getZ());

	bulletEnemy5= new Bullet();
	bulletEnemy5->setX(tieFighter5->getX());
	bulletEnemy5->setY(tieFighter5->getY());
	bulletEnemy5->setZ(tieFighter5->getZ());

	bulletEnemy6 = new Bullet();
	bulletEnemy6->setX(tieFighter6->getX());
	bulletEnemy6->setY(tieFighter6->getY());
	bulletEnemy6->setZ(tieFighter6->getZ());

	//Destra
	bullet0->setX(xWing->getX() + 0.4);
	bullet0->setY(xWing->getY() + 0.2);
	bullet0->setZ(xWing->getZ() + 0.4);
	//sinistra
	bullet1->setX(xWing->getX() - 0.4);
	bullet1->setY(xWing->getY() + 0.2);
	bullet1->setZ(xWing->getZ() + 0.4);
	//sinistra
	bullet2->setX(xWing->getX() - 0.4);
	bullet2->setY(xWing->getY() - 0.2);
	bullet2->setZ(xWing->getZ() + 0.4);
	//destra
	bullet3->setX(xWing->getX() + 0.4);
	bullet3->setY(xWing->getY() - 0.2);
	bullet3->setZ(xWing->getZ() + 0.4);

	arrivato = false;
	imperialPlay = false;
	forcePlay = false;
	tieFighterFirePlay = false;
	darthFirePlay = false;
	tieFigther2Play = false;
	fleetPlay = false;
	fleetFire = false;
	winPlay = false;
	losePlay = false;
	win = false;
	scena = false;
	detonator = false;
	moveDestroyer = 0;

	audio->playAsStream(1);

	glClearColor(0.1f, 0.1f, 0.1f, 1.f);

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POLYGON_SMOOTH_HINT);
	glEnable(GL_TEXTURE_2D);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_NORMALIZE);

	// XXX docs say all polygons are emitted CCW, but tests show that some aren't.
	if(getenv("MODEL_IS_BROKEN"))  
		glFrontFace(GL_CW);

	setOnTheLight();
}

void main(int argc, char* argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	//glutInitWindowPosition(0,0);
	//glutInitWindowSize(1280,800);
	//glutCreateWindow("Star wars 3D");
	glutGameModeString("1280x800:32@80");
    //glutSetCursor(GLUT_CURSOR_NONE);
	glutEnterGameMode();
	init();
	MessageBox(NULL, "- Star Wars: Trench Run -\n" 
					"Tasti:\n"
					"a: sinistra\n"
					"d: destra\n"
					"w: salta\n"
					"spazio: spara\n"
					"n: sgancia la bomba\n"
					"r: per ricominciare\n"
					"***ATTENZIONE***\n"
					"L' impatto con il muro comportera' la fine della partita\n"
					"E' possibile usare la bomba solo dopo aver sconfitto Darth Vader\n"
					"Obiettivo del gioco:\n"
					"Evitare i colpi nemici, colpire i TieFighter e distruggere la morte nera con la bomba", "INFO", MB_OK | MB_ICONINFORMATION);
	glutKeyboardFunc(key);
	glutKeyboardUpFunc(keyUp);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutMainLoop();
	
}

void printw (float x, float y, float z, char* format, ...)
{
	va_list args;	//  Variable argument list
	int len;		//	String length
	int i;			//  Iterator
	char * text;	//	Text

	//  Initialize a variable argument list
	va_start(args, format);

	//  Return the number of characters in the string referenced the list of arguments.
	//  _vscprintf doesn't count terminating '\0' (that's why +1)
	len = _vscprintf(format, args) + 1; 

	//  Allocate memory for a string of the specified size
	text = (char *)malloc(len * sizeof(char));

	//  Write formatted output using a pointer to the list of arguments
	vsprintf_s(text, len, format, args);

	//  End using variable argument list 
	va_end(args);

	//  Specify the raster position for pixel operations.
	glRasterPos3f (x, y, z);

	//  Draw the characters one by one
	for (i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(font_style, text[i]);

	//  Free the allocated memory for the string
	free(text);
}

void restart(){
	explosion->destroyParticleSystems();
	audio->stopAL(7);
	explosionControl = -1.0;
	arrivato = false;
	forcePlay = false;
	fleetPlay = false;
	fleetFire = false;
	win = false;
	scena = false;
	detonator = false;
	winPlay = false;
	losePlay = false;
	earthSimulation = 0;
	moveDestroyer = 0;

	delete xWing;
	delete tieFighter;
	delete tieFighter2;
	delete tieFighter3;
	delete tieFighter4;
	delete tieFighter5;
	delete tieFighter6;
	delete darthVader;
	delete morteNera;

	xWing = new Xwings();
	tieFighter = new TieFighter();
	tieFighter2 = new TieFighter();
	tieFighter3 = new TieFighter();
	tieFighter4 = new TieFighter();
	tieFighter5 = new TieFighter();
	tieFighter6 = new TieFighter();
	darthVader = new TieFighter();
	morteNera = new TieFighter();

	morteNera->setDimX(0.5);
	morteNera->setDimY(0.5);
	morteNera->setDimZ(0.5);
	morteNera->setX(-1);	
	morteNera->setY(0.6);	
	morteNera->setZ(-2.2); 
	morteNera->setHit(false);
	morteNera->setLive(1);
	morteNera->setAngle(-40);

	xWing->setDimX(0.5);
	xWing->setDimY(0.5);
	xWing->setDimZ(0.5);
	xWing->setX(0);
	xWing->setY(-2.15);
	xWing->setZ(-5);
	xWing->setLive(5);
	xWing->setDeath(false);

	tieFighter->setDimX(0.5);
	tieFighter->setDimY(0.5);
	tieFighter->setDimZ(0.5);
	tieFighter->setX(7);	
	tieFighter->setY(5);	
	tieFighter->setZ(-5);
	tieFighter->setHit(false);
	tieFighter->setLive(3);
	tieFighter->setSpeed(0.05);
	tieFighter->setDeath(false);

	bulletEnemy->setX(darthVader->getX());
	bulletEnemy->setY(darthVader->getY());
	bulletEnemy->setZ(darthVader->getZ());
	bulletEnemy->setStop(true);

	tieFighter2->setDimX(0.5);
	tieFighter2->setDimY(0.5);
	tieFighter2->setDimZ(0.5);
	tieFighter2->setX(-4);	
	tieFighter2->setY(5);
	tieFighter2->setZ(-5); 
	tieFighter2->setHit(false);
	tieFighter2->setLive(3);
	tieFighter2->setSpeed(0.05);
	tieFighter2->setDeath(false);

	bulletEnemy2->setX(darthVader->getX());
	bulletEnemy2->setY(darthVader->getY());
	bulletEnemy2->setZ(darthVader->getZ());
	bulletEnemy2->setStop(true);

	tieFighter3->setDimX(0.5);
	tieFighter3->setDimY(0.5);
	tieFighter3->setDimZ(0.5);
	tieFighter3->setX(-22);
	tieFighter3->setY(15);	
	tieFighter3->setZ(-25); 
	tieFighter3->setHit(false);
	tieFighter3->setRight(true);
	tieFighter3->setForward(false);
	tieFighter3->setDown(false);
	tieFighter3->setAngle(90);
	tieFighter3->setLive(2);
	tieFighter3->setSpeed(0.5);

	tieFighter4->setDimX(0.5);
	tieFighter4->setDimY(0.5);
	tieFighter4->setDimZ(0.5);
	tieFighter4->setX(-22);
	tieFighter4->setY(17);	
	tieFighter4->setZ(-25); 
	tieFighter4->setHit(false);
	tieFighter4->setRight(true);
	tieFighter4->setForward(false);
	tieFighter4->setDown(false);
	tieFighter4->setAngle(90);
	tieFighter4->setLive(2);
	tieFighter4->setSpeed(0.5);

	tieFighter5->setDimX(0.5);
	tieFighter5->setDimY(0.5);
	tieFighter5->setDimZ(0.5);
	tieFighter5->setX(-24);
	tieFighter5->setY(15);	
	tieFighter5->setZ(-25);
	tieFighter5->setHit(false);
	tieFighter5->setRight(true);
	tieFighter5->setForward(false);
	tieFighter5->setDown(false);
	tieFighter5->setAngle(90);
	tieFighter5->setLive(2);
	tieFighter5->setSpeed(0.5);

	tieFighter6->setDimX(0.5);
	tieFighter6->setDimY(0.5);
	tieFighter6->setDimZ(0.5);
	tieFighter6->setX(-24);
	tieFighter6->setY(17);	
	tieFighter6->setZ(-25);
	tieFighter6->setHit(false);
	tieFighter6->setRight(true);
	tieFighter6->setForward(false);
	tieFighter6->setDown(false);
	tieFighter6->setAngle(90);
	tieFighter6->setLive(2);
	tieFighter6->setSpeed(0.5);

	deathStar->setForward(true);
	deathStar->setX(-9);
	deathStar->setY(-1);
	deathStar->setZ(-70);
	deathStar->setDimX(90);
	deathStar->setDimY(90);
	deathStar->setDimZ(90);
	deathStar->setSpeed(0.5);

	deathStar2->setForward(true);
	deathStar2->setX(-9);
	deathStar2->setY(-1);
	deathStar2->setZ(-250);
	deathStar2->setDimX(90);
	deathStar2->setDimY(90);
	deathStar2->setDimZ(90);
	deathStar2->setSpeed(0.5);

	darthVader->setDimX(0.5);
	darthVader->setDimY(0.5);
	darthVader->setDimZ(0.5);
	darthVader->setX(-20);	
	darthVader->setY(16);	
	darthVader->setZ(-25); 
	darthVader->setAngle(-90);
	darthVader->setHit(false);
	darthVader->setRight(true);
	darthVader->setDown(false);
	darthVader->setForward(false);
	darthVader->setLive(5);
	darthVader->setSpeed(0.5);

	bulletDarth->setX(darthVader->getX());
	bulletDarth->setY(darthVader->getY());
	bulletDarth->setZ(darthVader->getZ());
	bulletDarth->setStop(true);

	tieFighter3->setDeath(false);
	tieFighter4->setDeath(false);
	tieFighter5->setDeath(false);
	tieFighter6->setDeath(false);
	darthVader->setDeath(false);

	audio->playAsStream(1);
}