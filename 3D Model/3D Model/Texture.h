#ifndef TEXTURE_H
#define TEXTURE_H

#ifndef GLEW_H
#define GLEW_H
#include <gl\glew.h>
#include <glut.h>
#endif

class Texture{

private: 
	int id;

public:
	Texture();
	Texture(const Texture &texture);

	void loadTexture(const char* textName, int internalFormat, GLenum format);
	int getId();
};

#endif