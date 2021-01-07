#include <stdlib.h>
#include <GL/glut.h>
#include "imageloader.h"
#include <iostream>
int _angle_x = 0; // x-axis
int _angle_y = 0; // y
float scal = 0.9; 
GLuint _textureBrick, _textureDoor, _textureGrass, _textureRoof, _textureWindow, _textureSky;

static void resize(int width, int height) //camera stat
{
    const float ar = (float) width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);

    // Sky
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureSky);// pic
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0,0,-10); //
        glBegin(GL_QUADS); //square
            glTexCoord3f(0.0,1.0,0.1);  glVertex3f(-10,10,0); //pos of sky
            glTexCoord3f(1.0,1.0,0.1);  glVertex3f(10,10,0);
            glTexCoord3f(1.0,0.0,0.1);  glVertex3f(10,-10,0);
            glTexCoord3f(0.0,0.0,0.1);  glVertex3f(-10,-10,0);
        glEnd();
    glPopMatrix();

    // Grass
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureGrass);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0,0,-6);

		glRotatef(_angle_x, 1.0, 0.0, 0.0);
		glRotatef(_angle_y, 0.0, 1.0, 0.0); //
		glScalef(scal, scal, scal);

        glBegin(GL_QUADS);
            glTexCoord3f(0.0,70.0,1);  glVertex3f(-50,-1.5,50);
            glTexCoord3f(0.0,0.0,-1);  glVertex3f(-50,-1.5,-50);
            glTexCoord3f(70.0,0.0,-1);  glVertex3f(50,-1.5,-50);
            glTexCoord3f(70.0,70.0,1);  glVertex3f(50,-1.5,50);
        glEnd();
    glPopMatrix();

    // Front side
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureBrick);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0,0,-6); 

		glRotatef(_angle_x, 1.0, 0.0, 0.0);
		glRotatef(_angle_y, 0.0, 1.0, 0.0); //
		glScalef(scal, scal, scal);

        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,2.0,0.1);  glVertex3f(-2,0,1);
            glTexCoord3f(4.0,2.0,0.1);  glVertex3f(2,0,1);
            glTexCoord3f(4.0,0.0,0.1);  glVertex3f(2,-1.5,1);
            glTexCoord3f(0.0,0.0,0.1);  glVertex3f(-2,-1.5,1);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, _textureRoof);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBegin(GL_QUADS);  // Roof
            glTexCoord3f(0.0,2.0,0); glVertex3f(-2.2,0.5,0);
            glTexCoord3f(4.0,2.0,0);glVertex3f(2.2,0.5,0);
            glTexCoord3f(4.0,0.0,1.25); glVertex3f(2.2,-0.1,1.25);
            glTexCoord3f(0.0,0.0,1.25); glVertex3f(-2.2,-0.1,1.25);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, _textureDoor);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBegin(GL_QUADS);  // Door
            glTexCoord3f(0.0,1.0,1.0001); glVertex3f(-0.3,-0.4,1.0001);
            glTexCoord3f(1.0,1.0,1.0001); glVertex3f(0.3,-0.4,1.0001);
            glTexCoord3f(1.0,0.0,1.0001); glVertex3f(0.3,-1.5,1.0001);
            glTexCoord3f(0.0,0.0,1.0001); glVertex3f(-0.3,-1.5,1.0001);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, _textureWindow);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBegin(GL_QUADS);  // Window Left
            glTexCoord3f(0.0,1.0,1.0001); glVertex3f(-1.5,-0.3,1.0001);
            glTexCoord3f(1.0,1.0,1.0001); glVertex3f(-0.75,-0.3,1.0001);
            glTexCoord3f(1.0,0.0,1.0001); glVertex3f(-0.75,-0.8,1.0001);
            glTexCoord3f(0.0,0.0,1.0001); glVertex3f(-1.5,-0.8,1.0001);
        glEnd();

        glBegin(GL_QUADS);  // Window Right
            glTexCoord3f(0.0,1.0,1.0001); glVertex3f(1.5,-0.3,1.0001);
            glTexCoord3f(1.0,1.0,1.0001); glVertex3f(0.75,-0.3,1.0001);
            glTexCoord3f(1.0,0.0,1.0001); glVertex3f(0.75,-0.8,1.0001);
            glTexCoord3f(0.0,0.0,1.0001); glVertex3f(1.5,-0.8,1.0001);
        glEnd();
    glPopMatrix();

    // Back side
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureBrick);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0,0,-6);

		glRotatef(_angle_x, 1.0, 0.0, 0.0);
		glRotatef(_angle_y, 0.0, 1.0, 0.0); //
		glScalef(scal, scal, scal);

        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,2.0,-1);  glVertex3f(-2,0,-1);
            glTexCoord3f(4.0,2.0,-1);  glVertex3f(2,0,-1);
            glTexCoord3f(4.0,0.0,-1);  glVertex3f(2,-1.5,-1);
            glTexCoord3f(0.0,0.0,-1);  glVertex3f(-2,-1.5,-1);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, _textureRoof);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBegin(GL_QUADS);  // Roof
            glTexCoord3f(0.0,2.0,0); glVertex3f(-2.2,0.5,0);
            glTexCoord3f(4.0,2.0,0);glVertex3f(2.2,0.5,0);
            glTexCoord3f(4.0,0.0,-1.25); glVertex3f(2.2,-0.1,-1.25);
            glTexCoord3f(0.0,0.0,-1.25); glVertex3f(-2.2,-0.1,-1.25);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, _textureWindow);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBegin(GL_QUADS);  // Window Left
            glTexCoord3f(0.0,1.0,-1.0001); glVertex3f(-1.5,-0.3,-1.0001);
            glTexCoord3f(1.0,1.0,-1.0001); glVertex3f(-0.75,-0.3,-1.0001);
            glTexCoord3f(1.0,0.0,-1.0001); glVertex3f(-0.75,-0.8,-1.0001);
            glTexCoord3f(0.0,0.0,-1.0001); glVertex3f(-1.5,-0.8,-1.0001);
        glEnd();

        glBegin(GL_QUADS);  // Window Right
            glTexCoord3f(0.0,1.0,1.0001); glVertex3f(1.5,-0.3,-1.0001);
            glTexCoord3f(1.0,1.0,1.0001); glVertex3f(0.75,-0.3,-1.0001);
            glTexCoord3f(1.0,0.0,1.0001); glVertex3f(0.75,-0.8,-1.0001);
            glTexCoord3f(0.0,0.0,1.0001); glVertex3f(1.5,-0.8,-1.0001);
        glEnd();
    glPopMatrix();

    // Right side
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureBrick);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0,0,-6);

        glRotatef(_angle_x, 1.0, 0.0, 0.0);
		glRotatef(_angle_y, 0.0, 1.0, 0.0);
		glScalef(scal,scal,scal);


        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,2.0,1); glVertex3f(2,0,1);
            glTexCoord3f(2.0,2.0,-1); glVertex3f(2,0,-1);
            glTexCoord3f(2.0,0.0,-1); glVertex3f(2,-1.5,-1);
            glTexCoord3f(0.0,0.0,1); glVertex3f(2,-1.5,1);
        glEnd();

        glBegin(GL_TRIANGLES);  // Wall Upper
            glTexCoord3f(0.0,1.0,0); glVertex3f(2,0.5,0);
            glTexCoord3f(1.0,0.0,1); glVertex3f(2,0,1);
            glTexCoord3f(-1.0,0.0,-1); glVertex3f(2,0,-1);
        glEnd();
    glPopMatrix();

    // Left side
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureBrick);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0,0,-6);

		glRotatef(_angle_x, 1.0, 0.0, 0.0);
		glRotatef(_angle_y, 0.0, 1.0, 0.0); //
		glScalef(scal, scal, scal);

        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,2.0,1);    glVertex3f(-2,0,1);
            glTexCoord3f(2.0,2.0,-1);    glVertex3f(-2,0,-1);
            glTexCoord3f(2.0,0.0,-1);    glVertex3f(-2,-1.5,-1);
            glTexCoord3f(0.0,0.0,1);    glVertex3f(-2,-1.5,1);
        glEnd();

        glBegin(GL_TRIANGLES);  // Wall Upper
            glTexCoord3f(0.0,1.0,0);    glVertex3f(-2,0.5,0);
            glTexCoord3f(1.0,0.0,1);    glVertex3f(-2,0,1);
            glTexCoord3f(-1.0,0.0,-1);    glVertex3f(-2,0,-1);
        glEnd();
    glPopMatrix();

    glutSwapBuffers();
}

void mySpecialFunc(int key, int x, int y){ // zooom ,right,left
	switch (key) {

	case GLUT_KEY_PAGE_UP:		if (scal <= 1)			scal += 0.1;		break;	case GLUT_KEY_PAGE_DOWN:		if (scal >= 0)			scal -= 0.1;		break;	case GLUT_KEY_RIGHT:		(_angle_y += 5) %= 360;		break;	case GLUT_KEY_LEFT:		(_angle_y -= 5) %= 360;		break;	case GLUT_KEY_UP:		(_angle_x += 5) %= 360;		break;	case GLUT_KEY_DOWN:		(_angle_x -= 5) %= 360;		break;



	}
	glutPostRedisplay();
}

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

void Initialize() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	Image* image = loadBMP("bricks.bmp");
	_textureBrick = loadTexture(image);
	image = loadBMP("door.bmp");
	_textureDoor = loadTexture(image);
	image = loadBMP("grass.bmp");
	_textureGrass = loadTexture(image);
	image = loadBMP("roof.bmp");
	_textureRoof = loadTexture(image);
	image = loadBMP("window.bmp");
	_textureWindow = loadTexture(image);
	image = loadBMP("sky.bmp");
	_textureSky = loadTexture(image);
	delete image;
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(600,600);
	glutCreateWindow("12th Project");
	glEnable(GL_DEPTH_TEST);


	GLfloat lightpos[] = { 0, 0,  10 };
	GLfloat lightcolor[] = { 255, 102,0 }; 
	GLfloat ambcolor[] = { 0, 0,  1 };
	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambcolor);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightcolor);


	glutReshapeFunc(resize);
	glutSpecialFunc(mySpecialFunc);
	glutDisplayFunc(renderScene);
	Initialize();

	glutMainLoop();

	return 0;
}
