#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "Gears.h"


struct wcPt3D_tag {
	GLfloat x, y, z;
};

typedef struct wcPt3D_tag wcPt3D;

/*  Compute binomial coefficients C for given value of n.  */
void binomialCoeffs(GLint n, GLint * C)
{
	GLint k, j;

	for (k = 0; k <= n; k++) {
		/*  Compute n!/(k!(n - k)!).  */
		C[k] = 1;
		for (j = n; j >= k + 1; j--)
			C[k] *= j;
		for (j = n - k; j >= 2; j--)
			C[k] /= j;
	}
}

void computeBezPt(GLfloat u, wcPt3D * bezPt, GLint nCtrlPts,
	wcPt3D * ctrlPts, GLint * C)
{
	GLint k, n = nCtrlPts - 1;
	GLfloat bezBlendFcn;

	bezPt->x = bezPt->y = bezPt->z = 0.0;

	/*  Compute blending functions and blend control points. */
	for (k = 0; k < nCtrlPts; k++) {
		bezBlendFcn = C[k] * pow(u, k) * pow(1 - u, n - k);
		bezPt->x += ctrlPts[k].x * bezBlendFcn;
		bezPt->y += ctrlPts[k].y * bezBlendFcn;
		bezPt->z += ctrlPts[k].z * bezBlendFcn;
	}
}


GLfloat u;

GLint nCtrlPts = 6;
wcPt3D ctrlPts[2][6] = {
		{ { 3, -.5, -.25 }, //path 1
		{ 3.5, -.5, -.8 },
		{ 1, -.15, -2.5 },
		{ -1, -.15, -2.5 },
		{ -3.5, -.5, -.8 },
		{ -3, 0, -.15 } },

		{ { -3, 0, -.15 }, //path 2
		{-.75, 1, -.5},
		{-.25, 1.5, -6},
		{.25, 2, -6},
		{.75, 2.5, -.5},
		{3, 3, -.25} }
};
GLint *C;

float light_intensity[] = {0, 0, 0, 0};

/*  Initialize material property, light source, lighting model,
*  and depth buffer.
*/
float objRot = 0;
int objectID = 0;


void init(void)
{

	GLfloat light_position0[] = { 0.0, 2.0, -.25, 0.0 };
	GLfloat light_position1[] = { 0.0, 1.5, 2.0, 0.0 };
	GLfloat white[] = { 1, 1, 1, 0 };
	GLfloat gray[] = { 0.5, 0.5, 0.5, 0 };
	GLfloat black[] = { 0, 0, 0, 0 };


	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_intensity);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_intensity);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_intensity);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_intensity);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_intensity);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_intensity);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	C = calloc(nCtrlPts, sizeof(GLint));
	binomialCoeffs(nCtrlPts - 1, C);
}

float helmGearRot = 0;
float inc = 2;
float yRot = 24;
float xRot = 9;
int pathNum = 0;

void initParams() {
	u = 0;
	pathNum++;
	if (pathNum > 1) {
		pathNum = 0;
	}
}



void display(void) {
	//printf("%f, %f \n", xRot, yRot);
	GLUquadric* quad = gluNewQuadric();
	wcPt3D bezCurvePt;

	float height_diff = 1.5;

	GLfloat black[] = { 0, 0, 0, 0.0 };
	GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat blue[] = { 0, 0, 0.75, 0 };
	GLfloat red[] = { 1, 0, 0, 0 };
	GLfloat red04[] = { 0.4, 0, 0, 0 };
	GLfloat red02[] = { 0.2, 0, 0, 0 };
	GLfloat white[] = { 1, 1, 1, 0 };
	float brassA[] = { .329412, .223529, .027451 };
	float brassD[] = { .780392, 0.568627, .113725 };
	float brassS[] = { .992157, .941176, .807843 };
	float brassShininess[] = { .21794872 * 128 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, brassA);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, brassD);
	glMaterialfv(GL_FRONT, GL_SPECULAR, brassS);
	glMaterialfv(GL_FRONT, GL_SHININESS, brassShininess);
	glShadeModel(GL_SMOOTH);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	computeBezPt(u, &bezCurvePt, nCtrlPts, ctrlPts[pathNum], C);
	gluLookAt(bezCurvePt.x, bezCurvePt.y, bezCurvePt.z,
		0, (pathNum == 0 ? 0 : bezCurvePt.y * 3 / 5), 0, 0, 1, 0);
	//gluLookAt(0, 2, -5, 0, 0, 0, 0, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glRotatef(xRot, 1, 0, 0);
	glRotatef(yRot, 0, 1, 0);

	glPushMatrix();
	glTranslatef(0, -1.25, 0);
	glScalef(4, 0.01, 4);      // floor
	glutSolidCube(1);
	glPopMatrix();

	for (int i = 0; i < 2; i++) {
		glPushMatrix(); //helmGear 1
		glTranslatef(0, (i * height_diff), 0);
		glScalef(.5, .5, .5);
		glRotatef(helmGearRot * (25.0 / 30.0), 0, 0, 1);
		if (i == 0) {
			helmGear(30, 6, 1);
		} else {
			colemanGear(30, 6, 1);
		}
		glPopMatrix();
		quad = gluNewQuadric();
		glPushMatrix();
		glTranslatef(0, (i * height_diff), 0);
		gluCylinder(quad, .08, .08, 1.15, 15, 15);
		glPopMatrix();

		glPushMatrix(); //helmGear 2
		glTranslatef(1, (i * height_diff), 0);
		glRotatef(-helmGearRot + 6, 0, 0, 1);
		glPushMatrix();
		glScalef(.4, .4, .4);
		helmGear(25, 5, 0);
		glPopMatrix();
		gluCylinder(quad, .04, .04, 1.25, 20, 20);
		glPopMatrix();

		glPushMatrix(); //colemanGear 1
		glTranslatef(1, (i * height_diff), .25);
		glRotatef(-helmGearRot, 0, 0, 1);
		glScalef(.6, .6, .6);
		if (i == 0) {
			colemanGear(25, 20);
		} else {
			helmGear(45, 10, 1);
		}
		glPopMatrix();

		glPushMatrix(); //helmGear 3
		glTranslatef(-1, (i * height_diff), 0);
		glRotatef(-helmGearRot, 0, 0, 1);
		glPushMatrix();
		glScalef(.4, .4, .4);
		helmGear(25, 5, 0);
		glPopMatrix();
		gluCylinder(quad, .04, .04, 1.25, 20, 20);
		glPopMatrix();

		glPushMatrix(); //chenGear 1
		glTranslatef(-1, (i * height_diff), .375);
		glRotatef(-helmGearRot, 0, 0, 1);
		glScalef(.4, .4, .4);
		chenGear(25, 5);
		glPopMatrix();

		quad = gluNewQuadric();
		glPushMatrix();
		glTranslatef(-.45, .55 + (i * height_diff), (i == 0 ? .2 : -.2));
		gluCylinder(quad, .05, .05, 1.5, 15, 15);
		glPopMatrix();
		glPushMatrix(); //helmGear 4
		glTranslatef(-.45, .55 + (i * height_diff), (i == 0 ? .2 : -.2));
		glRotatef(helmGearRot, 0, 0, 1);
		glScalef(.5, .5, .5);
		if (i == 0) {
			helmGear(25, 5, 2);
		} else {
			alpertGear(30, 10, 1);
		}
		glPopMatrix();

		quad = gluNewQuadric();
		glPushMatrix();
		glTranslatef(.375, .5 + (i * height_diff), -.35);
		gluCylinder(quad, .05, .05, 1.5, 15, 15);
		glPopMatrix();
		glPushMatrix(); //alpertGear 2
		glTranslatef(.375, .5 + (i * height_diff), -.35);
		glRotatef(-helmGearRot, 0, 0, 1);
		glScalef(.6, .6, .6);
		alpertGear(30, 6, .6);
		glPopMatrix();
	}
/*
	glMaterialfv(GL_FRONT, GL_AMBIENT, goldA);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, goldD);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
*/
	glPushMatrix(); //the box
	glTranslatef(0, .75, 1.375);
	glScalef(1.25, 2, .25);
	glutSolidCube(2);
	glPopMatrix();
	
	glPopMatrix();

	glutSwapBuffers();
}


float slowFactor = 0.2;
float angInc = 4; //2*3.14159/360;
int lastPath = 0;

void idle() {
	if (u > 1) {
		initParams();
	}
	else {
		u += 0.004*slowFactor;
	}

	helmGearRot += inc * slowFactor;

	if (pathNum == 0 && lastPath == 1) {
		light_intensity[0] = 0;
		light_intensity[1] = 0;
		light_intensity[2] = 0;
	}

	if (light_intensity[0] < .85 && (u > .05 && pathNum == 0) || pathNum == 1) {
		light_intensity[0] += .00025;
		light_intensity[1] += .00025;
		light_intensity[2] += .00025;
	}

	glLightfv(GL_LIGHT1, GL_AMBIENT, light_intensity);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_intensity);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_intensity);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_intensity);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_intensity);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_intensity);

	lastPath = pathNum;

	glutPostRedisplay();
}

void reshape(int w, int h)
{

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float sz = 0.5;
	if (w <= h)
		glFrustum(-sz, sz, -sz*(GLfloat)h / (GLfloat)w,
		sz*(GLfloat)h / (GLfloat)w, 1.0, 10.0);
	else
		glFrustum(-sz*(GLfloat)w / (GLfloat)h,
		sz*(GLfloat)w / (GLfloat)h, -sz, sz, 1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void special(int key, int x, int y) {

	switch (key) {

	case 100:
		yRot -= 3;
		break;
	case 102:
		yRot += 3;
		break;
	case 101:
		xRot -= 3;
		break;
	case 103:
		xRot += 3;
		break;
	}
	glutPostRedisplay();

}


void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'f':
		slowFactor *= 1.10;
		break;
	case 's':
		slowFactor *= 0.9;
		break;
	case 27:
		exit(0);
		break;
	case '0':
		objectID = 0;
		break;
	case '1':
		objectID = 1;
		break;
	case '2':
		objectID = 2;
		break;
	case '3':
		objectID = 3;
		break;
	case '4':
		objectID = 4;
		break;
	case '+':
		objRot += 3;
		break;
	case '-':
		objRot -= 3;
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMainLoop();
	return 0;
}