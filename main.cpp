#include<stdlib.h>
#include<freeglut/glut.h>
#include<stdio.h>
float helispeed = 0.02;
float heli_x = 50.0, heli_y = 0;
float heli = 0.0;
int i = 0, sci = 0;
float scf = 1;
char scs[20];
int wflag = 1;
char gameover[10] = "GAME OVER";
int sc = 0;
void init(void)
{
	heli_y = (rand() % 45) + 10;
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glLoadIdentity();
	glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 0.0);
}
void Helicopter()
{
	glColor3f(0.7, 1.0, 1.0);
	glRectf(10, 49.8, 19.8, 44.8);
	glRectf(2, 46, 10, 48);
	glRectf(2, 46, 4, 51);
	glRectf(14, 49.8, 15.8, 52.2);
	glRectf(7, 53.6, 22.8, 52.2);
}
void renderBitmapString(float x, float y, float z, void* font, char* string)
{
	char* c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *c);
	}
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	if ((i == 360 || i == -350)
		|| (((int)heli_x == 10 || (int)heli_x == 7 || (int)heli_x == 4 || (int)heli_x == 1) && (int)heli_y < 53 + (int)heli && (int)heli_y + 35>53 + (int)heli)
		|| (((int)heli_x == 9 || (int)heli_x == 3 || (int)heli_x == 6) && (int)heli_y < 45 + (int)heli && (int)heli_y + 35>45 + (int)heli)
		|| (((int)heli_x == 0) && (int)heli_y < 46 + (int)heli && (int)heli_y + 35>46 + (int)heli)
		)
	{
		glColor3f(0.8, 0.8, 1.0);
		glRectf(0.0, 0.0, 100.0, 100.0);
		glColor3f(0.0, 0.0, 0.0);
		renderBitmapString(10, 70, 0, GLUT_BITMAP_TIMES_ROMAN_24, gameover);

		glutSwapBuffers();
		glFlush();
		printf("GAME OVER\nYour score was %d\n", sc);
		exit(0);
	}
	else if (wflag == 1)
	{
		wflag = 0;
		glColor3f(0.3, 0.7, 0.2);
		printf("GAME BY IAN, AYUSH and DAKSH\n");
		printf("CLICK SCREEN TO START HELICOPTER\n");
		printf("CLICK AND HOLD LEFT MOUSE BUTTON TO GO UP\n");
		printf("RELEASE MOUSE BUTTON TO GO DOWN\n");
		Helicopter();
		glutSwapBuffers();
		glFlush();
	}
	else
	{
		glPushMatrix();
		glColor3f(0.3, 0.7, 0.2);
		glRectf(0.0, 0.0, 100.0, 10.0);
		glRectf(0.0, 100.0, 100.0, 90.0);
		sc++;
		sci = (int)scf;
		renderBitmapString(20, 3, 0, GLUT_BITMAP_TIMES_ROMAN_24, scs);
		glTranslatef(0.0, heli, 0.0);
		Helicopter();
		if (heli_x < -10)
		{
			heli_x = 50;
			heli_y = (rand() % 25) + 20;
		}
		else heli_x -= helispeed;
		glTranslatef(heli_x, -heli, 0.0);
		glColor3f(1.0, 0.0, 0.0);
		glRectf(heli_x, heli_y, heli_x + 5, heli_y + 35);
		glPopMatrix();
		glutSwapBuffers();
		glFlush();
	}
}
void Heliup()
{
	heli += 0.1;
	i++;
	glutPostRedisplay();
}
void Helidown()
{
	heli -= 0.1;
	i--;
	glutPostRedisplay();
}
void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w, 2.0 * (GLfloat)h / (GLfloat)w, -10.0, 20.0);
	else
		glOrtho(-2.0 * (GLfloat)w / (GLfloat)h, 2.0 * (GLfloat)w / (GLfloat)h, -2.0, 2.0, -10.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}
void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		glutIdleFunc(Heliup);
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
		glutIdleFunc(Helidown);
	glutPostRedisplay();
}
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 400);
	glutInitWindowPosition(200, 300);
	glutCreateWindow("Helicopter Game Project");
	init();
	glutReshapeFunc(Reshape);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMainLoop();
}
