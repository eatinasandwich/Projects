//
//  Mitchell Alpert
//  Project3


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "Gears.h"

#define false 0
#define true 1

/*  Initialize material property, light source, lighting model,
*  and depth buffer.
*/

void alpertGear(int t, int s, double radius)
{

	glPushMatrix();
	float n = 2 * t;
	float toothAng = .3;
	float rad = radius;
	float outRad = rad * 1.2;
	float ringThickness = .1 * rad;
	float innerRingThickness = .15 *rad;
	float angInc = 2 * 3.14159 / n;
	float spInc = 3.14159 / s;
	float ang = 0;
	float z = 0.1;
	float spokeThickness = .2 * z;
	float innerZ = 2 * z;
	float innerRingRad = .05 * rad;
	float nx, ny, nz;

	glNormal3f(0, 0, 1);

	for (int i = 0; i < n; i++) {

		glBegin(GL_POLYGON);//face of outside ring
		glVertex3f((rad - ringThickness)*cos(ang), (rad - ringThickness)*sin(ang), z);
		glVertex3f(rad*cos(ang), rad*sin(ang), z);
		glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), z);
		glVertex3f((rad - ringThickness)*cos(ang + angInc), (rad - ringThickness)*sin(ang + angInc), z);
		glEnd();
		glBegin(GL_POLYGON);//face of inside ring
		glVertex3f((innerRingRad + innerRingThickness)*cos(ang), (innerRingRad + innerRingThickness)*sin(ang), innerZ);
		glVertex3f(innerRingRad*cos(ang), innerRingRad*sin(ang), innerZ);
		glVertex3f(innerRingRad*cos(ang + angInc), innerRingRad*sin(ang + angInc), innerZ);
		glVertex3f((innerRingRad + innerRingThickness)*cos(ang + angInc), (innerRingRad + innerRingThickness)*sin(ang + angInc), innerZ);
		glEnd();
		ang += angInc;
	}

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	ang = 0;

	for (int i = 0; i < n; i++) {

		glBegin(GL_POLYGON);//flipside face of outside ring
		glVertex3f((rad - ringThickness)*cos(ang), (rad - ringThickness)*sin(ang), z);
		glVertex3f(rad*cos(ang), rad*sin(ang), z);
		glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), z);
		glVertex3f((rad - ringThickness)*cos(ang + angInc), (rad - ringThickness)*sin(ang + angInc), z);
		glEnd();
		glBegin(GL_POLYGON);//flipside face of inside ring
		glVertex3f((innerRingRad + innerRingThickness)*cos(ang), (innerRingRad + innerRingThickness)*sin(ang), innerZ);
		glVertex3f(innerRingRad*cos(ang), innerRingRad*sin(ang), innerZ);
		glVertex3f(innerRingRad*cos(ang + angInc), innerRingRad*sin(ang + angInc), innerZ);
		glVertex3f((innerRingRad + innerRingThickness)*cos(ang + angInc), (innerRingRad + innerRingThickness)*sin(ang + angInc), innerZ);
		glEnd();

		ang += angInc;
	}

	glPopMatrix();

	ang = 0;
	for (int i = 0; i < n; i++) {
		glBegin(GL_POLYGON); //inside of outer ring
		glNormal3f(-cos(ang), -sin(ang), 0);
		glVertex3f((rad - ringThickness)*cos(ang), (rad - ringThickness)*sin(ang), -z);
		glNormal3f(-cos(ang + angInc), -sin(ang + angInc), 0);
		glVertex3f((rad - ringThickness)*cos(ang + angInc), (rad - ringThickness)*sin(ang + angInc), -z);
		glNormal3f(-cos(ang + angInc), -sin(ang + angInc), 0);
		glVertex3f((rad - ringThickness)*cos(ang + angInc), (rad - ringThickness)*sin(ang + angInc), z);
		glNormal3f(-cos(ang), -sin(ang), 0);
		glVertex3f((rad - ringThickness)*cos(ang), (rad - ringThickness)*sin(ang), z);
		glEnd();
		glBegin(GL_POLYGON); //inside of inner ring
		glNormal3f(-cos(ang), -sin(ang), 0);
		glVertex3f(innerRingRad*cos(ang), innerRingRad*sin(ang), -innerZ);
		glNormal3f(-cos(ang + angInc), -sin(ang + angInc), 0);
		glVertex3f(innerRingRad*cos(ang + angInc), innerRingRad*sin(ang + angInc), -innerZ);
		glNormal3f(-cos(ang + angInc), -sin(ang + angInc), 0);
		glVertex3f(innerRingRad*cos(ang + angInc), innerRingRad*sin(ang + angInc), innerZ);
		glNormal3f(-cos(ang), -sin(ang), 0);
		glVertex3f(innerRingRad*cos(ang), innerRingRad*sin(ang), innerZ);
		glEnd();

		ang += angInc;
	}


	ang = 0;
	int drawTooth = false;
	for (int i = 0; i < n; i++) {       // face of the teeth
		calcNormal(rad*cos(ang), rad*sin(ang), z,
			outRad*cos(ang), outRad*sin(ang), toothAng * z,
			outRad*cos(ang + angInc), outRad*sin(ang + angInc), toothAng * z,
			&nx, &ny, &nz);

		glNormal3f(nx, ny, nz);
		drawTooth = !drawTooth;
		if (drawTooth) {
			glBegin(GL_POLYGON);
			glVertex3f(rad*cos(ang), rad*sin(ang), z);
			glVertex3f(outRad*cos(ang), outRad*sin(ang), toothAng * z);
			glVertex3f(outRad*cos(ang + angInc), outRad*sin(ang + angInc), toothAng * z);
			glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), z);
			glEnd();
		}
		ang += angInc;
	}

	glPushMatrix();
	glRotatef(180, 0, 1, 0);

	drawTooth = true;
	for (int i = 0; i < n; i++) {       // face of the teeth, flip side
		calcNormal(rad*cos(ang), rad*sin(ang), z,
			outRad*cos(ang), outRad*sin(ang), toothAng * z,
			outRad*cos(ang + angInc), outRad*sin(ang + angInc), toothAng * z,
			&nx, &ny, &nz);

		glNormal3f(nx, ny, nz);
		drawTooth = !drawTooth;
		if (drawTooth) {
			glBegin(GL_POLYGON);
			glVertex3f(rad*cos(ang), rad*sin(ang), z);
			glVertex3f(outRad*cos(ang), outRad*sin(ang), toothAng * z);
			glVertex3f(outRad*cos(ang + angInc), outRad*sin(ang + angInc), toothAng * z);
			glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), z);
			glEnd();
		}
		ang += angInc;
	}
	glPopMatrix();


	ang = 0;
	for (int i = 0; i < n; i++) {

		glNormal3f(rad*cos(ang + angInc / 2), rad*sin(ang + angInc / 2), 0);
		glBegin(GL_POLYGON); //space inbetween teeth
		glVertex3f(rad*cos(ang), rad*sin(ang), -z);
		glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), -z);
		glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), z);
		glVertex3f(rad*cos(ang), rad*sin(ang), z);
		glEnd();
		glBegin(GL_POLYGON); //outside of inner ring
		glNormal3f(cos(ang), sin(ang), 0);
		glVertex3f((innerRingRad + innerRingThickness)*cos(ang), (innerRingRad + innerRingThickness)*sin(ang), -innerZ);
		glNormal3f(cos(ang + angInc), sin(ang + angInc), 0);
		glVertex3f((innerRingRad + innerRingThickness)*cos(ang + angInc), (innerRingRad + innerRingThickness)*sin(ang + angInc), -innerZ);
		glVertex3f((innerRingRad + innerRingThickness)*cos(ang + angInc), (innerRingRad + innerRingThickness)*sin(ang + angInc), innerZ);
		glNormal3f(cos(ang), sin(ang), 0);
		glVertex3f((innerRingRad + innerRingThickness)*cos(ang), (innerRingRad + innerRingThickness)*sin(ang), innerZ);
		glEnd();

		ang += angInc;
	}


	ang = 0;

	drawTooth = false; //tooth cap
	for (int i = 0; i < n; i++) {
		drawTooth = !drawTooth;
		if (drawTooth) {
			glNormal3f(outRad*cos(ang + angInc / 2), outRad*sin(ang + angInc / 2), 0);
			glBegin(GL_POLYGON);
			glVertex3f(outRad*cos(ang), outRad*sin(ang), -z*toothAng);
			glVertex3f(outRad*cos(ang + angInc), outRad*sin(ang + angInc), -z*toothAng);
			glVertex3f(outRad*cos(ang + angInc), outRad*sin(ang + angInc), z*toothAng);
			glVertex3f(outRad*cos(ang), outRad*sin(ang), z*toothAng);
			glEnd();
		}
		ang += angInc;
	}

	ang = 0;

	drawTooth = false;
	for (int i = 0; i < n; i++) {
		drawTooth = !drawTooth;
		if (drawTooth) {

			calcNormal(rad*cos(ang), rad*sin(ang), -z,
				outRad*cos(ang), outRad*sin(ang), -z*toothAng,
				outRad*cos(ang), outRad*sin(ang), z*toothAng,
				&nx, &ny, &nz);

			glNormal3f(nx, ny, nz);
			glBegin(GL_POLYGON);
			glVertex3f(rad*cos(ang), rad*sin(ang), -z);
			glVertex3f(outRad*cos(ang), outRad*sin(ang), -z*toothAng);
			glVertex3f(outRad*cos(ang), outRad*sin(ang), z*toothAng);
			glVertex3f(rad*cos(ang), rad*sin(ang), z);
			glEnd();


			calcNormal(rad*cos(ang + angInc), rad*sin(ang + angInc), -z,
				outRad*cos(ang + angInc), outRad*sin(ang + angInc), z*toothAng,
				outRad*cos(ang + angInc), outRad*sin(ang + angInc), -z*toothAng,
				&nx, &ny, &nz);

			glNormal3f(nx, ny, nz);

			glBegin(GL_POLYGON);
			glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), -z);
			glVertex3f(outRad*cos(ang + angInc), outRad*sin(ang + angInc), -z*toothAng);
			glVertex3f(outRad*cos(ang + angInc), outRad*sin(ang + angInc), z*toothAng);
			glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), z);
			glEnd();

		}
		ang += angInc;
	}

	//spokes
	z = spokeThickness;
	ang = 0;
	calcNormal((innerRingRad + innerRingThickness) * cos(ang), (innerRingRad + innerRingThickness)*sin(ang), z,
		rad*cos(ang), rad*sin(ang), z,
		rad*cos(ang + spInc), rad*sin(ang + spInc), z,
		&nx, &ny, &nz);

	glNormal3f(nx, ny, nz);
	for (int i = 0; i < s; i++) {
		drawTooth = !drawTooth;
		glBegin(GL_POLYGON);
		glVertex3f((innerRingRad + innerRingThickness) * cos(ang), (innerRingRad + innerRingThickness)*sin(ang), z);
		glVertex3f(rad*cos(ang), rad*sin(ang), z);
		glVertex3f(rad*cos(ang + spInc), rad*sin(ang + spInc), z);
		glVertex3f((innerRingRad + innerRingThickness) * cos(ang + spInc), (innerRingRad + innerRingThickness)*sin(ang + spInc), z);
		glEnd();
		ang += 2 * spInc;
	}
	glPushMatrix();
	glRotatef(180, 180, 1, 0);

	calcNormal((innerRingRad + innerRingThickness) * cos(ang), (innerRingRad + innerRingThickness)*sin(ang), z,
		rad*cos(ang), rad*sin(ang), z,
		rad*cos(ang + spInc), rad*sin(ang + spInc), z,
		&nx, &ny, &nz);

	glNormal3f(nx, ny, nz);

	ang = 0;
	for (int i = 0; i < s; i++) {

		glBegin(GL_POLYGON);
		glVertex3f((innerRingRad + innerRingThickness) * cos(ang), (innerRingRad + innerRingThickness)*sin(ang), z);
		glVertex3f(rad*cos(ang), rad*sin(ang), z);
		glVertex3f(rad*cos(ang - spInc), rad*sin(ang - spInc), z);
		glVertex3f((innerRingRad + innerRingThickness) * cos(ang - spInc), (innerRingRad + innerRingThickness)*sin(ang - spInc), z);
		glEnd();
		ang -= 2 * spInc;
	}

	glPopMatrix();
	ang = 0;

	for (int i = 0; i < s; i++) {

		calcNormal((innerRingRad + innerRingThickness) * cos(ang), (innerRingRad + innerRingThickness)*sin(ang), -z,
			rad*cos(ang), rad*sin(ang), -z,
			rad*cos(ang), rad*sin(ang), z,
			&nx, &ny, &nz);

		glNormal3f(nx, ny, nz);

		glBegin(GL_POLYGON);
		glVertex3f((innerRingRad + innerRingThickness) * cos(ang), (innerRingRad + innerRingThickness)*sin(ang), -z);
		glVertex3f(rad*cos(ang), rad*sin(ang), -z);
		glVertex3f(rad*cos(ang), rad*sin(ang), z);
		glVertex3f((innerRingRad + innerRingThickness) * cos(ang), (innerRingRad + innerRingThickness)*sin(ang), z);
		glEnd();
		ang += 2 * spInc;
	}

	ang = 0;
	for (int i = 0; i < s; i++) {
		calcNormal((innerRingRad + innerRingThickness) * -cos(ang + spInc), (innerRingRad + innerRingThickness)*-sin(ang + spInc), -z,
			rad*-cos(ang + spInc), rad*-sin(ang + spInc), -z,
			rad*-cos(ang + spInc), rad*-sin(ang + spInc), z,
			&nx, &ny, &nz);

		glNormal3f(nx, ny, nz);
		glBegin(GL_POLYGON);
		glVertex3f((innerRingRad + innerRingThickness) * cos(ang + spInc), (innerRingRad + innerRingThickness)*sin(ang + spInc), -z);
		glVertex3f(rad*cos(ang + spInc), rad*sin(ang + spInc), -z);
		glVertex3f(rad*cos(ang + spInc), rad*sin(ang + spInc), z);
		glVertex3f((innerRingRad + innerRingThickness) * cos(ang + spInc), (innerRingRad + innerRingThickness)*sin(ang + spInc), z);
		glEnd();
		ang += 2 * spInc;
	}

	glPopMatrix();
}
