#include "texture.h"
#include <FreeImage.h>

Texture::Texture(){
	id=0;
}
	
Texture::Texture(const Texture &texture){
	id=texture.id;
}

void Texture::loadTexture(const char* textName, int internalFormat, GLenum format){
	// Otteniamo il formato dell'immagine
	FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(textName, 0);

	// Carichiamo l'immagine
	FIBITMAP *dib = FreeImage_Load(fifmt, textName,0);

	// L'immagine è convertita a 24 bit
	// indipendentemente dalla sorgente
	// quindi 8 bit per ogni componente
	if(internalFormat==3){
		dib = FreeImage_ConvertTo24Bits(dib);
	} else if (internalFormat==4){
		dib = FreeImage_ConvertTo32Bits(dib);
	}


	if( dib != NULL ){
		
		GLuint idTexture;
		glGenTextures( 1, &idTexture );
		glBindTexture( GL_TEXTURE_2D, idTexture );
		

		// Puntatore ai dati dell'immagine
		BYTE *pixels = (BYTE*)FreeImage_GetBits(dib);

		// Poichè FreeImage carica le immagini nel formato BGR
		// usiamo l'opzione GL_BGR_EXT per indicare ad OpenGL
		// che il formato dei dati è BGR
		// L'alternativa sarebbe stata quella di convertire
		//l'imagine dopo averla caricata da BGR a RGB
		/*glTexImage2D( GL_TEXTURE_2D, 0, 3, 
									FreeImage_GetWidth(dib), FreeImage_GetHeight(dib), 0,
									GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels );
        */
		if (internalFormat == 1) {
			glTexImage2D( GL_TEXTURE_2D, 0, GL_ALPHA, FreeImage_GetWidth(dib), FreeImage_GetHeight(dib), 0,
					GL_ALPHA, GL_UNSIGNED_BYTE, pixels );
		} else {
			glTexImage2D( GL_TEXTURE_2D, 0, internalFormat, FreeImage_GetWidth(dib), FreeImage_GetHeight(dib), 0,
					format, GL_UNSIGNED_BYTE, pixels );
		}

		

		glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		// Deallochiamo l'immagine
		FreeImage_Unload(dib);
		id=idTexture;
	}
}

//Restituisce l'id della texture
int Texture::getId(){
	return id;
}