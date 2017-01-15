//read unsigned char from file c++: http://stackoverflow.com/questions/11214782/how-to-read-in-binary-data-and-cast-to-unsigned-char-c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "textura.hpp"

using namespace std;

GLuint textureID = -1;

int LoadTexture(string filename)
{
	void* imgData;
	int imgWidth, imgHeight;

	cout << "Cargando texturas\n";

	textureID++;

	imgData = 0;
	FREE_IMAGE_FORMAT format = FreeImage_GetFIFFromFilename(filename.c_str());
	if (format == FIF_UNKNOWN) {
		cout << "Tipo desconocido de imagen para " << filename << endl;
	}
	FIBITMAP* bitmap = FreeImage_Load(format, filename.c_str(), 0);
	if (!bitmap) {
		cout << "Fallo en la carga de imagen " << filename << endl;
	}
	FIBITMAP* bitmap2 = FreeImage_ConvertTo24Bits(bitmap);
	FreeImage_Unload(bitmap);
	imgData = FreeImage_GetBits(bitmap2);
	imgWidth = FreeImage_GetWidth(bitmap2);
	imgHeight = FreeImage_GetHeight(bitmap2);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  // (Actually, this one is the default)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        int formato = (FI_RGBA_RED == 0) ? GL_RGB : GL_BGR;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, formato, GL_UNSIGNED_BYTE, imgData);

	if (imgData) {
		cout << "Textura cargada del fichero " << filename << " con tamano " << imgWidth << "x" << imgHeight << endl;
	}
	else {
		cout << "Fallo en la obtencion de datos de la imagen " << filename << endl;
		return (-1);
	}

	cout << "Hecho\n";

	return textureID;
}
