#include <stdlib.h>
#include <stdio.h>
#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <string.h>
#include <time.h>

void InitLight(){
	GLfloat global_ambient[] = { 0.9, 0.9, 0.9, 1.0 };	//���� �ֺ��ݻ�

	GLfloat mat_diffuse[] = { 1.0, 1.0, 0.3, 1.0 };
	//GLfloat mat_diffuse[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };

	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	//GLfloat light_position[ ] = {0, 2, 10, 0.0};; //{-3, 2, 3.0, 0.0};
	GLfloat light_position[] = { -3, 2, 3.0, 0.0 };; //������ ��ġ�� �ǹ� x, y, z, (����) �̰� �˰� �ֱ�

	GLfloat light1_ambient[] = { 0.0, 0.0, 0.0, 1.0 };	//1�� ���� Ư��
	GLfloat light1_diffuse[] = { 0.5, 0., 0., 1.0 };	//����
	GLfloat light1_specular[] = { 0.0, 0.0, 0.0, 1.0 };
	/*
	GLfloat mat_diffuse[ ] = {1.0, .0, .0, 1.0};
	GLfloat mat_specular[ ] = {.0, .0, .0, 1.0};
	GLfloat mat_ambient[ ] = {.0, .0, .0, 1.0};
	GLfloat mat_shininess[ ] = {0.0};

	GLfloat light_specular[ ] = {.0, .0, .0, 1.0};
	GLfloat light_diffuse[ ] = {1.0, 1.0, 1.0, 1.0};
	GLfloat light_ambient[ ] = {0., 0., 0., 1.0};
	GLfloat light_position[ ] = {0, 2, 10, 0.0};; //{-3, 2, 3.0, 0.0};
	*/
	glShadeModel(GL_SMOOTH);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

	glEnable(GL_LIGHT1);		//1�� ���� Ȱ��ȭ
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);	//1�� ���� Ư���Ҵ�
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);//�����ֺ��ݻ�
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); //�������� (�׳� �⺻������ true�� �صα�)
}

void InitVisibility(){

	glEnable(GL_CULL_FACE); 		//�� ���Ÿ� �����ϰڴ�	(�ĸ������۾�1)				
	//glFrontFace(GL_CCW);			//� ���� �ո��ΰ�(�⺻���� CCW(�ݽð�)) (�ĸ������۾�2)
	glFrontFace(GL_CW);				//glut �������� ��� cw�� �׸�
	glCullFace(GL_BACK);			//�޸� ������	
	//glCullFace(GL_FRONT); //BACK);	//�ո� ������ (�ĸ������۾�3)


	glEnable(GL_DEPTH_TEST); 		//�̰� ����� �׸��� z�� ���� ���� �� �� ��������(������ ������ �˰��� ���� ���߿� �׸� �׸��� ������ ������ ����)				
}

GLfloat ex = 0.0, ey = 0.0, ez = 100.0, lx = 0.0, ly = 0.0, lz = 0.0, tz = -1000.0, tz2 = -1000.0, tz3 = -1000.0, tz4 = -1000.0, tz5 = -1000.0, tz6 = -2000.0, tz7 = 97.0, mx = 0.0, my = 0.0;
GLfloat rx1 = 0.0, ry1 = 1.0, rx2 = 1.0, ry2 = 2.0, rx3 = -2.0, ry3 = -1.0, rx4 = 2.0, ry4 = 3.0, rx5 = 0.0, ry5 = 0.0, rx6 = 0.0, ry6 = 0.0, rx7 = 0.0, ry7 = 0.0;
GLint r = 0, besttime = 0, sumtime = 0, score = 0, bestscore = 0, fcount = 5;
GLboolean stop = false, bests = false, bestt = false, vsee = false, fin=false, big=false, fire=false;

void MyDisplay(){
	GLfloat LightPosition0[] = { 0.0, 100.0, 0.0, .0 };
	GLfloat LightPosition1[] = { 0.0, 0.0, 100, .0 };	//1�� ������ġ (4��°�� 1�̸� �ش� ��ġ�� ������ �޾���)
	GLfloat LightDirection1[] = { 0.0, 0.0, 99 };	//1�� ���� ����
	GLfloat SpotAngle1[] = { 30.0 };						//1�� ���� ���� (10���� ���̸� ���� ũ�Ⱑ �۾���)

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(ex, ey, ez, lx, ly, lz, 0.0, 1.0, 0.0); //�տ��� �ո� ����

	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition0);	//��ġ�� ���� (������ ���� �Լ�)-(�����̸�, ��ġ���Ѷ�, ���(������ġ))

	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition1);	//

	//glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, LightDirection1);	//���� (����Ʈ1��, ������, ���⸦ �ٶ󺸵���)
	//glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, SpotAngle1);	//����	//����(�Ʒ� ����)�� 20�� �������� (���� ũ�����)
	//glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);			//�ڻ��� �¼� //2.0 ���� ũ�� �Ҽ��� �߽��� �����
	if (fin){
		glColor3f(1.0, 1.0, 1.0);
		glRasterPos3f(-1.8, 3.0, 55); //define position on the screen
		char *text = "=!! game clear !!=";

		while (*text){
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *text++);
		}
		if (bests){
			glRasterPos3f(-2.0, 2.0, 55); //define position on the screen
			char *text3 = "best score:";

			while (*text3){
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *text3++);
			}
			glRasterPos3f(1.8, 2.0, 55); //define position on the screen
			char num2[10 + sizeof(char)];
			sprintf_s(num2, "%d", bestscore);
			char *text4 = num2;

			while (*text4){
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *text4++);
			}
		}
		else{
			glRasterPos3f(-2.0, 2.0, 55); //define position on the screen
			char *text3 = "score:";

			while (*text3){
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *text3++);
			}
			glRasterPos3f(0.0, 2.0, 55); //define position on the screen
			char num2[10 + sizeof(char)];
			sprintf_s(num2, "%d", score);
			char *text4 = num2;

			while (*text4){
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *text4++);
			}
		}

		if (bestt){
			glRasterPos3f(-2.0, 1.0, 55); //define position on the screen
			char *text5 = "best time:";

			while (*text5){
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *text5++);
			}
			glRasterPos3f(1.8, 1.0, 55); //define position on the screen
			char num3[10 + sizeof(char)];
			sprintf_s(num3, "%d", besttime);
			char *text6 = num3;

			while (*text6){
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *text6++);
			}
		}
		else{
			glRasterPos3f(-2.0, 1.0, 55); //define position on the screen
			char *text5 = "time :";

			while (*text5){
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *text5++);
			}
			glRasterPos3f(0.0, 1.0, 55); //define position on the screen
			char num3[10 + sizeof(char)];
			sprintf_s(num3, "%d", sumtime);
			char *text6 = num3;

			while (*text6){
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *text6++);
			}
		}


		glRasterPos3f(-1.8, -1.0, 55); //define position on the screen
		char *text2 = "replay press 'r'";

		while (*text2){
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *text2++);
		}
	}
	else if (stop){
		//���� �� �ȳ�����
		glColor3f(0.5, 0.0, 0.5);
		//�簢�� Ʋ
		//glBegin(GL_POLYGON);
		//glVertex3f(-2.5, -1.5, 0.0);
		//glVertex3f(2.5, -1.5, 0.0);
		//glVertex3f(2.5, 3.5, 0.0);
		//glVertex3f(-2.5, 3.5, 0.0);
		//glEnd();
		glPushMatrix();
		glCullFace(GL_BACK);
		glTranslatef(0.0, 0.0, 50);
		//glutSolidCube(10.0);
		glPopMatrix();

		glColor3f(1.0, 1.0, 1.0);
		glRasterPos3f(-1.5, 3.0, 55); //define position on the screen
		char *text = "= game over =";

		while (*text){
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *text++);
		}
		if (bests){
			glRasterPos3f(-2.0, 2.0, 55); //define position on the screen
			char *text3 = "best score:";

			while (*text3){
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *text3++);
			}
			glRasterPos3f(1.8, 2.0, 55); //define position on the screen
			char num2[10 + sizeof(char)];
			sprintf_s(num2, "%d", bestscore);
			char *text4 = num2;

			while (*text4){
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *text4++);
			}
		}
		else{
			glRasterPos3f(-2.0, 2.0, 55); //define position on the screen
			char *text3 = "score:";

			while (*text3){
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *text3++);
			}
			glRasterPos3f(0.0, 2.0, 55); //define position on the screen
			char num2[10 + sizeof(char)];
			sprintf_s(num2, "%d", score);
			char *text4 = num2;

			while (*text4){
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *text4++);
			}
		}

		if (bestt){
			glRasterPos3f(-2.0, 1.0, 55); //define position on the screen
			char *text5 = "best time:";

			while (*text5){
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *text5++);
			}
			glRasterPos3f(1.8, 1.0, 55); //define position on the screen
			char num3[10 + sizeof(char)];
			sprintf_s(num3, "%d", besttime);
			char *text6 = num3;

			while (*text6){
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *text6++);
			}
		}
		else{
			glRasterPos3f(-2.0, 1.0, 55); //define position on the screen
			char *text5 = "time :";

			while (*text5){
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *text5++);
			}
			glRasterPos3f(0.0, 1.0, 55); //define position on the screen
			char num3[10 + sizeof(char)];
			sprintf_s(num3, "%d", sumtime);
			char *text6 = num3;

			while (*text6){
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *text6++);
			}
		}


		glRasterPos3f(-1.8, -1.0, 55); //define position on the screen
		char *text2 = "replay press 'r'";

		while (*text2){
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *text2++);
		}
	}
	else{

		glColor3f(1.0, 0.0, 0.0);
		glRasterPos3f(ex-25.0, ey+3.0, -10); //define position on the screen
		char *string2 = "score:";

		while (*string2){
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *string2++);
		}

		//���� ��¹� (sumtime�� score�� �ٲ��ָ� �ɵ�)
		glColor3f(1.0, 0.0, 0.0);
		glRasterPos3f(ex-18.0, ey+3.0, -10); //define position on the screen
		char num[10 + sizeof(char)];
		sprintf_s(num, "%d", score);
		char *string = num;

		while (*string){
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *string++);
		}

		glColor3f(1.0, 0.0, 0.0);
		glRasterPos3f(ex-25.0, ey+0.88, -10); //define position on the screen
		char *time = "time:";

		while (*time){
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *time++);
		}

		//���� ��¹�
		glColor3f(1.0, 0.0, 0.0);
		glRasterPos3f(ex-18.0, ey+0.88, -10); //define position on the screen
		char numt[10 + sizeof(char)];
		sprintf_s(numt, "%d(s)", sumtime);
		char *st = numt;

		while (*st){
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *st++);
		}

		glPushMatrix();
		glTranslatef(rx1, ry1, tz);
		glRotatef(r, 0.0, 0.5, 0.0);
		glutSolidTeapot(0.5);
		//glutSolidIcosahedron();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(rx2, ry2, tz2);
		glRotatef(r, 0.0, 0.0, 1.0);
		glutSolidIcosahedron();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(rx3, ry3, tz3);
		glRotatef(r, 0.5, 0.5, 0.0);
		glutSolidTorus(0.1, 0.2, 20, 20);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(rx4, ry4, tz4);
		glRotatef(r, 0.5, 0.5, 0.0);
		glutSolidTorus(0.1, 0.2, 20, 20);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(rx5, ry5, tz5);
		glRotatef(r, 0.5, 0.5, 0.0);
		glutSolidIcosahedron();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(rx6, ry6, tz6);
		glRotatef(r, 0.5, 0.5, 0.0);
		glutSolidSphere(10, 10, 10);
		glPopMatrix();

		if (big){
			glPushMatrix();
			glTranslatef(ex-0.3, ey+0.6, 97);
			for (int i = 0; i < fcount; i++){			
				glutSolidCube(0.05);
				glTranslatef(0.06, 0.0, 0.0);
				//glTranslatef(-0.48, 0.0, -0.12);
			}
			glPopMatrix();
		}

		if (fire){	//���
			glColor3f(1.0, 0.0, 0.0);
			glRasterPos3f(mx - 1.5, my - 1.5, 55); //define position on the screen
			char *fff = "= loading =";

			while (*fff){
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *fff++);
			}

			printf("�ݹ�!!\n");
			glPushMatrix();
			glTranslatef(rx7, ry7, tz7);
			//glRotatef(r, 0.5, 0.5, 0.0);
			glutSolidSphere(0.5, 100, 100);
			glPopMatrix();
		}

		if (vsee){	//���ּ� ���
			glPushMatrix();
			glCullFace(GL_FRONT);
			glTranslatef(mx, my, 100);
			//glRotatef(40, 0.0, 1.0, 0.0);
			glutSolidCone(1.0, 2.0, 10, 10);
			glPopMatrix();
		}
		else{
			glPushMatrix();
			//glTranslatef(ex, ey, 97);
			//glLineWidth(3);
			glBegin(GL_LINES);     // mode ����
			glColor3f(0.0, 0.0, 1.0);
			glVertex3f(ex-0.05, ey+0.0, 97);
			glVertex3f(ex+0.05, ey+0.0, 97);
			glVertex3f(ex +0.0, ey + 0.05, 97);
			glVertex3f(ex +0.0, ey - 0.05, 97);
			glEnd();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(ex, ey, 97);
			//glRotatef(r, 0.5, 0.5, 0.0);
			glutSolidTorus(0.2, 1.0, 20, 20);
			glPopMatrix();
		}
	}
	glFlush();
}

void MyReshape(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30, 1.0, 0.1, 2000.0);
}
GLint count6 = 0;
void MyTimer6(int Value){
	if (!stop) {
		printf("%f\n", tz6);
		tz6 += 0.9;
		count6++;
	}
	if ((ex > rx6 - 5.0 && ex < rx6 + 5.0 && ey<ry6 + 5.0 && ey>ry6 - 5.0 && tz6>100 && tz6<103) || (mx > rx6 - 5.0 && mx < rx6 + 5.0 && my<ry6 + 5.0 && my>ry6 - 5.0 && tz6>100 && tz6<103)){
		//printf("%f\n", tz);
		if (score > bestscore){
			bestscore = score;
			bests = true; big = false;
		}

		stop = true;
		//fin = true;
		if (vsee){
			ez = 100; ly += 1.0;
		}
		ex = 0; ey = 0;

		vsee = false;
	}

	glutPostRedisplay();

	if (count6 > 2800){
		tz6 = -2000;
		score-=10;
		count6 = 0;
	}
	if (big)
		glutTimerFunc(10, MyTimer6, 1);
}
GLint count5 = 0;
void MyTimer5(int Value){
	if (!stop) {
		tz5 += 1.5;
		count5++;
	}
	if ((ex > rx5 - 0.6 && ex < rx5 + 0.6 && ey<ry5 + 0.6 && ey>ry5 - 0.6 && tz5>100 && tz5<103) || (mx > rx5 - 0.6 && mx < rx5 + 0.6 && my<ry5 + 0.6 && my>ry5 - 0.6 && tz5>100 && tz5<103)){
		//printf("%f\n", tz);
		if (score > bestscore){
			bestscore = score;
			bests = true;
		}

		stop = true;
		if (vsee){
			ez = 100.0; ly += 1.0;
		}
		ex = 0; ey = 0;

		vsee = false;
	}

	glutPostRedisplay();

	if (count5 > 800){
		srand(time(NULL));
		rx5 = rand() % 5;
		ry5 = -(rand() % 5);
		tz5 = -1000;
		score++;
		count5 = 0;
	}
	glutTimerFunc(10, MyTimer5, 1);
}
GLint count4 = 0;
void MyTimer4(int Value){
	if (!stop) {
		tz4 += 1.5;
		count4++;
	}
	if ((ex > rx4 - 0.6 && ex < rx4 + 0.6 && ey<ry4 + 0.6 && ey>ry4 - 0.6 && tz4>100 && tz4<103) || (mx > rx4 - 0.6 && mx < rx4 + 0.6 && my<ry4 + 0.6 && my>ry4 - 0.6 && tz4>100 && tz4<103)){
		//printf("%f\n", tz);
		if (score > bestscore){
			bestscore = score;
			bests = true;
		}

		stop = true;
		if (vsee){
			ez = 100; ly += 1.0;
		}
		ex = 0; ey = 0;

		vsee = false;
	}

	glutPostRedisplay();

	if (count4 > 800){
		srand(time(NULL));
		rx4 = rand() % 5;
		ry4 = -(rand() % 5);
		tz4 = -1000;
		score++;
		count4 = 0;
	}
	glutTimerFunc(10, MyTimer4, 1);
}
GLint count3 = 0;
void MyTimer3(int Value){
	if (!stop) {
		tz3 += 1.4;
		count3++;
	}
	if ((ex > rx3 - 0.6 && ex < rx3 + 0.6 && ey<ry3 + 0.6 && ey>ry3 - 0.6 && tz3>100 && tz3<103) || (mx > rx3 - 0.6 && mx < rx3 + 0.6 && my<ry3 + 0.6 && my>ry3 - 0.6 && tz3>100 && tz3<103)){
		//printf("%f\n", tz);
		if (score > bestscore){
			bestscore = score;
			bests = true;
		}

		stop = true;
		if (vsee){
			ez = 100; ly += 1.0;
		}
		ex = 0; ey = 0;

		vsee = false;
	}

	glutPostRedisplay();

	if (count3 > 800){
		srand(time(NULL));
		rx3 = -(rand() % 5);
		ry3 = -(rand() % 5);
		tz3 = -1000;
		score++;
		count3 = 0;
	}
	glutTimerFunc(10, MyTimer3, 1);
}
GLint count2 = 0;
void MyTimer2(int Value){
	if (!stop){
		tz2 += 1.5;
		r += 10;
		count2++;
	}
	if ((ex > rx2 - 0.6 && ex < rx2 + 0.6 && ey<ry2 + 0.6 && ey>ry2 - 0.6 && tz2>100 && tz2<103) || (mx > rx2 - 0.6 && mx < rx2 + 0.6 && my<ry2 + 0.6 && my>ry2 - 0.6 && tz2>100 && tz2<103)){
		//printf("%f\n", tz);
		if (score > bestscore){
			bestscore = score;
			bests = true;
		}

		stop = true;
		if (vsee){
			ez = 100; ly += 1.0;
		}
		ex = 0; ey = 0;

		vsee = false;
	}

	glutPostRedisplay();

	if (count4 == 0 && count2 == 500)
		glutTimerFunc(10, MyTimer4, 1);
	if (count2 > 800){
		srand(time(NULL));
		rx2 = -(rand() % 5);
		ry2 = rand() % 5;
		tz2 = -1000;
		score++;
		count2 = 0;
	}
	glutTimerFunc(10, MyTimer2, 1);
}
GLint count = 0;
void MyTimer(int Value){
	if (!stop){
		tz += 1.8;
		//printf("%d\n", count);
		count++;
	}

	if ((ex > rx1 - 0.6 && ex < rx1 + 0.6 && ey<ry1 + 0.6 && ey>ry1 - 0.6 && tz>100 && tz<103) || (mx > rx1 - 0.6 && mx < rx1 + 0.6 && my<ry1 + 0.6 && my>ry1 - 0.6 && tz>100 && tz<103)){
		//printf("%f\n", tz);
		if (score > bestscore){
			bestscore = score;
			bests = true;
		}

		stop = true;
		if (vsee){
			ez = 100; ly += 1.0;
		}
		ex = 0; ey = 0;

		vsee = false;
	}


	glutPostRedisplay();

	if (count > 800){
		srand(time(NULL));
		rx1 = rand() % 5;
		ry1 = rand() % 5;
		tz = -1000;
		score++;
		count = 0;
	}
	glutTimerFunc(10, MyTimer, 1);
}
void PlayTimer(int Value){
	if (!stop)
		sumtime++;
	if (sumtime!=0 && sumtime % 60 == 0){
		big = true;
		tz6 = -2000;
		glutTimerFunc(10, MyTimer6, 1);
	}
		
	glutTimerFunc(1000, PlayTimer, 1);
}
void FireTimer(int Value){
	if (fire){
		printf("%f\n",tz7);
		tz7 -= 10.0;

		if (tz7 < -500.0){	//��Ÿ� ����
			fire = false;
			tz7 = 97;
		}

		if (big && rx7 > -5.5 &&rx7<5.5 && ry7>-5.5 && ry7 < 5.5 && tz7 < tz6){
			printf("\n-----------����-------------\n"); 
			score++;
			fcount--;
			fire = false;
			if (fcount < 1){
				if (score > bestscore){
					bestscore = score;
					bests = true; big = false;
				}

				stop = true;
				fin = true;
				if (vsee){
					ez = 100; ly += 1.0;
				}
				ex = 0; ey = 0;

				vsee = false;
			}
		}
		
	}
	glutTimerFunc(10, FireTimer, 1);
}

void MyKeyboard(unsigned char key, int x, int y){
	switch (key) {
	case 'r':	//�ٽ� ���� ��ư
		tz = -1000;	tz2 = -1000; tz3 = -1000; tz4 = -1000; tz5 = -1000; tz6 = -2000;
		lx = 0.0; ly = 0.0;
		sumtime = 0;
		score = 0;
		fcount = 5;
		stop = false;
		bestt = false;
		bests = false;
		big = false;
		fin = false;
		glutPostRedisplay();
		break;
	case 'i':	//ī�޶� ���� ���� ��ư
		ey += 0.5;
		ly += 0.5;
		glutPostRedisplay();
		break;
	case 'j':
		ex -= 0.5;
		lx -= 0.5;
		glutPostRedisplay();
		break;
	case 'k':
		ex += 0.5;
		lx += 0.5;
		glutPostRedisplay();
		break;
	case 'm':
		ey -= 0.5;
		ly -= 0.5;
		glutPostRedisplay();
		break;
	case 'v':	//���� ��ȯ (1��Ī, 3��Ī ���� ��ȯ)
		if (!vsee){
			mx = ex; my = ey; ly -= 1.0;
			ez = 170.0; ey += 10.0;
			vsee = true;
		}
		else{
			ez = 100.0; ey -= 10.0;  ly += 1.0;
			vsee = false;
		}
		printf("��ü : %f, %f, %f\n", mx, my, 100.0);
		printf("ī�޶�: %f, %f, %f\n", ex, ey, ez);
		glutPostRedisplay();
		break;
	case 'w':	//���ּ� ���۸��
		ey += 0.5;
		ly += 0.5;
		my += 0.5;
		glutPostRedisplay();
		break;
	case 'a':
		ex -= 0.5;
		lx -= 0.5;
		mx -= 0.5;

		glutPostRedisplay();
		break;
	case 'd':
		ex += 0.5;
		lx += 0.5;
		mx += 0.5;
		glutPostRedisplay();
		break;
	case 's':
		ey -= 0.5;
		ly -= 0.5;
		my -= 0.5;
		glutPostRedisplay();
		break;
	case 'p':	//��� ��ư
		rx7 = mx;
		ry7 = my;
		tz7 = 97;
		fire = true;
		
		glutPostRedisplay();
		break;
	default:
		break;
	}
}


int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Sample Drawing");
	glClearColor(0.0, 0.0, 0.0, 0.0);

	InitLight();
	InitVisibility();

	glutTimerFunc(10, MyTimer, 1);
	glutTimerFunc(10, MyTimer2, 1);
	glutTimerFunc(10, MyTimer3, 1);
	glutTimerFunc(10, MyTimer5, 1);
	glutTimerFunc(1000, PlayTimer, 1);
	glutTimerFunc(10, FireTimer, 1);
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKeyboard);

	glutMainLoop();
	return 0;
}
