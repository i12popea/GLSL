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
Shader luz;
Shader light;

int texture;

GLfloat angle = 0.0; //set the angle of rotation

//light position variables
GLfloat lx = -6.0;
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

	light.init("lightshader.vert", "lightshader.frag");
	texture = LoadTexture("squirrel.jpg");
}

void cube (void)
{
	/*glRotatef(angle, 1.0, 0.0, 0.0); //rotate on the x axis
	glRotatef(angle, 0.0, 1.0, 0.0); //rotate on the y axis
	glRotatef(angle, 0.0, 0.0, 1.0); //rotate on the z axis*/

	LightVector = glGetUniformLocation(light.id(), "eyeSpaceLightVector");
	glUniform3fv(LightVector, 1, LightPosition);
	LightColor = glGetUniformLocation(light.id(), "diffuseColor");
	LightColorPos[0] = 1; LightColorPos[1] = 0; LightColorPos[2] = 0; LightColorPos[3] = 0;
	glUniform4fv(LightColor, 1, LightColorPos);

	/*LightVector = glGetUniformLocation(light.id(), "eyeSpaceLightVector");
	glUniform3fv(LightVector, 1, LightPosition);
	LightColor = glGetUniformLocation(light.id(), "diffuseColor");
	LightColorPos[0] = 1; LightColorPos[1] = 1; LightColorPos[2] = 1; LightColorPos[3] = 0;
	glUniform4fv(LightColor, 1, LightColorPos);*/

	glActiveTexture(GL_TEXTURE0);
	int texture_location = glGetUniformLocation(light.id(), "texture_color");
	glUniform1i(texture_location, texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	/*glActiveTexture(GL_TEXTURE0);
	int texture_location = glGetUniformLocation(shader.id(), "texture_color");
	glUniform1i(texture_location, 0);
	glBindTexture(GL_TEXTURE_2D, texture);*/

	glutSolidTeapot(2);
}

void setLighting(void)
{
}

void display (void)
{
	glClearColor (0.0,0.0,0.0,1.0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();  
	gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

//	shader.bind();
	light.bind();
	cube();
//	shader.unbind();
	light.unbind();

	glPushMatrix();
	glTranslatef(LightPosition[0], LightPosition[1], LightPosition[2]);
	glColor3f(LightColorPos[0], LightColorPos[1], LightColorPos[2]);
	glutSolidSphere(0.5, 36, 36);
	glPopMatrix();

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
