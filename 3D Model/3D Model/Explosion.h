#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <spark\SPK.h>
#include <spark\SPK_GL.h>
#include <stdio.h>

#include "texture.h"

using namespace std;
using namespace SPK;
using namespace SPK::GL;

class Explosion {
	private:
		Texture textureExplosion;
		Texture textureFlash;
		Texture textureSpark1;
		Texture textureSpark2;
		Texture textureWave;
		list<System*> particleSystems;
		bool loadTexture(GLuint& index,char* path,GLuint type,GLuint clamp,bool mipmap);
		SPK_ID createParticleSystemBase(GLuint textureExplosion,GLuint textureFlash,GLuint textureSpark1,GLuint textureSpark2,GLuint textureWave);
		void destroyParticleSystem(System*& system);	
		System* createParticleSystem(const Vector3D& pos);
public:
		void destroyParticleSystems();
		void initExp();
		void createParticleSystem (float x,float y, float z);
		void render();
		void updateParticleSystems(float dt);	
		int getSystemsSize();
};


#endif