/*
	program 6
*/

#include "GL/glut.h"
#include "GL/glui.h"
#include <math.h>
#include <stdio.h>
#include <iostream>

//#include <iostream>

float mouseX;
float mouseY;

//default cycle
const int n = 100;
GLfloat R = 0.5f;
const GLfloat pi = 3.1415926536f;

//submenue
static int submenu1;
int choice;

//find point position
float dis;
float midpoint[2];

// draw points
float vertex[30][3];
float pos[3];
int count = 0;

//rotate
float startX, startY;
float endX, endY;
float disX, disY;
float X, Y;

float clickX, clickY;
float centerX, centerY;

//move
bool found = false;
int num = 0;

//arc
float dot;
float degree;
bool show = false;

//
float t = 0.5;
float F[3];
bool five = false;
bool six = false;
bool seven = false;
bool eight = false;
bool nine = false;
bool ten = false;
bool eleven = false;
bool twelve = false;

float s = 0.5;

//HERMITE’S PROBLEM
int con;
float p[30][3][3];
int pcount = 0;
int count2 = 0;
int count3 = 0;
int num1;
int num2;

float all[30][90][3];
bool shownine = false;


void menu(int num) {  // num: id of the added item
	//printf("menu called with arg %d\n", num);
	if (num == 0) {
		choice == 0;

		for (int i = 0; i < count; i++) {
			vertex[i][0] = NULL;
			vertex[i][1] = NULL;
			vertex[i][2] = NULL;
		}
		count = 0;

		startX, startY = 0.0;
		endX, endY = 0.0;
		disX, disY = 0.0;
		X, Y = 0.0;

		show = false;
		five = false;
		six = false;
		seven = false;
		eight = false;
		nine = false;
		ten = false;
		eleven = false;
		twelve = false;
		shownine = false;

		F[0] = F[1] = F[2] = NULL;

		t = 0.5;

		for (int i = 0; i < count2; i++) {
			p[i][0][0] = NULL;
			p[i][0][1] = NULL;
			p[i][0][2] = NULL;
			p[i][1][0] = NULL;
			p[i][1][1] = NULL;
			p[i][1][2] = NULL;
			p[i][2][0] = NULL;
			p[i][2][1] = NULL;
			p[i][2][2] = NULL;
		}
		pcount = 0;
		count2 = 0;
		count3 = 0;

		glutPostRedisplay();
	}
	else if (num == 1) {
		choice = 1;
	}
	else if (num == 2) {
		choice = 2;
		show = true;
		glutPostRedisplay();
	}
	else if (num == 3) {
		exit(0);
	}
	else if (num == 4) {
		choice = 4;
		show = false;
		glutPostRedisplay();
	}
	else if (num == 5) {
		choice = 5;
		if (five == false) {
			five = true;
			printf("Show lines\n");
		}
		else {
			five = false;
			printf("Hide lines\n");
		}
		glutPostRedisplay();
	}
	else if (num == 6) {
		choice = 6;
		if (six == false) {
			six = true;
			printf("Show F(t)\n");
		}
		else {
			six = false;
			printf("Hide F(t)\n");
		}
		glutPostRedisplay();
	}
	else if (num == 7) {
		choice = 7;
		if (seven == false) {
			seven = true;
			printf("Show curve\n");
		}
		else {
			seven = false;
			printf("Hide curve\n");
		}
		glutPostRedisplay();
	}
	else if (num == 8) {
		choice = 8;
		if (eight == false) {
			eight = true;
			printf("Using UP and DOWN key to change t value\n");			
		}
		else {
			eight = false;
			printf("Stop changing t\n");
		}
		glutPostRedisplay();
	}
	/*
	else if (num == 9) {
		choice = 9;
		nine = true;
		glutPostRedisplay();
	}
	else if (num == 10) {
		choice = 10;
		ten = true;
		glutPostRedisplay();
	}
	else if (num == 11) {
		choice = 11;
		eleven = true;
		glutPostRedisplay();
	}
	else if (num == 12) {
		choice = 12;
		twelve = true;
		glutPostRedisplay();
	}
	*/
}

void createMenu(void) {
	submenu1 = glutCreateMenu(menu);     // create menu, assign a callback
	glutAddMenuEntry("Show lines", 5);
	glutAddMenuEntry("Show F(t)", 6);
	glutAddMenuEntry("Show curve", 7);
	glutAddMenuEntry("Change t", 8);

	glutCreateMenu(menu);
	glutAddMenuEntry(" CLEAR ", 0);
	glutAddMenuEntry(" ADJUST ", 1);
	glutAddMenuEntry(" SHOW POLYGON ", 2);
	glutAddMenuEntry(" Hide POLYGON ", 4);
	glutAddSubMenu(" DECASTELJAU ", submenu1);
	//glutAddMenuEntry(" Cut off left ", 9);
	//glutAddMenuEntry(" Cut off right ", 10);
	//glutAddMenuEntry(" Extend left ", 11);
	//glutAddMenuEntry(" Extend right ", 12);
	//glutAddMenuEntry(" EXIT ", 3);

	glutAttachMenu(GLUT_RIGHT_BUTTON);  // bind to the event: clicking the right button
}


void mouseClick(int button, int state, int x, int y)
{
	mouseX = x;
	mouseY = y;

	for (int x = 1; x < count3; x++) {
		dot = p[x][0][0] * p[x][1][0] + p[x][0][1] * p[x][1][1] + p[x][0][2] * p[x][1][2];
		degree = acos(dot);
		float temp[3];
		float a;
		float b;
		float j = -1;
		a = sin((1.0 - j) * degree) / sin(degree);
		b = sin(j * degree) / sin(degree);
		temp[0] = a * p[x][0][0] + b * p[x][1][0];
		temp[1] = a * p[x][0][1] + b * p[x][1][1];
		temp[2] = a * p[x][0][2] + b * p[x][1][2];
		p[x][2][0] = temp[0];
		p[x][2][1] = temp[1];
		p[x][2][2] = temp[2];
	}


	if (button == GLUT_LEFT_BUTTON) {
		if (con == 5) {
			if (state == GLUT_UP) {
				pos[0] = (mouseX - midpoint[0]) / (dis / 2);
				pos[1] = (midpoint[1] - mouseY) / (dis / 2);
				pos[2] = sqrtf(1 - powf(pos[0], 2) - powf(pos[1], 2));
				if ((powf(pos[0], 2) + powf(pos[1], 2)) > (1)) {
					printf("point is not on the sphere\n");
				}
				else {
					if (count2 < 30) {
						p[count2][0][0] = pos[0];
						p[count2][0][1] = pos[1];
						p[count2][0][2] = -pos[2];
						count2++;
						glutPostRedisplay();
					}
					else if (count2 >= 30) {
						printf("The count of points meets the maximum limition!\n");
					}
				}
			}
		}
		else if (con == 6) {
			if (state == GLUT_UP) {
				pos[0] = (mouseX - midpoint[0]) / (dis / 2);
				pos[1] = (midpoint[1] - mouseY) / (dis / 2);
				pos[2] = sqrtf(1 - powf(pos[0], 2) - powf(pos[1], 2));
				if ((powf(pos[0], 2) + powf(pos[1], 2)) > (1)) {
					printf("point is not on the sphere\n");
				}
				else {
					p[count3][1][0] = pos[0];
					p[count3][1][1] = pos[1];
					p[count3][1][2] = -pos[2];
					count3++;
					glutPostRedisplay();
				}
			}
		}
		else if (con == 8) {
			if (state == GLUT_DOWN) {
				if (count3 > 0) {
					pos[0] = (mouseX - midpoint[0]) / (dis / 2);
					pos[1] = (midpoint[1] - mouseY) / (dis / 2);
					pos[2] = sqrtf(1 - powf(pos[0], 2) - powf(pos[1], 2));

					num1 = 0;
					num2 = 1;

					float min = sqrtf(powf((p[0][1][0] - pos[0]), 2) + powf((p[0][1][1] - pos[1]), 2));

					for (int i = 1; i < count3; i++) {
						float temp = sqrtf(powf((p[i][1][0] - pos[0]), 2) + powf((p[i][1][1] - pos[1]), 2));
						if (temp < min) {
							min = temp;
							num1 = i;
							num2 = 1;
						}
						temp = sqrtf(powf((p[i][2][0] - pos[0]), 2) + powf((p[i][2][1] - pos[1]), 2));
						if (temp < min) {
							min = temp;
							num1 = i;
							num2 = 2;
						}
					}
					//printf("min is %f\n", min);
					if (min <= 0.002) {
						//printf("point found\n");
						found = true;
					}
				}
			}
		}
		int mod = glutGetModifiers();
		if (choice == 1 || show == true) {
			if (state == GLUT_DOWN) {
				if (mod == GLUT_ACTIVE_CTRL) {
					//printf("finding point\n");
					if (count > 0) {
						pos[0] = (mouseX - midpoint[0]) / (dis / 2);
						pos[1] = (midpoint[1] - mouseY) / (dis / 2);
						pos[2] = sqrtf(1 - powf(pos[0], 2) - powf(pos[1], 2));

						num = 0;

						float min = sqrtf(powf((vertex[0][0] - pos[0]), 2) + powf((vertex[0][1] - pos[1]), 2));

						for (int i = 0; i < count; i++) {
							float temp = sqrtf(powf((vertex[i][0] - pos[0]), 2) + powf((vertex[i][1] - pos[1]), 2));
							if (temp < min && vertex[i][2] <= 0) {
								min = temp;
								num = i;
							}
						}
						//printf("min is %f\n", min);
						if (min <= 0.02) {
							//printf("point found\n");
							found = true;
						}
					}
				}
			}
			else if (state == GLUT_UP) {
				if (mod == GLUT_ACTIVE_SHIFT) {
					pos[0] = (mouseX - midpoint[0]) / (dis / 2);
					pos[1] = (midpoint[1] - mouseY) / (dis / 2);
					pos[2] = sqrtf(1 - powf(pos[0], 2) - powf(pos[1], 2));
					if ((powf(pos[0], 2) + powf(pos[1], 2)) > (1)) {
						printf("point is not on the sphere\n");
					}
					else {
						if (count < 30) {
							vertex[count][0] = pos[0];
							vertex[count][1] = pos[1];
							vertex[count][2] = -pos[2];
							count++;
							glutPostRedisplay();
						}
						else if (count >= 30) {
							printf("The count of points meets the maximum limition!\n");
						}
					}
				}
				else if (mod == GLUT_ACTIVE_SHIFT + GLUT_ACTIVE_CTRL) {
					if (count > 0) {
						pos[0] = (mouseX - midpoint[0]) / (dis / 2);
						pos[1] = (midpoint[1] - mouseY) / (dis / 2);
						pos[2] = sqrtf(1 - powf(pos[0], 2) - powf(pos[1], 2));

						num = 0;
						float min = sqrtf(powf((vertex[0][0] - pos[0]), 2) + powf((vertex[0][1] - pos[1]), 2));
						//printf("(%f, %f, %f)\n", vertex[0][0], vertex[0][1], vertex[0][2]);
						//printf("(%f, %f, %f)\n", pos[0], pos[1], pos[2]);

						for (int i = 0; i < count; i++) {
							float temp = sqrtf(powf((vertex[i][0] - pos[0]), 2) + powf((vertex[i][1] - pos[1]), 2));
							if (temp < min && vertex[i][2] <= 0) {
								min = temp;
								num = i;
							}
						}
						//printf("min is %f\n", min);
						if (min <= 0.01) {
							for (int j = num; j < count - 1; j++) {
								vertex[j][0] = vertex[j + 1][0];
								vertex[j][1] = vertex[j + 1][1];
								vertex[j][2] = vertex[j + 1][2];
							}
							count--;
							glutPostRedisplay();
						}

					}
				}
				else if (mod == GLUT_ACTIVE_CTRL) {
					found = false;
				}
				else if (con == 8) {
					found = false;
				}
			}
		}
	}
}

void motion(int x, int y)
{
	int mod = glutGetModifiers();
	if (choice == 1 || show == true) {
		if (mod == GLUT_ACTIVE_CTRL) {
			if (found == true) {
				mouseX = x;
				mouseY = y;

				//printf("moving point\n");
				pos[0] = (mouseX - midpoint[0]) / (dis / 2);
				pos[1] = (midpoint[1] - mouseY) / (dis / 2);
				pos[2] = sqrtf(1 - powf(pos[0], 2) - powf(pos[1], 2));

				vertex[num][0] = pos[0];
				vertex[num][1] = pos[1];
				vertex[num][2] = -pos[2];

				glutPostRedisplay();
			}
		}
	}
	else if (con == 8) {
		if (found == true) {
			mouseX = x;
			mouseY = y;

			//printf("moving point\n");
			pos[0] = (mouseX - midpoint[0]) / (dis / 2);
			pos[1] = (midpoint[1] - mouseY) / (dis / 2);
			pos[2] = sqrtf(1 - powf(pos[0], 2) - powf(pos[1], 2));

			p[num1][num2][0] = pos[0];
			p[num1][num2][1] = pos[1];
			p[num1][num2][2] = -pos[2];

			glutPostRedisplay();
		}
	}
}

void SpecialKey(GLint key, GLint x, GLint y)
{
	if (eight == true) {
		if (key == GLUT_KEY_UP)
		{
			t += 0.003;
		}

		if (key == GLUT_KEY_DOWN)
		{
			t -= 0.003;
		}
		printf("t is %f\n", t);
		glutPostRedisplay();
	}
}

void control_cb(int control) {

	t = s;
	if (s > 1) {
		s = 1 / s;
	}
	else if (s < 0) {
		s = -s;
		if (s > 1) {
			s = 1 / s;
		}
	}
	GLUI_Master.sync_live_all();
	if (control == 1) {
		choice = 9;
		nine = true;
		glutPostRedisplay();
	}
	else if (control == 2) {
		choice = 10;
		ten = true;
		glutPostRedisplay();
	}
	else if (control == 3) {
		choice = 11;
		eleven = true;
		glutPostRedisplay();
	}
	else if (control == 4) {
		choice = 12;
		twelve = true;
		glutPostRedisplay();
	}
	else if (control == 5) {
		con = 5;
		glutPostRedisplay();
	}
	else if (control == 6) {
		con = 6;
		glutPostRedisplay();
	}
	else if (control == 7) {
		con = 7;
		glutPostRedisplay();
	}
	else if (control == 8) {
		con = 8;
		glutPostRedisplay();
	}
	else if (control == 9) {
		con = 9;
		glutPostRedisplay();
	}
}


void init(void)

{
	GLfloat a[] = { 0.4,0.4,0.4,1 };     
	GLfloat d[] = { 0.6,0.6,0.6,1 };         
	GLfloat s[] = { 0.6,0.6,0.6,1 };       
	GLfloat p[] = { 1,1,-3,1 };  
	
	glMatrixMode(GL_MODELVIEW);

	glLightfv(GL_LIGHT0, GL_AMBIENT, a); 	
	glLightfv(GL_LIGHT0, GL_DIFFUSE, d);
	glLightfv(GL_LIGHT0, GL_SPECULAR, s);
	glLightfv(GL_LIGHT0, GL_POSITION, p);  


	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);

	glEnable(GL_DEPTH_TEST);
}

int fac(int n) {
	if (n == 1 || n == 0) { 
		return 1; 
	}
	else { 
		return n * fac(n - 1); 
	}
}

void myDisplay(void)

{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glutSolidSphere(1, 40, 50);

	glDisable(GL_LIGHTING);
	
	//glutPostRedisplay();

	float allPoints[30][30][3];
	for (int i = 0; i < count; i++) {
		allPoints[0][i][0] = vertex[i][0];
		allPoints[0][i][1] = vertex[i][1];
		allPoints[0][i][2] = vertex[i][2];
	}
	int number = count - 1;


	for (int i = 1; i < count; i++) {
		for (int j = 0; j < number; j++) {
			float dotp = allPoints[i - 1][j][0] * allPoints[i - 1][j + 1][0] + allPoints[i - 1][j][1] * allPoints[i - 1][j + 1][1] + allPoints[i - 1][j][2] * allPoints[i - 1][j + 1][2];
			float angle = acos(dotp);
			float A = sin((1 - t) * angle) / sin(angle);
			float B = sin(t * angle) / sin(angle);
			allPoints[i][j][0] = A * allPoints[i - 1][j][0] + B * allPoints[i - 1][j + 1][0];
			allPoints[i][j][1] = A * allPoints[i - 1][j][1] + B * allPoints[i - 1][j + 1][1];
			allPoints[i][j][2] = A * allPoints[i - 1][j][2] + B * allPoints[i - 1][j + 1][2];
		}
		number--;
	}

	if (choice == 2 || show == true) {
		if (ten == true) {
			number = count - 1;
			for (int x = 0; x < count; x++) {
				vertex[x][0] = allPoints[x][0][0];
				vertex[x][1] = allPoints[x][0][1];
				vertex[x][2] = allPoints[x][0][2];
				number--;
			}
			ten = false;
		}
		else if (nine == true) {
			number = count - 1;
			for (int x = 0; x < count; x++) {
				vertex[number][0] = allPoints[x][number][0];
				vertex[number][1] = allPoints[x][number][1];
				vertex[number][2] = allPoints[x][number][2];
				number--;
			}
			nine = false;
		}
		else if (eleven == true) {

			number = count - 1;
			for (int x = 0; x < count; x++) {
				vertex[number][0] = allPoints[x][number][0];
				vertex[number][1] = allPoints[x][number][1];
				vertex[number][2] = allPoints[x][number][2];
				number--;
			}
			
			eleven = false;
		}
		else if (twelve == true) {

			number = count - 1;
			for (int x = 0; x < count; x++) {
				vertex[x][0] = allPoints[x][0][0];
				vertex[x][1] = allPoints[x][0][1];
				vertex[x][2] = allPoints[x][0][2];
				number--;
			}

			twelve = false;
		}
		for (int i = 0; i < count - 1; i++) {
			//printf("outer for loop\n");
			dot = vertex[i][0] * vertex[i + 1][0] + vertex[i][1] * vertex[i + 1][1] + vertex[i][2] * vertex[i + 1][2];
			degree = acos(dot);
			float temp[3];
			float a;
			float b;
			glColor3f(1.0, 0.0, 0.0);
			glBegin(GL_LINE_LOOP);
			float j = 0;
			while (j <= 1) {
				//printf("inner for loop\n");
				a = sin((1.0 - j) * degree) / sin(degree);
				b = sin(j * degree) / sin(degree);
				temp[0] = a * vertex[i][0] + b * vertex[i + 1][0];
				temp[1] = a * vertex[i][1] + b * vertex[i + 1][1];
				temp[2] = a * vertex[i][2] + b * vertex[i + 1][2];
				glVertex3f(temp[0], temp[1], temp[2]);
				j = j + 0.001;
			}
			glEnd();
		}
	}

	for (int i = 0; i < count; i++) {
		glColor3f(0.0, 1.0, 0.0);
		glPointSize(5.0);
		glBegin(GL_POINTS);
		glVertex3f(vertex[i][0], vertex[i][1], vertex[i][2]);
		glEnd();
	}

	if (t > 1) {
		t = 1 / t;
	}
	else if (t < 0) {
		t = -t;
		if (t > 1) {
			t = 1 / t;
		}
	}

	for (int i = 0; i < count; i++) {
		allPoints[0][i][0] = vertex[i][0];
		allPoints[0][i][1] = vertex[i][1];
		allPoints[0][i][2] = vertex[i][2];
	}
	number = count - 1;
	for (int i = 1; i < count; i++) {
		for (int j = 0; j < number; j++) {
			float dotp = allPoints[i - 1][j][0] * allPoints[i - 1][j + 1][0] + allPoints[i - 1][j][1] * allPoints[i - 1][j + 1][1] + allPoints[i - 1][j][2] * allPoints[i - 1][j + 1][2];
			float angle = acos(dotp);
			float A = sin((1 - t) * angle) / sin(angle);
			float B = sin(t * angle) / sin(angle);
			allPoints[i][j][0] = A * allPoints[i - 1][j][0] + B * allPoints[i - 1][j + 1][0];
			allPoints[i][j][1] = A * allPoints[i - 1][j][1] + B * allPoints[i - 1][j + 1][1];
			allPoints[i][j][2] = A * allPoints[i - 1][j][2] + B * allPoints[i - 1][j + 1][2];
			if (number == 1) {
				F[0] = allPoints[i][j][0];
				F[1] = allPoints[i][j][1];
				F[2] = allPoints[i][j][2];
			}
		}
		number--;
	}
	
	if (six == true) {

		glColor3f(1.0, 0.0, 0.0);
		glPointSize(5.0);
		glBegin(GL_POINTS);
		glVertex3f(F[0], F[1], F[2]);
		glEnd();
	}

	if (five == true) {
			number = count - 1;
			for (int x = 1; x < count; x++) {
				for (int y = 0; y < number; y++) {
					glColor3f(0.0, 1.0, 1.0);
					glPointSize(5.0);
					glBegin(GL_POINTS);
					glVertex3f(allPoints[x][y][0], allPoints[x][y][1], allPoints[x][y][2]);
					glEnd();
				}
				number--;
			}


			number = count - 1;
			for (int x = 1; x < count; x++) {

				for (int y = 0; y < number; y++) {
					dot = allPoints[x][y][0] * allPoints[x][y + 1][0] + allPoints[x][y][1] * allPoints[x][y + 1][1] + allPoints[x][y][2] * allPoints[x][y + 1][2];
					degree = acos(dot);
					float temp[3];
					float a;
					float b;
					glColor3f(0.0, 1.0, 0.0);
					glBegin(GL_LINE_LOOP);
					float j = 0;
					while (j <= 1) {
						//printf("inner for loop\n");
						a = sin((1.0 - j) * degree) / sin(degree);
						b = sin(j * degree) / sin(degree);
						temp[0] = a * allPoints[x][y][0] + b * allPoints[x][y + 1][0];
						temp[1] = a * allPoints[x][y][1] + b * allPoints[x][y + 1][1];
						temp[2] = a * allPoints[x][y][2] + b * allPoints[x][y + 1][2];
						glVertex3f(temp[0], temp[1], temp[2]);
						j = j + 0.001;
					}
					glEnd();
				}
				number--;
			}
	}

	if (seven == true) {
		//printf("enter 7\n");
		glColor3f(0.0, 1.0, 1.0);
		glBegin(GL_LINE_LOOP);
		float p = 0;
		float end = 1;
		if (nine == true) {
			end = 1;
			p = t;
		}
		else if (ten == true) {
			end = t;
			printf("t is %f\n", t);
		}
		while (p < end) {
			float allPoints[30][30][3];
			for (int i = 0; i < count; i++) {
				allPoints[0][i][0] = vertex[i][0];
				allPoints[0][i][1] = vertex[i][1];
				allPoints[0][i][2] = vertex[i][2];
			}
			int number = count - 1;
			float V[3];
			for (int i = 1; i < count; i++) {
				for (int j = 0; j < number; j++) {
					float dotp = allPoints[i - 1][j][0] * allPoints[i - 1][j + 1][0] + allPoints[i - 1][j][1] * allPoints[i - 1][j + 1][1] + allPoints[i - 1][j][2] * allPoints[i - 1][j + 1][2];
					float angle = acos(dotp);
					float A = sin((1 - p) * angle) / sin(angle);
					float B = sin(p * angle) / sin(angle);
					allPoints[i][j][0] = A * allPoints[i - 1][j][0] + B * allPoints[i - 1][j + 1][0];
					allPoints[i][j][1] = A * allPoints[i - 1][j][1] + B * allPoints[i - 1][j + 1][1];
					allPoints[i][j][2] = A * allPoints[i - 1][j][2] + B * allPoints[i - 1][j + 1][2];
					if (number == 1) {
						V[0] = allPoints[i][j][0];
						V[1] = allPoints[i][j][1];
						V[2] = allPoints[i][j][2];
					}
				}
				number--;
			}
			glVertex3f(V[0], V[1], V[2]);
			p = p + 0.001;
		}
		glEnd();
		
	}

	for (int i = 0; i < count2; i++) {
		glColor3f(0.0, 1.0, 0.0);
		glPointSize(5.0);
		glBegin(GL_POINTS);
		glVertex3f(p[i][0][0], p[i][0][1], p[i][0][2]);
		glEnd();
	}
	for (int x = 1; x < count3; x++) {
		dot = p[x][0][0] * p[x][1][0] + p[x][0][1] * p[x][1][1] + p[x][0][2] * p[x][1][2];
		degree = acos(dot);
		float temp[3];
		float a;
		float b;
		float j = -1;
		a = sin((1.0 - j) * degree) / sin(degree);
		b = sin(j * degree) / sin(degree);
		temp[0] = a * p[x][0][0] + b * p[x][1][0];
		temp[1] = a * p[x][0][1] + b * p[x][1][1];
		temp[2] = a * p[x][0][2] + b * p[x][1][2];
		p[x][2][0] = temp[0];
		p[x][2][1] = temp[1];
		p[x][2][2] = temp[2];
	}

	for (int x = 0; x < count3; x++) {
		dot = p[x][0][0] * p[x][1][0] + p[x][0][1] * p[x][1][1] + p[x][0][2] * p[x][1][2];
		degree = acos(dot);
		float temp[3];
		float a;
		float b;
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_LINE_LOOP);
		float j = 0;
		while (j <= 1) {
			a = sin((1.0 - j) * degree) / sin(degree);
			b = sin(j * degree) / sin(degree);
			temp[0] = a * p[x][0][0] + b * p[x][1][0];
			temp[1] = a * p[x][0][1] + b * p[x][1][1];
			temp[2] = a * p[x][0][2] + b * p[x][1][2];
			glVertex3f(temp[0], temp[1], temp[2]);
			j = j + 0.001;
		}
		glEnd();
	}


	if (con == 7 || con == 8) {
		glColor3f(1.0, 0.0, 0.0);
		glPointSize(5.0);
		glBegin(GL_POINTS);
		glVertex3f(p[0][1][0], p[0][1][1], p[0][1][2]);
		glEnd();
		for (int i = 1; i < count3; i++) {
			glColor3f(1.0, 0.0, 0.0);
			glPointSize(5.0);
			glBegin(GL_POINTS);
			glVertex3f(p[i][1][0], p[i][1][1], p[i][1][2]);
			glVertex3f(p[i][2][0], p[i][2][1], p[i][2][2]);
			glEnd();
		}
		for (int x = 0; x < count3-1; x++) {
			dot = p[x][1][0] * p[x+1][2][0] + p[x][1][1] * p[x+1][2][1] + p[x][1][2] * p[x+1][2][2];
			degree = acos(dot);
			float temp[3];
			float a;
			float b;
			glColor3f(0.0, 0.0, 0.0);
			glBegin(GL_LINE_LOOP);
			float j = 0;
			while (j <= 1) {
				a = sin((1.0 - j) * degree) / sin(degree);
				b = sin(j * degree) / sin(degree);
				temp[0] = a * p[x][1][0] + b * p[x+1][2][0];
				temp[1] = a * p[x][1][1] + b * p[x+1][2][1];
				temp[2] = a * p[x][1][2] + b * p[x+1][2][2];
				glVertex3f(temp[0], temp[1], temp[2]);
				j = j + 0.001;
			}
			glEnd();

			dot = p[x+1][2][0] * p[x+1][0][0] + p[x+1][2][1] * p[x+1][0][1] + p[x+1][2][2] * p[x+1][0][2];
			degree = acos(dot);

			glColor3f(0.0, 0.0, 0.0);
			glBegin(GL_LINE_LOOP);
			j = 0;
			while (j <= 1) {
				a = sin((1.0 - j) * degree) / sin(degree);
				b = sin(j * degree) / sin(degree);
				temp[0] = a * p[x + 1][2][0] + b * p[x + 1][0][0];
				temp[1] = a * p[x + 1][2][1] + b * p[x + 1][0][1];
				temp[2] = a * p[x + 1][2][2] + b * p[x + 1][0][2];
				glVertex3f(temp[0], temp[1], temp[2]);
				j = j + 0.001;
			}
			glEnd();
		}
	}

	if (con == 9 || shownine == true) {
		shownine = true;
		glColor3f(1.0, 0.0, 0.0);
		glPointSize(5.0);
		glBegin(GL_POINTS);
		glVertex3f(p[0][1][0], p[0][1][1], p[0][1][2]);
		glEnd();
		for (int i = 1; i < count3; i++) {
			glColor3f(1.0, 0.0, 0.0);
			glPointSize(5.0);
			glBegin(GL_POINTS);
			glVertex3f(p[i][1][0], p[i][1][1], p[i][1][2]);
			glVertex3f(p[i][2][0], p[i][2][1], p[i][2][2]);
			glEnd();
		}
		for (int x = 0; x < count3 - 1; x++) {
			dot = p[x][1][0] * p[x + 1][2][0] + p[x][1][1] * p[x + 1][2][1] + p[x][1][2] * p[x + 1][2][2];
			degree = acos(dot);
			float temp[3];
			float a;
			float b;
			glColor3f(0.0, 0.0, 0.0);
			glBegin(GL_LINE_LOOP);
			float j = 0;
			while (j <= 1) {
				a = sin((1.0 - j) * degree) / sin(degree);
				b = sin(j * degree) / sin(degree);
				temp[0] = a * p[x][1][0] + b * p[x + 1][2][0];
				temp[1] = a * p[x][1][1] + b * p[x + 1][2][1];
				temp[2] = a * p[x][1][2] + b * p[x + 1][2][2];
				glVertex3f(temp[0], temp[1], temp[2]);
				j = j + 0.001;
			}
			glEnd();

			dot = p[x + 1][2][0] * p[x + 1][0][0] + p[x + 1][2][1] * p[x + 1][0][1] + p[x + 1][2][2] * p[x + 1][0][2];
			degree = acos(dot);

			glColor3f(0.0, 0.0, 0.0);
			glBegin(GL_LINE_LOOP);
			j = 0;
			while (j <= 1) {
				a = sin((1.0 - j) * degree) / sin(degree);
				b = sin(j * degree) / sin(degree);
				temp[0] = a * p[x + 1][2][0] + b * p[x + 1][0][0];
				temp[1] = a * p[x + 1][2][1] + b * p[x + 1][0][1];
				temp[2] = a * p[x + 1][2][2] + b * p[x + 1][0][2];
				glVertex3f(temp[0], temp[1], temp[2]);
				j = j + 0.001;
			}
			glEnd();
		}

		

		for (int a = 0; a < count2-1; a++) {
			glColor3f(0.0, 1.0, 0.0);
			glBegin(GL_LINE_LOOP);
			float s = 0;
			
			while (s < 1) {
				float allPoints[30][30][3];
				allPoints[0][0][0] = p[a][0][0];
				allPoints[0][0][1] = p[a][0][1];
				allPoints[0][0][2] = p[a][0][2];

				allPoints[0][1][0] = p[a][1][0];
				allPoints[0][1][1] = p[a][1][1];
				allPoints[0][1][2] = p[a][1][2];

				allPoints[0][2][0] = p[a+1][2][0];
				allPoints[0][2][1] = p[a+1][2][1];
				allPoints[0][2][2] = p[a+1][2][2];

				allPoints[0][3][0] = p[a+1][0][0];
				allPoints[0][3][1] = p[a+1][0][1];
				allPoints[0][3][2] = p[a+1][0][2];

				int number = 3;
				float V[3];
				for (int i = 1; i < 4; i++) {
					for (int j = 0; j < number; j++) {
						float dotp = allPoints[i - 1][j][0] * allPoints[i - 1][j + 1][0] + allPoints[i - 1][j][1] * allPoints[i - 1][j + 1][1] + allPoints[i - 1][j][2] * allPoints[i - 1][j + 1][2];
						float angle = acos(dotp);
						float A = sin((1 - s) * angle) / sin(angle);
						float B = sin(s * angle) / sin(angle);
						allPoints[i][j][0] = A * allPoints[i - 1][j][0] + B * allPoints[i - 1][j + 1][0];
						allPoints[i][j][1] = A * allPoints[i - 1][j][1] + B * allPoints[i - 1][j + 1][1];
						allPoints[i][j][2] = A * allPoints[i - 1][j][2] + B * allPoints[i - 1][j + 1][2];
						if (number == 1) {
							V[0] = allPoints[i][j][0];
							V[1] = allPoints[i][j][1];
							V[2] = allPoints[i][j][2];
						}
					}
					number--;
				}
				glVertex3f(V[0], V[1], V[2]);
				s = s + 0.001;
			}
			glEnd();
		}
	}



	glEnable(GL_LIGHTING);
	glPopMatrix();

	glDisable(GL_LIGHTING);

	//longitude 
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINE_LOOP);
	R = 1;
	for (int i = 0; i < n; i++)
	{
		glVertex2f(R * cos((pi / (2*n)) * i), R * sin((pi / (2*n)) * i));
	}
	for (int i = 0; i < n; i++)
	{
		glVertex2f(R * cos((pi / (2 * n)) * i), -R * sin((pi / (2 * n)) * i));
	}
	glEnd();

	glColor3f(0.0, 0.0, 1.0);

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(-R * cos((pi / (2 * n)) * i), R * sin((pi / (2 * n)) * i));
	}
	for (int i = 0; i < n; i++)
	{
		glVertex2f(-R * cos((pi / (2 * n)) * i), -R * sin((pi / (2 * n)) * i));
	}
	glEnd();

	glRotatef(30, 0.0f, 1.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(R * cos(2 * (pi / n) * i), R * sin(2 * (pi / n) * i));
	}
	glEnd();

	glRotatef(30, 0.0f, 1.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(R * cos(2 * (pi / n) * i), R * sin(2 * (pi / n) * i));
	}
	glEnd();

	glRotatef(30, 0.0f, 1.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(R * cos(2 * (pi / n) * i), R * sin(2 * (pi / n) * i));
	}
	glEnd();

	glRotatef(30, 0.0f, 1.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(R * cos(2 * (pi / n) * i), R * sin(2 * (pi / n) * i));
	}
	glEnd();

	glRotatef(30, 0.0f, 1.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(R * cos(2 * (pi / n) * i), R * sin(2 * (pi / n) * i));
	}
	glEnd();

	glRotatef(150, 0.0f, -1.0f, 0.0f); //reset orientation

	//latitude 
	glColor3f(1.0, 1.0, 0.0);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(R * cos(2 * (pi / n) * i), R * sin(2 * (pi / n) * i));
	}
	glEnd();
	glRotatef(90, -1.0f, 0.0f, 0.0f);

	glColor3f(0.0, 0.0, 1.0);
	glTranslatef(0.0, 0.33, 0);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	R = 0.95;
	for (int i = 0; i < n; i++)
	{
		glVertex2f(R * cos(2 * (pi / n) * i), R * sin(2 * (pi / n) * i));
	}
	glEnd();
	glRotatef(90, -1.0f, 0.0f, 0.0f);
	glTranslatef(0.0, -0.33, 0);

	
	glTranslatef(0.0, 0.66, 0);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	R = 0.76;
	for (int i = 0; i < n; i++)
	{
		glVertex2f(R * cos(2 * (pi / n) * i), R * sin(2 * (pi / n) * i));
	}
	glEnd();
	glRotatef(90, -1.0f, 0.0f, 0.0f);
	glTranslatef(0.0, -0.66, 0);

	glTranslatef(0.0, -0.33, 0);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	R = 0.95;
	for (int i = 0; i < n; i++)
	{
		glVertex2f(R * cos(2 * (pi / n) * i), R * sin(2 * (pi / n) * i));
	}
	glEnd();
	glRotatef(90, -1.0f, 0.0f, 0.0f);
	glTranslatef(0.0, 0.33, 0);

	glTranslatef(0.0, -0.66, 0);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	R = 0.76;
	for (int i = 0; i < n; i++)
	{
		glVertex2f(R * cos(2 * (pi / n) * i), R * sin(2 * (pi / n) * i));
	}
	glEnd();
	glRotatef(90, -1.0f, 0.0f, 0.0f);
	glTranslatef(0.0, 0.66, 0);
	
	glEnable(GL_LIGHTING);
	
	glFlush();

}

void resize(int w, int h)
{
	if (w < h) {
		dis = w;
		midpoint[0] = w / 2;
		midpoint[1] = h - (w / 2);
	}
	else {
		dis = h;
		midpoint[0] = h / 2;
		midpoint[1] = h / 2;
	}
	glViewport(0, 0, dis, dis);

	//glMatrixMode(GL_PROJECTION);

	//glLoadIdentity();

	//glOrtho(-1.5, 1.5, -1.5, 1.5, -10.0, 10.0);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(10, 10);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glViewport(0, 0, 600, 600);
	glutCreateWindow("Program 6");

	init();
	
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(resize);
	createMenu();
	glutMouseFunc(mouseClick);
	glutMotionFunc(motion);
	glutSpecialFunc(SpecialKey);

	GLUI* glui = GLUI_Master.create_glui("Controller", 0, 900, 10);
	new GLUI_Spinner(glui, "s:", &s);
	new GLUI_Separator(glui);
	new GLUI_Button(glui, "Cut off left", 1, control_cb);
	new GLUI_Button(glui, "Cut off right", 2, control_cb);
	new GLUI_Button(glui, "Extend left", 3, control_cb);
	new GLUI_Button(glui, "Extend right", 4, control_cb);
	new GLUI_Button(glui, "Set points", 5, control_cb);
	new GLUI_Button(glui, "Set tangents", 6, control_cb);
	new GLUI_Button(glui, "Draw control", 7, control_cb);
	new GLUI_Button(glui, "Move control", 8, control_cb);
	new GLUI_Button(glui, "Draw curve", 9, control_cb);
	new GLUI_Button(glui, "Quit", 0, (GLUI_Update_CB)exit);
	

	glutMainLoop();
	return 0;
}