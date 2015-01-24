#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "Gears.h"

#define true 1
#define false 0

void calcNormal(float x1, float y1, float z1,
	float x2, float y2, float z2,
	float x3, float y3, float z3,
	float* nx, float* ny, float* nz) {

	float ux = x2 - x1, uy = y2 - y1, uz = z2 - z1;
	float vx = x3 - x1, vy = y3 - y1, vz = z3 - z1;

	*nx = uy * vz - uz * vy;
	*ny = uz * vx - ux * vz;
	*nz = ux * vy - uy * vx;
}

void normalize(float* nx, float* ny, float* nz) {
	float scalar = sqrt(pow(*nx, 2.0) + pow(*ny, 2.0) + pow(*nz, 2.0));
	*nx = *nx / scalar;
	*ny = *ny / scalar;
	*nz = *nz / scalar;
}

void drawCoin(float radius) {

	int n = 40;
	float rad = radius;
	float outRad = rad * 1.16;
	float angInc = 2 * 3.14159 / n;
	float ang = 0;
	float z = 0.1;

	glNormal3f(0, 0, 1);

	for (int i = 0; i < n; i++) {                //  majority of the gear face
		glBegin(GL_POLYGON);
		glVertex3f(0, 0, z);
		glVertex3f(rad*cos(ang), rad*sin(ang), z);
		glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), z);
		glEnd();

		ang += angInc;
	}

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	ang = 0;                              //  majority of the gear face, flip side
	for (int i = 0; i < n; i++) {
		glBegin(GL_POLYGON);
		glVertex3f(0, 0, z);
		glVertex3f(rad*cos(ang), rad*sin(ang), z);
		glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), z);
		glEnd();

		ang += angInc;
	}
	glPopMatrix();



	ang = 0;
	for (int i = 0; i < n; i++) { // belt

		glNormal3f(rad*cos(ang + angInc / 2), rad*sin(ang + angInc / 2), 0);
		glBegin(GL_POLYGON);
		glVertex3f(rad*cos(ang), rad*sin(ang), -z);
		glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), -z);
		glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), z);
		glVertex3f(rad*cos(ang), rad*sin(ang), z);
		glEnd();

		ang += angInc;
	}

}

void helmGear(int numTeeth, int numSpokes, int mode) {
	glPushMatrix();

	float goldA[] = { .24725, .1995, .0745 };
	float goldD[] = { .75164, .60648, .22648 };
	float goldS[] = { .628281, .555802, .366065 };
	float goldShininess[] = { .4 * 128 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, goldA);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, goldD);
	glMaterialfv(GL_FRONT, GL_SPECULAR, goldS);
	glMaterialfv(GL_FRONT, GL_SHININESS, goldShininess);
	glShadeModel(GL_SMOOTH);

	int n = numTeeth * 2;
	int spokes = numSpokes;
	float rad = 1;
	float outRad = rad * 1.16;
	float angInc = 2 * 3.14159 / n;
	float ang = 0;
	float z = 0.1;
	float zDiff = .35 * z;
	float angDiff = (ang - angInc) / 4;
	float inRad = rad * .85;
	float centerRad = .3;

	if (mode != 0) {
		glutSolidSphere(centerRad, 40, 40);
	} else {
		drawCoin(centerRad / 2);
	}

	glNormal3f(0, 0, 1);

	for (int i = 0; i < n; i++) {          //  Donut Face
		float nx, ny, nz;
		calcNormal(inRad*cos(ang), inRad*sin(ang), z - zDiff,
			rad*cos(ang), rad*sin(ang), z,
			rad*cos(ang + angInc), rad*sin(ang + angInc), z,
			&nx, &ny, &nz);
		normalize(&nx, &ny, &nz);
		glNormal3f(nx, ny, nz);

		glBegin(GL_POLYGON);
		glVertex3f(inRad*cos(ang), inRad*sin(ang), z - zDiff);
		glVertex3f(rad*cos(ang), rad*sin(ang), z);
		glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), z);
		glVertex3f(inRad*cos(ang + angInc), inRad*sin(ang + angInc), z - zDiff);
		glEnd();

		ang += angInc;
	}

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	ang = 0;                              //  Donut Face, flip side
	for (int i = 0; i < n; i++) {
		float nx, ny, nz;
		calcNormal(inRad*cos(ang), inRad*sin(ang), z - zDiff,
			rad*cos(ang), rad*sin(ang), z,
			rad*cos(ang + angInc), rad*sin(ang + angInc), z,
			&nx, &ny, &nz);
		normalize(&nx, &ny, &nz);
		glNormal3f(nx, ny, nz);

		glBegin(GL_POLYGON);
		glVertex3f(inRad*cos(ang), inRad*sin(ang), z - zDiff);
		glVertex3f(rad*cos(ang), rad*sin(ang), z);
		glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), z);
		glVertex3f(inRad*cos(ang + angInc), inRad*sin(ang + angInc), z - zDiff);
		glEnd();

		ang += angInc;
	}
	glPopMatrix();



	ang = 0;
	int drawTooth = false;
	for (int i = 0; i < n; i++) {       // face of the teeth
		drawTooth = !drawTooth;
		if (drawTooth) {
			float nx, ny, nz;
			calcNormal(rad*cos(ang), rad*sin(ang), z,
				outRad*cos(ang - angDiff), outRad*sin(ang - angDiff), z - zDiff,
				outRad*cos(ang + angInc + angDiff), outRad*sin(ang + angInc + angDiff), z - zDiff,
				&nx, &ny, &nz);
			normalize(&nx, &ny, &nz);
			glNormal3f(nx, ny, nz);

			glBegin(GL_POLYGON);
			glVertex3f(rad*cos(ang), rad*sin(ang), z);
			glVertex3f(outRad*cos(ang - angDiff), outRad*sin(ang - angDiff), z - zDiff);
			glVertex3f(outRad*cos(ang + angInc + angDiff), outRad*sin(ang + angInc + angDiff), z - zDiff);
			glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), z);
			glEnd();
		}
		ang += angInc;
	}


	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	ang = 0;
	if ((n / 2) % 2 == 0) {
		drawTooth = true;
	}
	else {
		drawTooth = false;
	}
	for (int i = 0; i < n; i++) {       // face of the teeth, flip side
		drawTooth = !drawTooth;
		if (drawTooth) {
			float nx, ny, nz;
			calcNormal(rad*cos(ang), rad*sin(ang), z,
				outRad*cos(ang - angDiff), outRad*sin(ang - angDiff), z - zDiff,
				outRad*cos(ang + angInc + angDiff), outRad*sin(ang + angInc + angDiff), z - zDiff,
				&nx, &ny, &nz);
			normalize(&nx, &ny, &nz);
			glNormal3f(nx, ny, nz);

			glBegin(GL_POLYGON);
			glVertex3f(rad*cos(ang), rad*sin(ang), z);
			glVertex3f(outRad*cos(ang - angDiff), outRad*sin(ang - angDiff), z - zDiff);
			glVertex3f(outRad*cos(ang + angInc + angDiff), outRad*sin(ang + angInc + angDiff), z - zDiff);
			glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), z);
			glEnd();
		}
		ang += angInc;
	}
	glPopMatrix();

	ang = 0;
	for (int i = 0; i < n; i++) { //teeth bridge

		glNormal3f(rad*cos(ang + angInc / 2), rad*sin(ang + angInc / 2), 0);
		glBegin(GL_POLYGON);
		glVertex3f(rad*cos(ang), rad*sin(ang), -z);
		glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), -z);
		glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), z);
		glVertex3f(rad*cos(ang), rad*sin(ang), z);
		glEnd();

		glPushMatrix();
		glRotatef(180, 0, 0, 1);
		glNormal3f(-rad*cos(ang + angInc / 2), -rad*sin(ang + angInc / 2), 0);
		glBegin(GL_POLYGON);
		glVertex3f(inRad*cos(ang), inRad*sin(ang), -z + zDiff);
		glVertex3f(inRad*cos(ang + angInc), inRad*sin(ang + angInc), -z + zDiff);
		glVertex3f(inRad*cos(ang + angInc), inRad*sin(ang + angInc), z - zDiff);
		glVertex3f(inRad*cos(ang), inRad*sin(ang), z - zDiff);
		glEnd();
		glPopMatrix();

		ang += angInc;
	}


	ang = 0;

	drawTooth = false;
	for (int i = 0; i < n; i++) { //tooth roof
		drawTooth = !drawTooth;
		if (drawTooth) {
			glNormal3f(outRad*cos(ang + angInc / 2), outRad*sin(ang + angInc / 2), 0);
			glBegin(GL_POLYGON);
			glVertex3f(outRad*cos(ang - angDiff), outRad*sin(ang - angDiff), -z + zDiff);
			glVertex3f(outRad*cos(ang + angInc + angDiff), outRad*sin(ang + angInc + angDiff), -z + zDiff);
			glVertex3f(outRad*cos(ang + angInc + angDiff), outRad*sin(ang + angInc + angDiff), z - zDiff);
			glVertex3f(outRad*cos(ang - angDiff), outRad*sin(ang - angDiff), z - zDiff);
			glEnd();
		}
		ang += angInc;
	}

	ang = 0;

	drawTooth = false;
	for (int i = 0; i < n; i++) { //tooth sides
		drawTooth = !drawTooth;
		if (drawTooth) {
			float nx, ny, nz;

			calcNormal(rad*cos(ang), rad*sin(ang), -z,
				outRad*cos(ang - angDiff), outRad*sin(ang - angDiff), -z + zDiff,
				outRad*cos(ang - angDiff), outRad*sin(ang - angDiff), z - zDiff,
				&nx, &ny, &nz);
			normalize(&nx, &ny, &nz);
			glNormal3f(nx, ny, nz);

			glBegin(GL_POLYGON);
			glVertex3f(rad*cos(ang), rad*sin(ang), -z);
			glVertex3f(outRad*cos(ang - angDiff), outRad*sin(ang - angDiff), -z + zDiff);
			glVertex3f(outRad*cos(ang - angDiff), outRad*sin(ang - angDiff), z - zDiff);
			glVertex3f(rad*cos(ang), rad*sin(ang), z);
			glEnd();


			calcNormal(rad*cos(ang + angInc), rad*sin(ang + angInc), z,
				outRad*cos(ang + angInc + angDiff), outRad*sin(ang + angInc + angDiff), z - zDiff,
				outRad*cos(ang + angInc + angDiff), outRad*sin(ang + angInc + angDiff), -z + zDiff,
				&nx, &ny, &nz);
			normalize(&nx, &ny, &nz);
			glNormal3f(nx, ny, nz);

			glBegin(GL_POLYGON);
			glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), z);
			glVertex3f(outRad*cos(ang + angInc + angDiff), outRad*sin(ang + angInc + angDiff), z - zDiff);
			glVertex3f(outRad*cos(ang + angInc + angDiff), outRad*sin(ang + angInc + angDiff), -z + zDiff);
			glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), -z);
			glEnd();

		}
		ang += angInc;
	}

	if (mode == 0) {//square spokes
		ang = 0;
		float width = z;
		if (spokes > 10) {
			width = width - ((spokes - 10) * (.075 * z));
		}
		for (int i = 0; i < spokes; i++) {
			glPushMatrix();
			glRotatef(ang, 0, 0, 1);
			glTranslatef(rad / 2, 0, 0);
			glScalef(inRad * 1.05, width, (z - zDiff) * 2);


			glutSolidCube(1);
			glPopMatrix();

			ang += 360.0 / spokes;
		}
	} else if (mode == 1) { // bumpy spokes
		ang = 0;
		float distance = inRad - centerRad;
		float beadRad = (distance / 2) / 4;
		if (spokes > 12) {
			beadRad *= .8;
		}
		for (int i = 0; i < spokes; i++) {
			glPushMatrix();
			glRotatef(ang, 0, 0, 1);
			glTranslatef(centerRad + (beadRad / 2), 0, 0);
			for (int i = 0; i < (distance / (beadRad * .75)); i++) {
				glutSolidSphere(beadRad, 15, 15);
				glTranslatef(.75 * beadRad, 0, 0);
			}
			glPopMatrix();
			ang += 360.0 / spokes;
		}
	} else { //snow men spokes
		GLUquadric* quad;
		ang = 0;
		float hatRoom = inRad - (centerRad * (1.2 + .75));
		float chestRad = .75 * centerRad;
		for (int i = 0; i < spokes; i++) {
			glPushMatrix(); //heads
			glRotatef(ang, 0, 0, 1);
			glTranslatef(centerRad * 1.2, 0, 0);
			glutSolidSphere(.75 * centerRad, 15, 15);
			glPopMatrix();

			glPushMatrix(); //hat top
			glRotatef(ang, 0, 0, 1);
			glTranslatef(inRad - .5 * (hatRoom * 1), 0, 0);
			glScalef(hatRoom * 1.1, centerRad * .8, (z - zDiff) * 2);
			glutSolidCube(1);
			glPopMatrix();

			glPushMatrix(); //hat ring
			glRotatef(ang, 0, 0, 1);
			glTranslatef(centerRad * (1.2 + .75), 0, 0);
			glScalef(.04, centerRad * 2, z * 2);
			glutSolidCube(1);
			glPopMatrix();
			ang += 360 / spokes;

			quad = gluNewQuadric();
			glPushMatrix(); //nose
			glRotatef(ang, 0, 0, 1);
			glTranslatef(centerRad * 1.25, 0, 0);
			gluCylinder(quad, centerRad * .25, 0, centerRad, 10, 10);
			glPopMatrix();

			glPushMatrix(); //eye 1
			glRotatef(ang, 0, 0, 1);
			glTranslatef(centerRad * 1.4, centerRad * .15, .70 * centerRad);
			glutSolidSphere(centerRad * .085, 8, 8);
			glPopMatrix();

			glPushMatrix(); //eye 2
			glRotatef(ang, 0, 0, 1);
			glTranslatef(centerRad * 1.4, centerRad * -.15, .70 * centerRad);
			glutSolidSphere(centerRad * .085, 8, 8);
			glPopMatrix();

			glPushMatrix();

			glRotatef(180, 1, 0, 0);
			quad = gluNewQuadric();
			glPushMatrix(); //nose
			glRotatef(ang, 0, 0, 1);
			glTranslatef(centerRad * 1.25, 0, 0);
			gluCylinder(quad, centerRad * .25, 0, centerRad, 10, 10);
			glPopMatrix();

			glPushMatrix(); //eye 1
			glRotatef(ang, 0, 0, 1);
			glTranslatef(centerRad * 1.4, centerRad * .15, .70 * centerRad);
			glutSolidSphere(centerRad * .085, 8, 8);
			glPopMatrix();

			glPushMatrix(); //eye 2
			glRotatef(ang, 0, 0, 1);
			glTranslatef(centerRad * 1.4, centerRad * -.15, .70 * centerRad);
			glutSolidSphere(centerRad * .085, 8, 8);
			glPopMatrix();

			glPopMatrix();
		}
	}

	glPopMatrix();
}