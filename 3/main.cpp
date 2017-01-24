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
GLfloat lw = 0.0;

void init(void)
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	shader.init("shader.vert", "shader.frag");
	texture = LoadTexture("brickwall.jpg");
	normal_texture = LoadTexture("brickwall_normal.jpg");
}

void cube (void)
{
//	glRotatef(angle, 1.0, 0.0, 0.0); //rotate on the x axis
//	glRotatef(angle, 0.0, 1.0, 0.0); //rotate on the y axis
//	glRotatef(angle, 0.0, 0.0, 1.0); //rotate on the z axis

	/*glActiveTexture(GL_TEXTURE0);
	int texture_location = glGetUniformLocation(shader.id(), "texture_color");
	glUniform1i(texture_location, 0);
	glBindTexture(GL_TEXTURE_2D, texture);*/
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	int texture_location = glGetUniformLocation(shader.id(), "color_texture");
	glUniform1i(texture_location, 0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	int normal_location = glGetUniformLocation(shader.id(), "normal_texture");
	glUniform1i(normal_location, 1);
	glBindTexture(GL_TEXTURE_2D, normal_texture);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 1);
	glDisable(GL_TEXTURE_2D);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

//	glutSolidTeapot(2);
	//glutSolidCube(2);
	//glutSolidTorus(2, 2.5, 50, 50);

	float hd = 1.5;
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glNormal3f(0, 1, 0);
		glVertex3f(-hd,-hd,hd);

		glTexCoord2f(1.0, 0.0);
		//glNormal3f(0, 1, 0);
		glVertex3f(hd,-hd,hd);

		glTexCoord2f(1.0, 1.0);
		//glNormal3f(0, 1, 0);
		glVertex3f(hd,hd,hd);

		glTexCoord2f(0.0, 1.0);
		//glNormal3f(0, 1, 0);
		glVertex3f(-hd,hd,hd);
	glEnd();
}

void setLighting(void)
{
	GLfloat DiffuseLight[] = {1.0, 1.0, 1.0};
	GLfloat AmbientLight[] = {0.2, 0.2, 0.2};
	GLfloat SpecularLight[] = {1.0, 1.0, 1.0};

	glLightfv (GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glLightfv (GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv (GL_LIGHT0, GL_AMBIENT, AmbientLight);

	GLfloat LightPosition[] = {lx, ly, lz, lw}; //set the LightPosition to the specified values

	glLightfv (GL_LIGHT0, GL_POSITION, LightPosition); //change the light accordingly
}

void display (void)
{
	glClearColor (0.0,0.0,0.0,1.0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();  
	gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	//setLighting();

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
