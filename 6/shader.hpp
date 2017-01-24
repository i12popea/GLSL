#ifndef _SHADER_HPP_
#define _SHADER_HPP_

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

class Shader {
private:
	unsigned int shader_id;
	unsigned int shader_vp;
	unsigned int shader_fp;
public:
	Shader();
	Shader(const char *vsFile, const char *fsFile);
	~Shader();

	void init(const char *vsFile, const char *fsFile);
	void init1(const char *vsFile1, const char *fsFile1, const char *vsFile2, const char *fsFile2);
	void bind();
	void unbind();
	unsigned int id();
	unsigned int vp();
	unsigned int fp();
};


#endif
