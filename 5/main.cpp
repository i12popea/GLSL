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
#endif

#include "shader.hpp"

Shader shader;

GLfloat angle = 0.0; //set the angle of rotation

//light position variables
GLfloat lx = -3.0;
GLfloat ly = 1.0;
GLfloat lz = 1.0;
GLfloat lX = 3.0;
GLfloat lY = 1.0;
GLfloat lZ = 1.0;

int LightVector;
int LightColor;
GLfloat LightPosition[] = {lx, ly, lz, lX, lY, lZ}; //set the LightPosition to the specified values
GLfloat LightColorPos[8];// = {1, 0, 0, 0, 1, 0};
//GLfloat LightPosition[] = {lx, ly, lz}; //set the LightPosition to the specified values

void init(void)
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

//	glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);

	shader.init("shader.vert", "shader.frag");
}

void cube (void)
{
	glRotatef(angle, 1.0, 0.0, 0.0); //rotate on the x axis
	glRotatef(angle, 0.0, 1.0, 0.0); //rotate on the y axis
	glRotatef(angle, 0.0, 0.0, 1.0); //rotate on the z axis

	/*GLfloat mShininess[] = {50};

	GLfloat DiffuseMaterial[] = {1.0, 0.0, 0.0};
	GLfloat AmbientMaterial[] = {0.0, 0.0, 0.0};
	GLfloat SpecularMaterial[] = {1.0, 1.0, 1.0};

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, DiffuseMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AmbientMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SpecularMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);*/

	LightVector = glGetUniformLocation(shader.id(), "eyeSpaceLightVector");
	glUniform3fv(LightVector, 2, LightPosition);
	LightColor = glGetUniformLocation(shader.id(), "diffuseColor");
	LightColorPos[0] = 1; LightColorPos[1] = 0; LightColorPos[2] = 0; LightColorPos[3] = 0;
	LightColorPos[4] = 0; LightColorPos[5] = 1; LightColorPos[6] = 0; LightColorPos[7] = 0;
	glUniform4fv(LightColor, 2, LightColorPos);

//	glPushMatrix();
//	glColor3f(1, 1, 0);
	glutSolidTeapot(2);
//	glPopMatrix();
}

void setLighting(void)
{
	/*GLfloat DiffuseLight[] = {1.0, 1.0, 1.0};
	GLfloat AmbientLight[] = {0.2, 0.2, 0.2};
	GLfloat SpecularLight[] = {1.0, 1.0, 1.0};

	glLightfv (GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glLightfv (GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv (GL_LIGHT0, GL_AMBIENT, AmbientLight);*/

	//GLfloat LightPosition[] = {lx, ly, lz, lw}; //set the LightPosition to the specified values
}

void display (void)
{
	glClearColor (0.0,0.0,0.0,1.0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();  
	gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	setLighting();

	shader.bind();
	cube();
	shader.unbind();

	glPushMatrix();
	glTranslatef(LightPosition[0], LightPosition[1], LightPosition[2]);
//	glColor3f(1, 0, 0);
	glColor3f(LightColorPos[0], LightColorPos[1], LightColorPos[2]);
	glutSolidSphere(0.5, 36, 36);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(LightPosition[3], LightPosition[4], LightPosition[5]);
//	glColor3f(0, 1, 0);
	glColor3f(LightColorPos[4], LightColorPos[5], LightColorPos[6]);
	glutSolidSphere(0.5, 36, 36);
	glPopMatrix();

	glutSwapBuffers();
	//angle += 0.1f;
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
