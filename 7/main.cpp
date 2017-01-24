#if ( (defined(__MACH__)) && (defined(__APPLE__)) )   
#include <stdlib.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <OpenGL/glext.h>
#else
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include "textura.hpp"
#endif

#include "shader.hpp"

Shader shader;

int texture;
int normal_texture; // Our normal map texture

GLfloat angle = 0.0; //set the angle of rotation

//light position variables
GLfloat lx = 0.0;
GLfloat ly = 1.0;
GLfloat lz = 1.0;

int LightVector;
int LightColor;
GLfloat LightPosition[] = {lx, ly, lz};
GLfloat LightColorPos[4];

void init(void)
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	shader.init("shader.vert", "shader.frag");
	texture = LoadTexture("crate.jpg");
	normal_texture = LoadTexture("l3d.jpg");
}

void cube (void)
{
	glRotatef(angle, 1.0, 0.0, 0.0); //rotate on the x axis
	glRotatef(angle, 0.0, 1.0, 0.0); //rotate on the y axis
	glRotatef(angle, 0.0, 0.0, 1.0); //rotate on the z axis

	LightVector = glGetUniformLocation(shader.id(), "eyeSpaceLightVector");
	glUniform3fv(LightVector, 1, LightPosition);
	LightColor = glGetUniformLocation(shader.id(), "diffuseColor");
	LightColorPos[0] = 1; LightColorPos[1] = 1; LightColorPos[2] = 1; LightColorPos[3] = 0;
	glUniform4fv(LightColor, 1, LightColorPos);

	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	int texture_location = glGetUniformLocation(shader.id(), "texture1");
	glUniform1i(texture_location, 0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	int normal_location = glGetUniformLocation(shader.id(), "texture2");
	glUniform1i(normal_location, 1);
	glBindTexture(GL_TEXTURE_2D, normal_texture);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 1);
	glDisable(GL_TEXTURE_2D);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	glPushMatrix();
	glTranslatef(0, 0, 0);
	glutSolidTeapot(2);
	glPopMatrix();
}

void display (void)
{
	glClearColor (0.0,0.0,0.0,1.0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();  
	gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	shader.bind();
	cube();
	shader.unbind();

	glutSwapBuffers();
	angle += 0.1f;
}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	glMatrixMode (GL_MODELVIEW);
}

int main (int argc, char **argv)
{
	glutInit(&argc, argv); //set up the double buffering
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("A basic OpenGL Window");

	glewInit();

	glutDisplayFunc(display);
	glutIdleFunc(display);

	glutReshapeFunc(reshape);

	init();

	glutMainLoop();

	return 0;
}
