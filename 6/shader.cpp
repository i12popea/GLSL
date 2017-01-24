#include "shader.hpp"


using namespace std;

static char* textFileRead(const char *fileName)
{
	/*char* text;

	if (fileName != NULL)
	{
		FILE *file = fopen(fileName, "rt");

		if (file != NULL)
		{
			fseek(file, 0, SEEK_END);
			int count = ftell(file);
			rewind(file);

			if (count > 0)
			{
				text = (char*)malloc(sizeof(char) * (count + 1));
				count = fread(text, sizeof(char), count, file);
				text[count] = '\0';
			}
			fclose(file);
		}
	}
	return text;*/
	FILE *fp;
	char *content = NULL;

	int count = 0;

	if (fileName != NULL)
	{
		fp = fopen(fileName,"rt");
		if (fp != NULL)
		{
			fseek(fp, 0, SEEK_END);
			count = ftell(fp);
			rewind(fp);

			if (count > 0)
			{
				content = (char *)malloc(sizeof(char) * (count+1));
				count = fread(content,sizeof(char),count,fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	return content;
}

Shader::Shader(){}

Shader::Shader(const char *vsFile, const char *fsFile)
{
	init(vsFile, fsFile);
}

static void validateShader(GLuint shader, const char* file = 0)
{
	const unsigned int BUFFER_SIZE = 512;
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);
	GLsizei length = 0;

	glGetShaderInfoLog(shader, BUFFER_SIZE, &length, buffer);
	if (length > 0)
	{
		cerr << "Shader " << shader << " (" << (file?file:"") << ") compile error: " << buffer << endl;
	}
}

static void validateProgram(GLuint program)
{
	const unsigned int BUFFER_SIZE = 512;
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);
	GLsizei length = 0;

	memset(buffer, 0, BUFFER_SIZE);
	glGetProgramInfoLog(program, BUFFER_SIZE, &length, buffer);
	if (length > 0)
		cerr << "Program " << program << " link error: " << buffer << endl;

	glValidateProgram(program);
	GLint status;
	glGetProgramiv(program, GL_VALIDATE_STATUS, &status);
	if (status == GL_FALSE)
		cerr << "Error validating shader " << program << endl;
}

void Shader::init(const char *vsFile, const char *fsFile)
{
	shader_vp = glCreateShader(GL_VERTEX_SHADER);
	shader_fp = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vsText = textFileRead(vsFile);
	const char* fsText = textFileRead(fsFile);    

	if (vsText == NULL || fsText == NULL)
	{
		cerr << "Either vertex shader or fragment shader file not found." << endl;
		return;
	}

	glShaderSource(shader_vp, 1, &vsText, 0);
	glShaderSource(shader_fp, 1, &fsText, 0);

	glCompileShader(shader_vp);
	validateShader(shader_vp, vsFile);
	glCompileShader(shader_fp);
	validateShader(shader_fp, fsFile);

	shader_id = glCreateProgram();
	glAttachShader(shader_id, shader_fp);
	glAttachShader(shader_id, shader_vp);
	glLinkProgram(shader_id);
	validateProgram(shader_id);
}

void Shader::init1(const char *vsFile1, const char *fsFile1, const char *vsFile2, const char *fsFile2)
{
	unsigned int shader_vp1 = glCreateShader(GL_VERTEX_SHADER);
	unsigned int shader_fp1 = glCreateShader(GL_FRAGMENT_SHADER);
	unsigned int shader_vp2 = glCreateShader(GL_VERTEX_SHADER);
	unsigned int shader_fp2 = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vsText1 = textFileRead(vsFile1);
	const char* fsText1 = textFileRead(fsFile1);    
	const char* vsText2 = textFileRead(vsFile2);
	const char* fsText2 = textFileRead(fsFile2);    

	if (vsText1 == NULL || fsText1 == NULL || vsText2 == NULL || fsText2 == NULL)
	{
		cerr << "Either vertex shader or fragment shader file not found." << endl;
		return;
	}

	glShaderSource(shader_vp1, 1, &vsText1, 0);
	glShaderSource(shader_fp1, 1, &fsText1, 0);
	glShaderSource(shader_vp2, 1, &vsText2, 0);
	glShaderSource(shader_fp2, 1, &fsText2, 0);

	glCompileShader(shader_vp1);
	validateShader(shader_vp1, vsFile1);
	glCompileShader(shader_fp1);
	validateShader(shader_fp1, fsFile1);
	glCompileShader(shader_vp2);
	validateShader(shader_vp2, vsFile2);
	glCompileShader(shader_fp2);
	validateShader(shader_fp2, fsFile2);

	shader_id = glCreateProgram();
	glAttachShader(shader_id, shader_fp1);
	glAttachShader(shader_id, shader_vp1);
	glAttachShader(shader_id, shader_fp2);
	glAttachShader(shader_id, shader_vp2);
	glLinkProgram(shader_id);
	validateProgram(shader_id);
}

Shader::~Shader()
{
	glDetachShader(shader_id, shader_fp);
	glDetachShader(shader_id, shader_vp);

	glDeleteShader(shader_fp);
	glDeleteShader(shader_vp);
	glDeleteProgram(shader_id);
}

unsigned int Shader::id()
{
	return shader_id;
}

unsigned int Shader::vp()
{
	return shader_vp;
}

unsigned int Shader::fp()
{
	return shader_fp;
}

void Shader::bind()
{
	glUseProgram(shader_id);
}

void Shader::unbind()
{
	glUseProgram(0);
}











































/*#include "shader.h"
#include <string.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

static char* textFileRead(const char *fileName) {
    char* text;
    
    if (fileName != NULL) {
        FILE *file = fopen(fileName, “rt”);
        
        if (file != NULL) {
            fseek(file, 0, SEEK_END);
            int count = ftell(file);
            rewind(file);
            
            if (count > 0) {
                text = (char*)malloc(sizeof(char) * (count + 1));
                count = fread(text, sizeof(char), count, file);
                text[count] = ‘\0′;
            }
            fclose(file);
        }
    }
    return text;
}*/
