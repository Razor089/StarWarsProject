#ifndef MAIN_H
#define MAIN_H

void reshape(int w, int h);
void display();
void init();
void key(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void idle();
void printw (float x, float y, float z, char* format, ...);
void displayInfo();
void control();
void reset();
void lifeBar(Xwings *model);
void lifeBar2(TieFighter *model);
void setOnTheLight();
void attack();
void final();
void wallpaper();
GLuint loadTexture(char* nameFile);
void finalBomb();
void FinalWallpaper();
void restart();
void moveBullets();
void shake();
void explosionDisplay();
void drawDestroyer();
#endif