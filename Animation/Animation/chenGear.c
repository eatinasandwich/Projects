#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "Gears.h"

#define false 0
#define true 1
#define PI 3.14159

void hollowCylinder(float innerRadius, float outerRadius, int sides, float length) {

	int i = 0;
	double r1 = innerRadius;
	double r2 = outerRadius;
	double ang = 0;
	double angIncr = 2 * 3.14159 / sides;
	double z = length / 2;

	glNormal3f(0, 0, 1);

	for (int i = 0; i < sides; i++) {
		glBegin(GL_POLYGON);
		glVertex3f(r1*cos(ang), r1*sin(ang), z);
		glVertex3f(r2*cos(ang), r2*sin(ang), z);
		glVertex3f(r2*cos(ang + angIncr), r2*sin(ang + angIncr), z);
		glVertex3f(r1*cos(ang + angIncr), r1*sin(ang + angIncr), z);
		glEnd();
		ang += angIncr;
	}

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	for (int i = 0; i < sides; i++) {
		glBegin(GL_POLYGON);
		glVertex3f(r1*cos(ang), r1*sin(ang), z);
		glVertex3f(r2*cos(ang), r2*sin(ang), z);
		glVertex3f(r2*cos(ang + angIncr), r2*sin(ang + angIncr), z);
		glVertex3f(r1*cos(ang + angIncr), r1*sin(ang + angIncr), z);
		glEnd();
		ang += angIncr;
	}
	glPopMatrix();

	// make outer side of hollow cylinder
	for (int i = 0; i < sides; i++) {
		glBegin(GL_POLYGON);

		glNormal3f(cos(ang), sin(ang), 0);
		glVertex3f(r2*cos(ang), r2*sin(ang), -z);
		glNormal3f(cos(ang + angIncr), sin(ang + angIncr), 0);
		glVertex3f(r2*cos(ang + angIncr), r2*sin(ang + angIncr), -z);
		glVertex3f(r2*cos(ang + angIncr), r2*sin(ang + angIncr), z);
		glNormal3f(cos(ang), sin(ang), 0);
		glVertex3f(r2*cos(ang), r2*sin(ang), z);

		glEnd();
		ang += angIncr;
	}

	// make inner side of hollow cylinder
	for (int i = 0; i < sides; i++) {
		glBegin(GL_POLYGON);

		glNormal3f(-cos(ang), -sin(ang), 0);
		glVertex3f(r1*cos(ang), r1*sin(ang), -z);
		glNormal3f(-cos(ang + angIncr), -sin(ang + angIncr), 0);
		glVertex3f(r1*cos(ang + angIncr), r1*sin(ang + angIncr), -z);
		glVertex3f(r1*cos(ang + angIncr), r1*sin(ang + angIncr), z);
		glNormal3f(-cos(ang), -sin(ang), 0);
		glVertex3f(r1*cos(ang), r1*sin(ang), z);

		glEnd();
		ang += angIncr;
	}
}


void chenGear(int numTeeth, int numSpokes)
{
	float red[] = { 1, 0, 0 };
	float green[] = { 0, 1, 0 };
	float blue[] = { 0, 0, 1 };
	float gray[] = { 0.5, 0.5, 0.5 };
	float gold_a[] = { 0.24725, 0.1995, 0.0745 };
	float gold_d[] = { 0.75164, 0.60648, 0.22648 };
	float gold_s[] = { 0.628281, 0.555802, 0.366065 };
	float gold_spec = 0.4;

	glMaterialfv(GL_FRONT, GL_AMBIENT, gold_a);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, gold_d);
	glMaterialfv(GL_FRONT, GL_SPECULAR, gold_s);
	glMaterialf(GL_FRONT, GL_SHININESS, gold_spec * 128);

	int n = numTeeth * 2;
	int m = numSpokes;
	float radAxleToHouse = 0.125;
	float radHouseToInnerRim = 0.225;
	float radInnerRimToSpoke = 0.35;
	float radSpokeToOuterRim = 0.8;
	float radOuterRimToFrame = 0.9;
	float radFrameToTeeth = 1.0;
	float radTeethEdge = radFrameToTeeth * 1.2;
	float thickHouse = 3.25;
	float thickFrame = 2.0;
	float angInc = 360 / m;
	float ang = 0.0;
	float z = 0.1;
	float bevelZ = 0.04;
	float bevelR = 0.15;

	hollowCylinder(radAxleToHouse, radHouseToInnerRim, n, z * thickHouse);
	hollowCylinder(radHouseToInnerRim, radInnerRimToSpoke, n, z);
	hollowCylinder(radSpokeToOuterRim, radOuterRimToFrame, n, z);
	hollowCylinder(radOuterRimToFrame, radFrameToTeeth, n, z * thickFrame);

	for (int i = 0; i < m; i++) {

		glPushMatrix();
		glRotatef(ang, 0, 0, 1);
		glTranslatef((radInnerRimToSpoke + radOuterRimToFrame) / 2, 0, 0);
		glScalef(radOuterRimToFrame - radHouseToInnerRim, 0.15, z);
		glutSolidCube(1);
		glPopMatrix();

		ang += angInc;
	}

	glNormal3f(0, 0, 1);

	ang = 0;
	angInc = 2 * PI / n;

	float d = z * (thickHouse - 1) / 2;
	float bAng = 0;
	float bAngInc = 2 * PI / 32;
	for (int i = 0; i < n; i++) {       // house to inner rim bevel
		bAng = 0;
		for (int j = 0; j < 8; j++) {
			glBegin(GL_POLYGON);
			glNormal3f(cos(ang)*cos(bAng), sin(ang)*cos(bAng), sin(bAng));
			glVertex3f((radHouseToInnerRim + d*(1 - cos(bAng)))*cos(ang), (radHouseToInnerRim + d*(1 - cos(bAng)))*sin(ang), z / 2 * thickHouse - d*sin(bAng));
			glNormal3f(cos(ang + angInc)*cos(bAng), sin(ang + angInc)*cos(bAng), sin(bAng));
			glVertex3f((radHouseToInnerRim + d*(1 - cos(bAng)))*cos(ang + angInc), (radHouseToInnerRim + d*(1 - cos(bAng)))*sin(ang + angInc), z / 2 * thickHouse - d*sin(bAng));
			glNormal3f(cos(ang + angInc)*cos(bAng + angInc), sin(ang + angInc)*cos(bAng + angInc), sin(bAng + angInc));
			glVertex3f((radHouseToInnerRim + d*(1 - cos(bAng + bAngInc)))*cos(ang + angInc), (radHouseToInnerRim + d*(1 - cos(bAng + bAngInc)))*sin(ang + angInc), z / 2 * thickHouse - d*sin(bAng + bAngInc));
			glNormal3f(cos(ang)*cos(bAng + angInc), sin(ang)*cos(bAng + angInc), sin(bAng + angInc));
			glVertex3f((radHouseToInnerRim + d*(1 - cos(bAng + bAngInc)))*cos(ang), (radHouseToInnerRim + d*(1 - cos(bAng + bAngInc)))*sin(ang), z / 2 * thickHouse - d*sin(bAng + bAngInc));
			glEnd();

			bAng += bAngInc;
		}
		ang += angInc;
	}

	bAng = 0;
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	for (int i = 0; i < n; i++) {       // house to inner rim bevel, reverse side
		bAng = 0;
		for (int j = 0; j < 8; j++) {
			glBegin(GL_POLYGON);
			glNormal3f(cos(ang)*cos(bAng), sin(ang)*cos(bAng), sin(bAng));
			glVertex3f((radHouseToInnerRim + d*(1 - cos(bAng)))*cos(ang), (radHouseToInnerRim + d*(1 - cos(bAng)))*sin(ang), z / 2 * thickHouse - d*sin(bAng));
			glNormal3f(cos(ang + angInc)*cos(bAng), sin(ang + angInc)*cos(bAng), sin(bAng));
			glVertex3f((radHouseToInnerRim + d*(1 - cos(bAng)))*cos(ang + angInc), (radHouseToInnerRim + d*(1 - cos(bAng)))*sin(ang + angInc), z / 2 * thickHouse - d*sin(bAng));
			glNormal3f(cos(ang + angInc)*cos(bAng + angInc), sin(ang + angInc)*cos(bAng + angInc), sin(bAng + angInc));
			glVertex3f((radHouseToInnerRim + d*(1 - cos(bAng + bAngInc)))*cos(ang + angInc), (radHouseToInnerRim + d*(1 - cos(bAng + bAngInc)))*sin(ang + angInc), z / 2 * thickHouse - d*sin(bAng + bAngInc));
			glNormal3f(cos(ang)*cos(bAng + angInc), sin(ang)*cos(bAng + angInc), sin(bAng + angInc));
			glVertex3f((radHouseToInnerRim + d*(1 - cos(bAng + bAngInc)))*cos(ang), (radHouseToInnerRim + d*(1 - cos(bAng + bAngInc)))*sin(ang), z / 2 * thickHouse - d*sin(bAng + bAngInc));
			glEnd();

			bAng += bAngInc;
		}
		ang += angInc;
	}
	glPopMatrix();

	d = z * (thickFrame - 1) / 2;
	bAng = 0;
	for (int i = 0; i < n; i++) {       // spoke to outer rim bevel
		bAng = 0;
		for (int j = 0; j < 8; j++) {
			glBegin(GL_POLYGON);
			glNormal3f(-cos(ang)*cos(bAng), -sin(ang)*cos(bAng), sin(bAng));
			glVertex3f((radOuterRimToFrame + d*(cos(bAng) - 1))*cos(ang), (radOuterRimToFrame + d*(cos(bAng) - 1))*sin(ang), z / 2 * thickFrame - d*sin(bAng));
			glNormal3f(-cos(ang + angInc)*cos(bAng), -sin(ang + angInc)*cos(bAng), sin(bAng));
			glVertex3f((radOuterRimToFrame + d*(cos(bAng) - 1))*cos(ang + angInc), (radOuterRimToFrame + d*(cos(bAng) - 1))*sin(ang + angInc), z / 2 * thickFrame - d*sin(bAng));
			glNormal3f(-cos(ang + angInc)*cos(bAng + angInc), -sin(ang + angInc)*cos(bAng + angInc), sin(bAng + angInc));
			glVertex3f((radOuterRimToFrame + d*(cos(bAng + bAngInc) - 1))*cos(ang + angInc), (radOuterRimToFrame + d*(cos(bAng + bAngInc) - 1))*sin(ang + angInc), z / 2 * thickFrame - d*sin(bAng + bAngInc));
			glNormal3f(-cos(ang)*cos(bAng + angInc), -sin(ang)*cos(bAng + angInc), sin(bAng + angInc));
			glVertex3f((radOuterRimToFrame + d*(cos(bAng + bAngInc) - 1))*cos(ang), (radOuterRimToFrame + d*(cos(bAng + bAngInc) - 1))*sin(ang), z / 2 * thickFrame - d*sin(bAng + bAngInc));
			glEnd();

			bAng += bAngInc;
		}
		ang += angInc;
	}

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	bAng = 0;
	for (int i = 0; i < n; i++) {       // spoke to outer rim bevel, reverse side
		bAng = 0;
		for (int j = 0; j < 8; j++) {
			glBegin(GL_POLYGON);
			glNormal3f(-cos(ang)*cos(bAng), -sin(ang)*cos(bAng), sin(bAng));
			glVertex3f((radOuterRimToFrame + d*(cos(bAng) - 1))*cos(ang), (radOuterRimToFrame + d*(cos(bAng) - 1))*sin(ang), z / 2 * thickFrame - d*sin(bAng));
			glNormal3f(-cos(ang + angInc)*cos(bAng), -sin(ang + angInc)*cos(bAng), sin(bAng));
			glVertex3f((radOuterRimToFrame + d*(cos(bAng) - 1))*cos(ang + angInc), (radOuterRimToFrame + d*(cos(bAng) - 1))*sin(ang + angInc), z / 2 * thickFrame - d*sin(bAng));
			glNormal3f(-cos(ang + angInc)*cos(bAng + angInc), -sin(ang + angInc)*cos(bAng + angInc), sin(bAng + angInc));
			glVertex3f((radOuterRimToFrame + d*(cos(bAng + bAngInc) - 1))*cos(ang + angInc), (radOuterRimToFrame + d*(cos(bAng + bAngInc) - 1))*sin(ang + angInc), z / 2 * thickFrame - d*sin(bAng + bAngInc));
			glNormal3f(-cos(ang)*cos(bAng + angInc), -sin(ang)*cos(bAng + angInc), sin(bAng + angInc));
			glVertex3f((radOuterRimToFrame + d*(cos(bAng + bAngInc) - 1))*cos(ang), (radOuterRimToFrame + d*(cos(bAng + bAngInc) - 1))*sin(ang), z / 2 * thickFrame - d*sin(bAng + bAngInc));
			glEnd();

			bAng += bAngInc;
		}
		ang += angInc;
	}
	glPopMatrix();

	ang = 0;
	angInc = 2 * PI / n;
	int drawTooth = false;
	for (int i = 0; i < n; i++) {       // face of the teeth
		drawTooth = !drawTooth;
		if (drawTooth) {
			float nx, ny, nz;

			calcNormal(radFrameToTeeth*cos(ang), radFrameToTeeth*sin(ang), z,
				radTeethEdge*cos(ang + angInc*bevelR), radTeethEdge*sin(ang + angInc*bevelR), z - bevelZ,
				radTeethEdge*cos(ang + angInc*(1 - bevelR)), radTeethEdge*sin(ang + angInc*(1 - bevelR)), z - bevelZ,
				&nx, &ny, &nz);

			glNormal3f(nx, ny, nz);
			glBegin(GL_POLYGON);
			glVertex3f(radFrameToTeeth*cos(ang), radFrameToTeeth*sin(ang), z);
			glVertex3f(radTeethEdge*cos(ang + angInc*bevelR), radTeethEdge*sin(ang + angInc*bevelR), z - bevelZ);
			glVertex3f(radTeethEdge*cos(ang + angInc*(1 - bevelR)), radTeethEdge*sin(ang + angInc*(1 - bevelR)), z - bevelZ);
			glVertex3f(radFrameToTeeth*cos(ang + angInc), radFrameToTeeth*sin(ang + angInc), z);
			glEnd();
		}
		ang += angInc;
	}

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	ang = 0;
	drawTooth = (numTeeth + 1) % 2;
	for (int i = 0; i < n; i++) {       // face of the teeth, flip side
		drawTooth = !drawTooth;
		if (drawTooth) {
			float nx, ny, nz;

			calcNormal(radFrameToTeeth*cos(ang), radFrameToTeeth*sin(ang), z,
				radTeethEdge*cos(ang + angInc*bevelR), radTeethEdge*sin(ang + angInc*bevelR), z - bevelZ,
				radTeethEdge*cos(ang + angInc*(1 - bevelR)), radTeethEdge*sin(ang + angInc*(1 - bevelR)), z - bevelZ,
				&nx, &ny, &nz);

			glNormal3f(nx, ny, nz);
			glBegin(GL_POLYGON);
			glVertex3f(radFrameToTeeth*cos(ang), radFrameToTeeth*sin(ang), z);
			glVertex3f(radTeethEdge*cos(ang + angInc*bevelR), radTeethEdge*sin(ang + angInc*bevelR), z - bevelZ);
			glVertex3f(radTeethEdge*cos(ang + angInc*(1 - bevelR)), radTeethEdge*sin(ang + angInc*(1 - bevelR)), z - bevelZ);
			glVertex3f(radFrameToTeeth*cos(ang + angInc), radFrameToTeeth*sin(ang + angInc), z);
			glEnd();
		}
		ang += angInc;
	}
	glPopMatrix();



	ang = 0;

	drawTooth = false;
	for (int i = 0; i < n; i++) {
		drawTooth = !drawTooth;
		if (drawTooth) {
			glNormal3f(radTeethEdge*cos(ang + angInc / 2), radTeethEdge*sin(ang + angInc / 2), 0);
			glBegin(GL_POLYGON);
			glVertex3f(radTeethEdge*cos(ang + angInc*bevelR), radTeethEdge*sin(ang + angInc*bevelR), -(z - bevelZ));
			glVertex3f(radTeethEdge*cos(ang + angInc*(1 - bevelR)), radTeethEdge*sin(ang + angInc*(1 - bevelR)), -(z - bevelZ));
			glVertex3f(radTeethEdge*cos(ang + angInc*(1 - bevelR)), radTeethEdge*sin(ang + angInc*(1 - bevelR)), z - bevelZ);
			glVertex3f(radTeethEdge*cos(ang + angInc*bevelR), radTeethEdge*sin(ang + angInc*bevelR), z - bevelZ);
			glEnd();
		}
		ang += angInc;
	}

	ang = 0;

	drawTooth = false;
	for (int i = 0; i < n; i++) {
		drawTooth = !drawTooth;
		if (drawTooth) {
			float nx, ny, nz;

			calcNormal(radFrameToTeeth*cos(ang), radFrameToTeeth*sin(ang), -z,
				radTeethEdge*cos(ang + angInc*bevelR), radTeethEdge*sin(ang + angInc*bevelR), -(z - bevelZ),
				radTeethEdge*cos(ang + angInc*bevelR), radTeethEdge*sin(ang + angInc*bevelR), z - bevelZ,
				&nx, &ny, &nz);

			glNormal3f(nx, ny, nz);
			glBegin(GL_POLYGON);
			glVertex3f(radFrameToTeeth*cos(ang), radFrameToTeeth*sin(ang), -z);
			glVertex3f(radTeethEdge*cos(ang + angInc*bevelR), radTeethEdge*sin(ang + angInc*bevelR), -(z - bevelZ));
			glVertex3f(radTeethEdge*cos(ang + angInc*bevelR), radTeethEdge*sin(ang + angInc*bevelR), z - bevelZ);
			glVertex3f(radFrameToTeeth*cos(ang), radFrameToTeeth*sin(ang), z);
			glEnd();


			calcNormal(radFrameToTeeth*cos(ang + angInc), radFrameToTeeth*sin(ang + angInc), -z,
				radTeethEdge*cos(ang + angInc*(1 - bevelR)), radTeethEdge*sin(ang + angInc*(1 - bevelR)), z - bevelZ,
				radTeethEdge*cos(ang + angInc*(1 - bevelR)), radTeethEdge*sin(ang + angInc*(1 - bevelR)), -(z - bevelZ),
				&nx, &ny, &nz);

			glNormal3f(nx, ny, nz);

			glBegin(GL_POLYGON);
			glVertex3f(radFrameToTeeth*cos(ang + angInc), radFrameToTeeth*sin(ang + angInc), -z);
			glVertex3f(radTeethEdge*cos(ang + angInc*(1 - bevelR)), radTeethEdge*sin(ang + angInc*(1 - bevelR)), -(z - bevelZ));
			glVertex3f(radTeethEdge*cos(ang + angInc*(1 - bevelR)), radTeethEdge*sin(ang + angInc*(1 - bevelR)), z - bevelZ);
			glVertex3f(radFrameToTeeth*cos(ang + angInc), radFrameToTeeth*sin(ang + angInc), z);
			glEnd();

		}
		ang += angInc;
	}






	glFlush();
}