#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "Gears.h"

#define true 1
#define false 0

void colemanGear(int numTeeth, int numSpokes) {

	float red[] = { 1, 0, 0 };
	float green[] = { 0, 1, 0 };
	float blue[] = { 0, 0, 1 };
	float gray[] = { 0.5, 0.5, 0.5 };
	float goldA[] = { 0.247, 0.199, 0.074, 1 };
	float goldD[] = { 0.751, 0.606, 0.226, 1 };
	float goldS[] = { 0.628, 0.556, 0.366, 1 };
	float silverA[] = { 0.192, 0.192, 0.192, 1 };
	float silverD[] = { 0.507, 0.507, 0.507, 1 };
	float silverS[] = { 0.608, 0.608, 0.608, 1 };
	float bronzeA[] = { 0.2125, 0.1275, 0.054, 1 };
	float bronzeD[] = { 0.714, 0.4284, 0.18144, 1 };
	float bronzeS[] = { 0.3935, 0.2719, 0.1667, 1 };


	glMaterialfv(GL_FRONT, GL_DIFFUSE, goldD);
	glMaterialfv(GL_FRONT, GL_AMBIENT, goldA);
	glMaterialfv(GL_FRONT, GL_SPECULAR, goldS);
	glMaterialf(GL_FRONT, GL_SHININESS, 128);
	// numTeeth = numTeeth * 2;
	float rad = 1.0;
	float outRad = rad * 1.2;
	float inRad = rad * 0.8;
	float smallRad = rad * 0.4;
	float angInc = 2 * 3.14159 / (numTeeth * 2);
	float ang = 0;
	float z = 0.1;

	glNormal3f(0, 0, 1);

	for (int i = 0; i < (numTeeth * 2); i++) {                //  majority of the gear face
		if (numSpokes > 0) {
			glBegin(GL_POLYGON);
			glVertex3f(inRad*cos(ang), inRad*sin(ang), z);
			glVertex3f(rad*cos(ang), rad*sin(ang), z);
			glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), z);
			glVertex3f(inRad*cos(ang + angInc), inRad*sin(ang + angInc), z);
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(0, 0, z);
			glVertex3f(smallRad*cos(ang), smallRad*sin(ang), z);
			glVertex3f(smallRad*cos(ang + angInc), smallRad*sin(ang + angInc), z);
			glEnd();
		}
		else {
			glBegin(GL_POLYGON);
			glVertex3f(0, 0, z);
			glVertex3f(rad*cos(ang), rad*sin(ang), z);
			glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), z);
			glEnd();
		}
		ang += angInc;
	}

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	ang = 0;                              //  majority of the gear face, flip side
	for (int i = 0; i < (numTeeth * 2); i++) {
		if (numSpokes > 0) {
			glBegin(GL_POLYGON);
			glVertex3f(inRad*cos(ang), inRad*sin(ang), z);
			glVertex3f(rad*cos(ang), rad*sin(ang), z);
			glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), z);
			glVertex3f(inRad*cos(ang + angInc), inRad*sin(ang + angInc), z);
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(0, 0, z);
			glVertex3f(smallRad*cos(ang), smallRad*sin(ang), z);
			glVertex3f(smallRad*cos(ang + angInc), smallRad*sin(ang + angInc), z);
			glEnd();
		}
		else {
			glBegin(GL_POLYGON);
			glVertex3f(0, 0, z);
			glVertex3f(rad*cos(ang), rad*sin(ang), z);
			glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), z);
			glEnd();
		}
		ang += angInc;
	}
	glPopMatrix();

	ang = 0;
	int drawTooth = false;
	for (int i = 0; i < numTeeth; i++) {       // face of the teeth
		drawTooth = !drawTooth;
		// if (drawTooth) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, bronzeD);
		glMaterialfv(GL_FRONT, GL_AMBIENT, bronzeA);
		glMaterialfv(GL_FRONT, GL_SPECULAR, bronzeS);


		float nx, ny, nz;

		calcNormal(rad*cos(ang + (angInc / 2)), rad*sin(ang + (angInc / 2)), z,
			outRad*cos(ang + (angInc / 3)), outRad*sin(ang + (angInc / 3)), (z - 0.05),
			outRad*cos(ang + angInc - (angInc / 3)), outRad*sin(ang + angInc - (angInc / 3)), (z - 0.05),
			&nx, &ny, &nz);

		glNormal3f(nx, ny, nz);

		glBegin(GL_POLYGON);
		glVertex3f(rad*cos(ang), rad*sin(ang), z);
		glVertex3f(outRad*cos(ang + (angInc / 3)), outRad*sin(ang + (angInc / 3)), (z - 0.05));
		glVertex3f(outRad*cos(ang + angInc - (angInc / 3)), outRad*sin(ang + angInc - (angInc / 3)), (z - 0.05));
		glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), z);
		glEnd();
		//}
		ang += (angInc * 2);
	}

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	ang = 0;
	drawTooth = true;
	if (numTeeth % 2 == 0) {
		ang += angInc;
	}
	for (int i = 0; i < numTeeth; i++) {       // face of the teeth, flip side
		drawTooth = !drawTooth;
		//  if (drawTooth) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, bronzeD);
		glMaterialfv(GL_FRONT, GL_AMBIENT, bronzeA);
		glMaterialfv(GL_FRONT, GL_SPECULAR, bronzeS);

		float nx, ny, nz;

		calcNormal(rad*cos(ang + (angInc / 2)), rad*sin(ang + (angInc / 2)), z,
			outRad*cos(ang + (angInc / 3)), outRad*sin(ang + (angInc / 3)), (z - 0.05),
			outRad*cos(ang + angInc - (angInc / 3)), outRad*sin(ang + angInc - (angInc / 3)), (z - 0.05),
			&nx, &ny, &nz);

		glNormal3f(nx, ny, nz);
		glBegin(GL_POLYGON);
		glVertex3f(rad*cos(ang), rad*sin(ang), z);
		glVertex3f(outRad*cos(ang + (angInc / 3)), outRad*sin(ang + (angInc / 3)), (z - 0.05));
		glVertex3f(outRad*cos(ang + angInc - (angInc / 3)), outRad*sin(ang + angInc - (angInc / 3)), (z - 0.05));
		glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), z);
		glEnd();
		//}
		ang += (angInc * 2);

	}
	glPopMatrix();




	ang = 0;
	for (int i = 0; i < (numTeeth * 2); i++) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, silverD);
		glMaterialfv(GL_FRONT, GL_AMBIENT, silverA);
		glMaterialfv(GL_FRONT, GL_SPECULAR, silverS);

		glNormal3f(rad*cos(ang + angInc / 2), rad*sin(ang + angInc / 2), 0);
		glBegin(GL_POLYGON);
		glVertex3f(rad*cos(ang), rad*sin(ang), -z);
		glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), -z);
		glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), z);
		glVertex3f(rad*cos(ang), rad*sin(ang), z);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(smallRad*cos(ang), smallRad*sin(ang), -z);
		glVertex3f(smallRad*cos(ang + angInc), smallRad*sin(ang + angInc), -z);
		glVertex3f(smallRad*cos(ang + angInc), smallRad*sin(ang + angInc), z);
		glVertex3f(smallRad*cos(ang), smallRad*sin(ang), z);
		glEnd();

		if (numSpokes > 0) {
			glPushMatrix();
			glRotatef(180, 0, 1, 0);
			glNormal3f(-rad*cos(ang + angInc / 2), -rad*sin(ang + angInc / 2), 0);
			glBegin(GL_POLYGON);
			glVertex3f(inRad*cos(ang), inRad*sin(ang), -z);
			glVertex3f(inRad*cos(ang + angInc), inRad*sin(ang + angInc), -z);
			glVertex3f(inRad*cos(ang + angInc), inRad*sin(ang + angInc), z);
			glVertex3f(inRad*cos(ang), inRad*sin(ang), z);
			glEnd();
			glPopMatrix();
		}
		ang += angInc;
	}
	//draw spokes
	if (numSpokes > 0) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, bronzeD);
		glMaterialfv(GL_FRONT, GL_AMBIENT, bronzeA);
		glMaterialfv(GL_FRONT, GL_SPECULAR, bronzeS);
		glPushMatrix();
		float angle = 0;
		float incr = 360 / numSpokes;
		//float cylAng = 0;
		glRotatef(90, 1, 0, 0);
		for (int i = 0; i < numSpokes; i++) {
			glRotatef(incr, 0, 1, 0);
			gluCylinder(gluNewQuadric(), 0.02, 0.02, .8, 8, 1);

		}
		glPopMatrix();
	}

	ang = 0;

	drawTooth = false;
	for (int i = 0; i < (numTeeth * 2); i++) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, goldD);
		glMaterialfv(GL_FRONT, GL_AMBIENT, goldA);
		glMaterialfv(GL_FRONT, GL_SPECULAR, goldS);
		drawTooth = !drawTooth;
		// if (drawTooth) {
		glNormal3f(outRad*cos(ang + angInc / 2), outRad*sin(ang + angInc / 2), 0);
		glBegin(GL_POLYGON);
		glVertex3f(outRad*cos(ang + (angInc / 3)), outRad*sin(ang + (angInc / 3)), -(z - 0.05));
		glVertex3f(outRad*cos(ang + angInc - (angInc / 3)), outRad*sin(ang + angInc - (angInc / 3)), -(z - 0.05));
		glVertex3f(outRad*cos(ang + angInc - (angInc / 3)), outRad*sin(ang + angInc - (angInc / 3)), z - 0.05);
		glVertex3f(outRad*cos(ang + (angInc / 3)), outRad*sin(ang + (angInc / 3)), z - 0.05);
		glEnd();
		//}
		ang += (angInc * 2);
	}

	ang = 0;

	drawTooth = false;
	for (int i = 0; i < numTeeth; i++) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, silverD);
		glMaterialfv(GL_FRONT, GL_AMBIENT, silverA);
		glMaterialfv(GL_FRONT, GL_SPECULAR, silverS);
		drawTooth = !drawTooth;
		//if (drawTooth) {
		float nx, ny, nz;

		calcNormal(rad*cos(ang), rad*sin(ang), -z,
			outRad*cos(ang + (angInc / 3)), outRad*sin(ang + (angInc / 3)), -(z - 0.05),
			outRad*cos(ang + (angInc / 3)), outRad*sin(ang + (angInc / 3)), (z - 0.05),
			&nx, &ny, &nz);

		glNormal3f(nx, ny, nz);
		glBegin(GL_POLYGON);
		glVertex3f(rad*cos(ang), rad*sin(ang), -z);
		glVertex3f(outRad*cos(ang + (angInc / 3)), outRad*sin(ang + (angInc / 3)), -(z - 0.05));
		glVertex3f(outRad*cos(ang + (angInc / 3)), outRad*sin(ang + (angInc / 3)), (z - 0.05));
		glVertex3f(rad*cos(ang), rad*sin(ang), z);
		glEnd();


		calcNormal(rad*cos(ang + angInc), rad*sin(ang + angInc), -z,
			outRad*cos(ang + angInc - (angInc / 3)), outRad*sin(ang + angInc - (angInc / 3)), z - 0.05,
			outRad*cos(ang + angInc - (angInc / 3)), outRad*sin(ang + angInc - (angInc / 3)), -(z - 0.05),
			&nx, &ny, &nz);

		glNormal3f(nx, ny, nz);

		glBegin(GL_POLYGON);
		glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), -z);
		glVertex3f(outRad*cos(ang + angInc - (angInc / 3)), outRad*sin(ang + angInc - (angInc / 3)), -(z - 0.05));
		glVertex3f(outRad*cos(ang + angInc - (angInc / 3)), outRad*sin(ang + angInc - (angInc / 3)), (z - 0.05));
		glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), z);
		glEnd();

		//}
		ang += (angInc * 2);
	}


}
