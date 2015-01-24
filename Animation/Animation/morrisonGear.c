#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#define false 0
#define true 1



void morrisonGear(int numTeeth, int numSpokes) {

	GLfloat red[] = { 1, 0, 0 };
	GLfloat green[] = { 0, 1, 0 };
	GLfloat blue[] = { 0, 0, 1 };
	GLfloat yellow[] = { 1, 1, 0 };
	GLfloat aqua[] = { 0, 1, 1 };
	GLfloat gray[] = { 0.5, 0.5, 0.5 };
	GLfloat white[] = { 1, 1, 1 };
	GLfloat black[] = { 0, 0, 0 };

	GLfloat gold[] = { 1, 0.82353, 0 };
	GLfloat bronze[] = { 0.8039, 0.49019, 0.19607 };
	GLfloat silver[] = { 0.7529, 0.7529, 0.7529 };

	GLfloat specular[] = { 0, 0, 0, 1.0 };
	GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shiny[] = { 10.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shiny);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);

	int n = numTeeth;
	int spokes = numSpokes;
	float angSpoke = 2 * 3.14159 / (spokes * 5);

	float rad = 1.0;
	float outRad = rad * 1.15;
	float angInc = 2 * 3.14159 / n;
	float ang = 0;
	float z = 0.08;
	//opengl vrml materials
	// used as the radius for the coin in the middle that is skinnier that is not the gear
	float innerRad = 0.25;

	// used to create the outside radius for the inner gear
	float innerBevRad = innerRad - 0.1;

	// used for bevel z values to change thickness of the inner gear and outer gear
	float bevZ = 0.08;

	// used for z values of the teeth of the inner gear
	float inTeethZ = bevZ * 2;

	// used to create the inner radius for the inner gear
	float innerBevRad2 = innerBevRad + 0.04;

	// used for how long the teeth on the inside are
	float innerTeethRad = innerBevRad2 + 0.03;

	// used for the outside radius that the square base is ended for the outside teeth
	float outRad1 = rad + 0.05;

	// used as the inner radius for the beggining of the outside gear bevel
	float topInRad = 0.7;

	// used as the outer radius for the beggining of the outside gear bevel
	float topBevRad3 = topInRad + 0.05;

	// used for the inside radius of the bevel at the base of the outside teeth
	float topBevRad = 0.95;

	// used for the outer radius of the bevel at the base of the outside teeth
	float topBevRad2 = 0.98;

	// changes the z value to get the angle on the tooth walls, roof and face
	float zChange = 0.06;

	glNormal3f(0, 0, 1);
	/*
	There are two gears associated with this gear,
	an inner small one and the outer main gear.
	*/
	for (int i = 0; i < n; i++) {                //  majority of the gear face

		//********************************* inner coin/gear *************************************

		// draws the inner original face FRONT 
		glMaterialfv(GL_FRONT, GL_SPECULAR, gold);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, silver);
		glMaterialfv(GL_FRONT, GL_AMBIENT, white);

		glBegin(GL_POLYGON);
		glVertex3f(innerBevRad*cos(ang), innerBevRad*sin(ang), z);
		glVertex3f(innerRad*cos(ang), innerRad*sin(ang), z);
		glVertex3f(innerRad*cos(ang + angInc), innerRad*sin(ang + angInc), z);
		glVertex3f(innerBevRad*cos(ang + angInc), innerBevRad*sin(ang + angInc), z);
		glEnd();


		//gear
		// face for bevel inner bevel for gear FRONT
		glNormal3f(0, 0, 1);
		glMaterialfv(GL_FRONT, GL_SPECULAR, gold);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, bronze);
		glMaterialfv(GL_FRONT, GL_AMBIENT, white);

		glBegin(GL_POLYGON);
		glVertex3f(innerBevRad*cos(ang), innerBevRad*sin(ang), z + inTeethZ);
		glVertex3f(innerBevRad2*cos(ang), innerBevRad2*sin(ang), z + inTeethZ);
		glVertex3f(innerBevRad2*cos(ang + angInc), innerBevRad2*sin(ang + angInc), z + inTeethZ);
		glVertex3f(innerBevRad*cos(ang + angInc), innerBevRad*sin(ang + angInc), z + inTeethZ);
		glEnd();

		//********************************* end inner coin/gear *************************************



		//********************************* outer coin/gear *************************************

		// face for bevel upper FRONT
		glNormal3f(0, 0, 1);
		glBegin(GL_POLYGON);
		glVertex3f(topBevRad*cos(ang), topBevRad*sin(ang), z + bevZ);
		glVertex3f(rad*cos(ang), rad*sin(ang), z + bevZ);
		glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), z + bevZ);
		glVertex3f(topBevRad*cos(ang + angInc), topBevRad*sin(ang + angInc), z + bevZ);
		glEnd();

		// face for bevel lower FRONT
		glBegin(GL_POLYGON);
		glVertex3f(topBevRad3*cos(ang), topBevRad3*sin(ang), z + bevZ);
		glVertex3f(topInRad*cos(ang), topInRad*sin(ang), z + bevZ);
		glVertex3f(topInRad*cos(ang + angInc), topInRad*sin(ang + angInc), z + bevZ);
		glVertex3f(topBevRad3*cos(ang + angInc), topBevRad3*sin(ang + angInc), z + bevZ);
		glEnd();

		//draws face of the top coin, the inlay between spokes FRONT
		glMaterialfv(GL_FRONT, GL_SPECULAR, gold);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, silver);
		glMaterialfv(GL_FRONT, GL_AMBIENT, white);

		glBegin(GL_POLYGON);
		glVertex3f(topInRad*cos(ang), topInRad*sin(ang), z);
		glVertex3f(rad*cos(ang), rad*sin(ang), z);
		glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), z);
		glVertex3f(topInRad*cos(ang + angInc), topInRad*sin(ang + angInc), z);
		glEnd();

		//********************************* end outer coin/gear *************************************

		glNormal3f(0, 0, 1);

		ang += angInc;
	}
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	ang = 0;                              //  majority of the gear face, flip side
	for (int i = 0; i < n; i++) {

		//********************************* inner coin/gear *************************************
		// coin
		glMaterialfv(GL_FRONT, GL_SPECULAR, gold);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, silver);
		glMaterialfv(GL_FRONT, GL_AMBIENT, white);

		glBegin(GL_POLYGON);
		glVertex3f(innerBevRad*cos(ang), innerBevRad*sin(ang), z);
		glVertex3f(innerRad*cos(ang), innerRad*sin(ang), z);
		glVertex3f(innerRad*cos(ang + angInc), innerRad*sin(ang + angInc), z);
		glVertex3f(innerBevRad*cos(ang + angInc), innerBevRad*sin(ang + angInc), z);
		glEnd();

		//gear
		// opposite face for bevel inner bevel for gear REAR
		glMaterialfv(GL_FRONT, GL_SPECULAR, gold);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, bronze);
		glMaterialfv(GL_FRONT, GL_AMBIENT, white);

		glBegin(GL_POLYGON);
		glVertex3f(innerBevRad*cos(ang), innerBevRad*sin(ang), z + inTeethZ);
		glVertex3f(innerBevRad2*cos(ang), innerBevRad2*sin(ang), z + inTeethZ);
		glVertex3f(innerBevRad2*cos(ang + angInc), innerBevRad2*sin(ang + angInc), z + inTeethZ);
		glVertex3f(innerBevRad*cos(ang + angInc), innerBevRad*sin(ang + angInc), z + inTeethZ);
		glEnd();

		//********************************* end inner coin/gear *************************************

		//********************************* outer coin/gear *************************************

		// face for bevel upper REAR
		glBegin(GL_POLYGON);
		glVertex3f(topBevRad*cos(ang), topBevRad*sin(ang), z + bevZ);
		glVertex3f(rad*cos(ang), rad*sin(ang), z + bevZ);
		glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), z + bevZ);
		glVertex3f(topBevRad*cos(ang + angInc), topBevRad*sin(ang + angInc), z + bevZ);
		glEnd();

		// face for bevel lower REAR
		glNormal3f(0, 0, 1);
		glBegin(GL_POLYGON);
		glVertex3f(topBevRad3*cos(ang), topBevRad3*sin(ang), z + bevZ);
		glVertex3f(topInRad*cos(ang), topInRad*sin(ang), z + bevZ);
		glVertex3f(topInRad*cos(ang + angInc), topInRad*sin(ang + angInc), z + bevZ);
		glVertex3f(topBevRad3*cos(ang + angInc), topBevRad3*sin(ang + angInc), z + bevZ);
		glEnd();

		glNormal3f(0, 0, 1);
		//draws the top coin face, the inlay, between the spokes
		glMaterialfv(GL_FRONT, GL_SPECULAR, gold);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, silver);
		glMaterialfv(GL_FRONT, GL_AMBIENT, white);

		glBegin(GL_POLYGON);
		glVertex3f(topInRad*cos(ang), topInRad*sin(ang), z);
		glVertex3f(rad*cos(ang), rad*sin(ang), z);
		glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), z);
		glVertex3f(topInRad*cos(ang + angInc), topInRad*sin(ang + angInc), z);
		glEnd();

		//********************************* end outer coin/gear *************************************

		ang += angInc;
	}
	glPopMatrix();

	ang = 0;
	int drawTooth = false;
	for (int i = 0; i < n; i++) {       // face of the teeth
		drawTooth = !drawTooth;
		if (drawTooth) {

			//********************************* outer coin/gear *************************************

			//draw square bottom of top tooth, face FRONT
			glMaterialfv(GL_FRONT, GL_SPECULAR, gold);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, bronze);
			glMaterialfv(GL_FRONT, GL_AMBIENT, white);

			glBegin(GL_POLYGON);
			glNormal3f(0, 0, 1);
			glVertex3f(rad*cos(ang), rad*sin(ang), z + bevZ);
			glNormal3f(cos(ang - zChange), sin(ang - zChange), 1);
			glVertex3f(outRad1*cos(ang), outRad1*sin(ang), z + bevZ);
			glVertex3f(outRad1*cos(ang + angInc), outRad1*sin(ang + angInc), z + bevZ);
			glNormal3f(0, 0, 1);
			glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), z + bevZ);
			glEnd();

			//draw bent tooth face of top tooth FRONT
			glBegin(GL_POLYGON);
			glNormal3f(cos(ang - zChange), sin(ang - zChange), 1);
			glVertex3f(outRad1*cos(ang), outRad1*sin(ang), z + bevZ);
			glVertex3f(outRad*cos(ang + zChange), outRad*sin(ang + zChange), z + zChange);
			glVertex3f(outRad*cos(ang - zChange + angInc), outRad*sin(ang - zChange + angInc), z + zChange);
			glVertex3f(outRad1*cos(ang + angInc), outRad1*sin(ang + angInc), z + bevZ);
			glEnd();
			glNormal3f(0, 0, 1);

			//********************************* end outer coin/gear *************************************


			//********************************* inner coin/gear *************************************

			// draw bent tooth, inner teeth face FRONT SMALL
			glBegin(GL_POLYGON);
			glVertex3f(innerBevRad2*cos(ang), innerBevRad2*sin(ang), z + inTeethZ);
			glVertex3f(innerTeethRad*cos(ang + zChange), innerTeethRad*sin(ang + zChange), z + inTeethZ);
			glVertex3f(innerTeethRad*cos(ang - zChange + angInc), innerTeethRad*sin(ang - zChange + angInc), z + inTeethZ);
			glVertex3f(innerBevRad2*cos(ang + angInc), innerBevRad2*sin(ang + angInc), z + inTeethZ);
			glEnd();
			glNormal3f(0, 0, 1);

			//draw back of the tooth for if the tooth gets longer than the bevel face of middle coin
			glBegin(GL_POLYGON);
			glVertex3f(innerBevRad2*cos(ang), innerBevRad2*sin(ang), -z);
			glVertex3f(innerTeethRad*cos(ang + zChange), innerTeethRad*sin(ang + zChange), -z);
			glVertex3f(innerTeethRad*cos(ang - zChange + angInc), innerTeethRad*sin(ang - zChange + angInc), -z);
			glVertex3f(innerBevRad2*cos(ang + angInc), innerBevRad2*sin(ang + angInc), -z);
			glEnd();
			glNormal3f(0, 0, 1);

			//********************************* end inner coin/gear *************************************
		}
		ang += angInc;
	}


	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	ang = 0;
	drawTooth = true;
	for (int i = 0; i < n; i++) {       // face of the teeth, flip side
		drawTooth = !drawTooth;
		if (drawTooth) {

			//********************************* outer coin/gear *************************************

			//draw face of the bottom square back
			glBegin(GL_POLYGON);
			glNormal3f(0, 0, 1);
			glVertex3f(rad*cos(ang), rad*sin(ang), z + bevZ);
			glNormal3f(cos(ang - zChange), sin(ang - zChange), 1);
			glVertex3f(outRad1*cos(ang), outRad1*sin(ang), z + bevZ);
			glVertex3f(outRad1*cos(ang + angInc), outRad1*sin(ang + angInc), z + bevZ);
			glNormal3f(0, 0, 1);
			glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), z + bevZ);
			glEnd();

			//draw bent tooth, face of the top tooth back
			glBegin(GL_POLYGON);
			glNormal3f(cos(ang + zChange), sin(ang + zChange), 1);
			glVertex3f(outRad1*cos(ang), outRad1*sin(ang), z + bevZ);
			glVertex3f(outRad*cos(ang + zChange), outRad*sin(ang + zChange), z + zChange);
			glVertex3f(outRad*cos(ang - zChange + angInc), outRad*sin(ang - zChange + angInc), z + zChange);
			glVertex3f(outRad1*cos(ang + angInc), outRad1*sin(ang + angInc), z + bevZ);
			glEnd();
			glNormal3f(0, 0, 1);

			//********************************* end outer coin/gear *************************************



			//********************************* inner coin/gear *************************************

			// draw bent tooth, inner teeth face back small gear tooth
			glBegin(GL_POLYGON);
			glVertex3f(innerBevRad2*cos(ang), innerBevRad2*sin(ang), z + inTeethZ);
			glVertex3f(innerTeethRad*cos(ang + zChange), innerTeethRad*sin(ang + zChange), z + inTeethZ);
			glVertex3f(innerTeethRad*cos(ang - zChange + angInc), innerTeethRad*sin(ang - zChange + angInc), z + inTeethZ);
			glVertex3f(innerBevRad2*cos(ang + angInc), innerBevRad2*sin(ang + angInc), z + inTeethZ);
			glEnd();
			glNormal3f(0, 0, 1);

			//draw back of the tooth
			glBegin(GL_POLYGON);
			glVertex3f(innerBevRad2*cos(ang), innerBevRad2*sin(ang), -z);
			glVertex3f(innerTeethRad*cos(ang + zChange), innerTeethRad*sin(ang + zChange), -z);
			glVertex3f(innerTeethRad*cos(ang - zChange + angInc), innerTeethRad*sin(ang - zChange + angInc), -z);
			glVertex3f(innerBevRad2*cos(ang + angInc), innerBevRad2*sin(ang + angInc), -z);
			glEnd();
			glNormal3f(0, 0, 1);

			//********************************* end inner coin/gear *************************************

		}
		ang += angInc;
	}
	glPopMatrix();


	ang = 0;
	for (int i = 0; i < n; i++) {		// does the coin edge

		//********************************* inner coin *************************************

		// original
		// draws coin edge for inner coin thinner coin not gear
		glMaterialfv(GL_FRONT, GL_SPECULAR, gold);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, silver);
		glMaterialfv(GL_FRONT, GL_AMBIENT, white);

		glNormal3f(cos(ang), sin(ang), 0);
		glBegin(GL_POLYGON);
		glVertex3f(innerRad*cos(ang), innerRad*sin(ang), -z);
		glNormal3f(cos(ang + angInc), sin(ang + angInc), 0);
		glVertex3f(innerRad*cos(ang + angInc), innerRad*sin(ang + angInc), -z);
		glVertex3f(innerRad*cos(ang + angInc), innerRad*sin(ang + angInc), z);
		glNormal3f(cos(ang), sin(ang), 0);
		glVertex3f(innerRad*cos(ang), innerRad*sin(ang), z);
		glEnd();

		glMaterialfv(GL_FRONT, GL_SPECULAR, gold);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, bronze);
		glMaterialfv(GL_FRONT, GL_AMBIENT, white);

		// gear
		//setup coin edge for inner gear top
		glNormal3f(cos(ang), sin(ang), 0);
		glBegin(GL_POLYGON);
		glVertex3f(innerBevRad2*cos(ang), innerBevRad2*sin(ang), -z - inTeethZ);
		glNormal3f(cos(ang + angInc), sin(ang + angInc), 0);
		glVertex3f(innerBevRad2*cos(ang + angInc), innerBevRad2*sin(ang + angInc), -z - inTeethZ);
		glVertex3f(innerBevRad2*cos(ang + angInc), innerBevRad2*sin(ang + angInc), z + inTeethZ);
		glNormal3f(cos(ang), sin(ang), 0);
		glVertex3f(innerBevRad2*cos(ang), innerBevRad2*sin(ang), z + inTeethZ);
		glEnd();

		//setup coin edge for inner gear bottom
		glNormal3f(-cos(ang), -sin(ang), 0);
		glBegin(GL_POLYGON);
		glVertex3f(innerBevRad*cos(ang), innerBevRad*sin(ang), -z - inTeethZ);
		glNormal3f(-cos(ang + angInc), -sin(ang + angInc), 0);
		glVertex3f(innerBevRad*cos(ang + angInc), innerBevRad*sin(ang + angInc), -z - inTeethZ);
		glVertex3f(innerBevRad*cos(ang + angInc), innerBevRad*sin(ang + angInc), z + inTeethZ);
		glNormal3f(-cos(ang), -sin(ang), 0);
		glVertex3f(innerBevRad*cos(ang), innerBevRad*sin(ang), z + inTeethZ);
		glEnd();

		//********************************* end inner coin *************************************



		//********************************* outer coin *************************************

		//setup outer coin edge for outer gear TOP
		glNormal3f(cos(ang), sin(ang), 0);
		glBegin(GL_POLYGON);
		glVertex3f(rad*cos(ang), rad*sin(ang), -z - bevZ);
		glNormal3f(cos(ang + angInc), sin(ang + angInc), 0);
		glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), -z - bevZ);
		glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), z + bevZ);
		glNormal3f(cos(ang), sin(ang), 0);
		glVertex3f(rad*cos(ang), rad*sin(ang), z + bevZ);
		glEnd();

		//setup outer coin edge for outer gear BOTTOM
		glNormal3f(-cos(ang), -sin(ang), 0);
		glBegin(GL_POLYGON);
		glVertex3f(topBevRad*cos(ang), topBevRad*sin(ang), -z - bevZ);
		glNormal3f(-cos(ang + angInc), -sin(ang + angInc), 0);
		glVertex3f(topBevRad*cos(ang + angInc), topBevRad*sin(ang + angInc), -z - bevZ);
		glVertex3f(topBevRad*cos(ang + angInc), topBevRad*sin(ang + angInc), z + bevZ);
		glNormal3f(-cos(ang), -sin(ang), 0);
		glVertex3f(topBevRad*cos(ang), topBevRad*sin(ang), z + bevZ);
		glEnd();

		//draws the bottom coin edge of outer coin
		glNormal3f(-cos(ang), -sin(ang), 0);
		glBegin(GL_POLYGON);
		glVertex3f(topInRad*cos(ang), topInRad*sin(ang), -z - bevZ);
		glNormal3f(-cos(ang + angInc), -sin(ang + angInc), 0);
		glVertex3f(topInRad*cos(ang + angInc), topInRad*sin(ang + angInc), -z - bevZ);
		glVertex3f(topInRad*cos(ang + angInc), topInRad*sin(ang + angInc), z + bevZ);
		glNormal3f(-cos(ang), -sin(ang), 0);
		glVertex3f(topInRad*cos(ang), topInRad*sin(ang), z + bevZ);
		glEnd();

		//draws the edge for the lower bevel, upper edge
		glNormal3f(cos(ang), sin(ang), 0);
		glBegin(GL_POLYGON);
		glVertex3f(topBevRad3*cos(ang), topBevRad3*sin(ang), -z - bevZ);
		glNormal3f(cos(ang + angInc), sin(ang + angInc), 0);
		glVertex3f(topBevRad3*cos(ang + angInc), topBevRad3*sin(ang + angInc), -z - bevZ);
		glVertex3f(topBevRad3*cos(ang + angInc), topBevRad3*sin(ang + angInc), z + bevZ);
		glNormal3f(cos(ang), sin(ang), 0);
		glVertex3f(topBevRad3*cos(ang), topBevRad3*sin(ang), z + bevZ);
		glEnd();
		glNormal3f(0, 0, 1);

		//********************************* end outer coin *************************************
		ang += angInc;
	}


	ang = 0;
	for (int i = 0; i < spokes; i++) {	// does outer coin
		float nx, ny, nz;
		glNormal3f(0, 0, 1);

		//********************************* outer coin *************************************

		//draws spoke face front for the top coin FRONT
		glBegin(GL_POLYGON);
		glVertex3f(topInRad*cos(ang), topInRad*sin(ang), z + bevZ);
		glVertex3f(rad*cos(ang), rad*sin(ang), z + bevZ);
		glVertex3f(rad*cos(ang + angSpoke), rad*sin(ang + angSpoke), z + bevZ);
		glVertex3f(topInRad*cos(ang + angSpoke), topInRad*sin(ang + angSpoke), z + bevZ);
		glEnd();

		calcNormal(topInRad*cos(ang), topInRad*sin(ang), -z - bevZ,
			rad*cos(ang), rad*sin(ang), -z - bevZ,
			rad*cos(ang), rad*sin(ang), z + bevZ,
			&nx, &ny, &nz);

		glNormal3f(nx, ny, nz);
		// draws edge of spokes, the right edge
		glBegin(GL_POLYGON);
		glVertex3f(topInRad*cos(ang), topInRad*sin(ang), -z - bevZ);
		glNormal3f(nx, ny, nz);
		glVertex3f(rad*cos(ang), rad*sin(ang), -z - bevZ);
		glVertex3f(rad*cos(ang), rad*sin(ang), z + bevZ);
		glVertex3f(topInRad*cos(ang), topInRad*sin(ang), z + bevZ);
		glEnd();

		calcNormal(topInRad*cos(ang + angSpoke), topInRad*sin(ang + angSpoke), -z - bevZ,
			rad*cos(ang + angSpoke), rad*sin(ang + angSpoke), -z - bevZ,
			rad*cos(ang + angSpoke), rad*sin(ang + angSpoke), z + bevZ,
			&nx, &ny, &nz);

		glNormal3f(-nx, -ny, -nz);
		// draws edge of spokes opposite side, left edge
		glBegin(GL_POLYGON);
		glVertex3f(topInRad*cos(ang + angSpoke), topInRad*sin(ang + angSpoke), -z - bevZ);
		glVertex3f(rad*cos(ang + angSpoke), rad*sin(ang + angSpoke), -z - bevZ);
		glVertex3f(rad*cos(ang + angSpoke), rad*sin(ang + angSpoke), z + bevZ);
		glVertex3f(topInRad*cos(ang + angSpoke), topInRad*sin(ang + angSpoke), z + bevZ);
		glEnd();

		glNormal3f(0, 0, -1);
		//draws opposite spoke face, top REAR
		glBegin(GL_POLYGON);
		glVertex3f(topInRad*cos(ang), topInRad*sin(ang), -z - bevZ);
		glVertex3f(rad*cos(ang), rad*sin(ang), -z - bevZ);
		glVertex3f(rad*cos(ang + angSpoke), rad*sin(ang + angSpoke), -z - bevZ);
		glVertex3f(topInRad*cos(ang + angSpoke), topInRad*sin(ang + angSpoke), -z - bevZ);
		glEnd();
		ang += angSpoke * 5;

		//********************************* end outer coin *************************************
	}


	ang = 0.3;
	for (int i = 0; i <= spokes; i++) {	// does inner spokes
		float nx, ny, nz;
		glNormal3f(0, 0, 1);

		//********************************* inner coin *************************************


		//draws spoke face FRONT
		glBegin(GL_POLYGON);
		glVertex3f(innerRad*cos(ang), innerRad*sin(ang), z);
		glVertex3f((topBevRad3 - 0.01)*cos(ang), (topBevRad3 - 0.01)*sin(ang), z);
		glVertex3f((topBevRad3 - 0.01)*cos(ang + angSpoke), (topBevRad3 - 0.01)*sin(ang + angSpoke), z);
		glVertex3f(innerRad*cos(ang + angSpoke), innerRad*sin(ang + angSpoke), z);
		glEnd();

		calcNormal(innerRad*cos(ang), innerRad*sin(ang), -z,
			(topBevRad3 - 0.01)*cos(ang), (topBevRad3 - 0.01)*sin(ang), -z,
			(topBevRad3 - 0.01)*cos(ang), (topBevRad3 - 0.01)*sin(ang), z,
			&nx, &ny, &nz);

		glNormal3f(nx, ny, nz);
		// draws edge of spokes, right edge
		glBegin(GL_POLYGON);
		glVertex3f(innerRad*cos(ang), innerRad*sin(ang), -z);
		glNormal3f(nx, ny, nz);
		glVertex3f((topBevRad3 - 0.01)*cos(ang), (topBevRad3 - 0.01)*sin(ang), -z);
		glVertex3f((topBevRad3 - 0.01)*cos(ang), (topBevRad3 - 0.01)*sin(ang), z);
		glVertex3f(innerRad*cos(ang), innerRad*sin(ang), z);
		glEnd();

		calcNormal(innerRad*cos(ang + angSpoke), innerRad*sin(ang + angSpoke), -z,
			(topBevRad3 - 0.01)*cos(ang + angSpoke), (topBevRad3 - 0.01)*sin(ang + angSpoke), -z,
			(topBevRad3 - 0.01)*cos(ang + angSpoke), (topBevRad3 - 0.01)*sin(ang + angSpoke), z,
			&nx, &ny, &nz);

		glNormal3f(-nx, -ny, -nz);
		// draws edge of bevel spokes opposite side, left
		glBegin(GL_POLYGON);
		glVertex3f(innerRad*cos(ang + angSpoke), innerRad*sin(ang + angSpoke), -z);
		glVertex3f((topBevRad3 - 0.01)*cos(ang + angSpoke), (topBevRad3 - 0.01)*sin(ang + angSpoke), -z);
		glVertex3f((topBevRad3 - 0.01)*cos(ang + angSpoke), (topBevRad3 - 0.01)*sin(ang + angSpoke), z);
		glVertex3f(innerRad*cos(ang + angSpoke), innerRad*sin(ang + angSpoke), z);
		glEnd();

		glNormal3f(0, 0, -1);
		//draws opposite spoke face, REAR
		glBegin(GL_POLYGON);
		glVertex3f(innerRad*cos(ang), innerRad*sin(ang), -z);
		glVertex3f((topBevRad3 - 0.01)*cos(ang), (topBevRad3 - 0.01)*sin(ang), -z);
		glVertex3f((topBevRad3 - 0.01)*cos(ang + angSpoke), (topBevRad3 - 0.01)*sin(ang + angSpoke), -z);
		glVertex3f(innerRad*cos(ang + angSpoke), innerRad*sin(ang + angSpoke), -z);
		glEnd();
		ang += angSpoke * 5;

		//********************************* end inner coin *************************************
	}

	ang = 0;

	drawTooth = false;
	for (int i = 0; i < n; i++) {	// draws the tooth roof top
		drawTooth = !drawTooth;
		if (drawTooth) {
			// draws outer coin tooth roof front *******************************************************
			glNormal3f(outRad*cos(ang + angInc / 2), outRad*sin(ang + angInc / 2), 0);
			glBegin(GL_POLYGON);
			glVertex3f(outRad*cos(ang + zChange), outRad*sin(ang + zChange), -z - zChange);
			glVertex3f(outRad*cos(ang - zChange + angInc), outRad*sin(ang - zChange + angInc), -z - zChange);
			glVertex3f(outRad*cos(ang - zChange + angInc), outRad*sin(ang - zChange + angInc), z + zChange);
			glVertex3f(outRad*cos(ang + zChange), outRad*sin(ang + zChange), z + zChange);

			glEnd();

			// draws inner coin tooth roof front *******************************************************
			glNormal3f(innerTeethRad*cos(ang + angInc / 2), innerTeethRad*sin(ang + angInc / 2), 0);
			glBegin(GL_POLYGON);
			glVertex3f(innerTeethRad*cos(ang + zChange), innerTeethRad*sin(ang + zChange), z);
			glVertex3f(innerTeethRad*cos(ang - zChange + angInc), innerTeethRad*sin(ang - zChange + angInc), z);
			glVertex3f(innerTeethRad*cos(ang - zChange + angInc), innerTeethRad*sin(ang - zChange + angInc), z + inTeethZ);
			glVertex3f(innerTeethRad*cos(ang + zChange), innerTeethRad*sin(ang + zChange), z + inTeethZ);
			glEnd();

			// draws inner coin tooth roof back *******************************************************
			glNormal3f(innerTeethRad*cos(ang + angInc / 2), innerTeethRad*sin(ang + angInc / 2), 0);
			glBegin(GL_POLYGON);
			glVertex3f(innerTeethRad*cos(ang + zChange), innerTeethRad*sin(ang + zChange), -z);
			glVertex3f(innerTeethRad*cos(ang - zChange + angInc), innerTeethRad*sin(ang - zChange + angInc), -z);
			glVertex3f(innerTeethRad*cos(ang - zChange + angInc), innerTeethRad*sin(ang - zChange + angInc), -z - inTeethZ);
			glVertex3f(innerTeethRad*cos(ang + zChange), innerTeethRad*sin(ang + zChange), -z - inTeethZ);
			glEnd();
		}
		ang += angInc;
	}

	ang = 0;

	drawTooth = false;
	for (int i = 0; i < n; i++) {	// draws the tooth walls
		drawTooth = !drawTooth;
		if (drawTooth) {
			float nx, ny, nz;

			//********************************* inner coin *************************************

			//draw bent tooth on inner gear edge 
			//front right
			calcNormal(innerBevRad2*cos(ang), innerBevRad2*sin(ang), -z - inTeethZ,
				innerTeethRad*cos(ang + zChange), innerTeethRad*sin(ang + zChange), -z - inTeethZ,
				innerTeethRad*cos(ang + zChange), innerTeethRad*sin(ang + zChange), z + inTeethZ,
				&nx, &ny, &nz);

			glNormal3f(nx, ny, nz);
			//draw bent tooth wall inner tooth FRONT RIGHT
			glBegin(GL_POLYGON);
			glVertex3f(innerBevRad2*cos(ang), innerBevRad2*sin(ang), z);
			glVertex3f(innerTeethRad*cos(ang + zChange), innerTeethRad*sin(ang + zChange), z);
			glVertex3f(innerTeethRad*cos(ang + zChange), innerTeethRad*sin(ang + zChange), z + inTeethZ);
			glVertex3f(innerBevRad2*cos(ang), innerBevRad2*sin(ang), z + inTeethZ);
			glEnd();

			// front left
			calcNormal(innerBevRad2*cos(ang + angInc), innerBevRad2*sin(ang + angInc), -z - inTeethZ,
				innerTeethRad*cos(ang + zChange - angInc), innerTeethRad*sin(ang - zChange + angInc), z + inTeethZ,
				innerTeethRad*cos(ang + zChange - angInc), innerTeethRad*sin(ang - zChange + angInc), -z - inTeethZ,
				&nx, &ny, &nz);

			glNormal3f(nx, ny, nz);
			//draw bent tooth wall inner tooth FRONT LEFT
			glBegin(GL_POLYGON);
			glVertex3f(innerBevRad2*cos(ang + angInc), innerBevRad2*sin(ang + angInc), z);
			glVertex3f(innerTeethRad*cos(ang - zChange + angInc), innerTeethRad*sin(ang - zChange + angInc), z);
			glVertex3f(innerTeethRad*cos(ang - zChange + angInc), innerTeethRad*sin(ang - zChange + angInc), z + inTeethZ);
			glVertex3f(innerBevRad2*cos(ang + angInc), innerBevRad2*sin(ang + angInc), z + inTeethZ);
			glEnd();

			//back left
			calcNormal(innerBevRad2*cos(ang), innerBevRad2*sin(ang), -z - inTeethZ,
				innerTeethRad*cos(ang + zChange), innerTeethRad*sin(ang + zChange), -z - inTeethZ,
				innerTeethRad*cos(ang + zChange), innerTeethRad*sin(ang + zChange), z + inTeethZ,
				&nx, &ny, &nz);

			glNormal3f(nx, ny, nz);
			//draw bent tooth wall BACK LEFT
			glBegin(GL_POLYGON);
			glVertex3f(innerBevRad2*cos(ang), innerBevRad2*sin(ang), -z);
			glVertex3f(innerTeethRad*cos(ang + zChange), innerTeethRad*sin(ang + zChange), -z);
			glVertex3f(innerTeethRad*cos(ang + zChange), innerTeethRad*sin(ang + zChange), -z - inTeethZ);
			glVertex3f(innerBevRad2*cos(ang), innerBevRad2*sin(ang), -z - inTeethZ);
			glEnd();

			// back right
			calcNormal(innerBevRad2*cos(ang + angInc), innerBevRad2*sin(ang + angInc), -z - inTeethZ,
				innerTeethRad*cos(ang + zChange - angInc), innerTeethRad*sin(ang - zChange + angInc), z + inTeethZ,
				innerTeethRad*cos(ang + zChange - angInc), innerTeethRad*sin(ang - zChange + angInc), -z - inTeethZ,
				&nx, &ny, &nz);

			glNormal3f(nx, ny, nz);
			//draw bent tooth wall BACK RIGHT
			glBegin(GL_POLYGON);
			glVertex3f(innerBevRad2*cos(ang + angInc), innerBevRad2*sin(ang + angInc), -z);
			glVertex3f(innerTeethRad*cos(ang - zChange + angInc), innerTeethRad*sin(ang - zChange + angInc), -z);
			glVertex3f(innerTeethRad*cos(ang - zChange + angInc), innerTeethRad*sin(ang - zChange + angInc), -z - inTeethZ);
			glVertex3f(innerBevRad2*cos(ang + angInc), innerBevRad2*sin(ang + angInc), -z - inTeethZ);
			glEnd();

			//********************************* end inner coin *************************************



			//********************************* outer coin *************************************

			calcNormal(rad*cos(ang), rad*sin(ang), -z - bevZ,
				outRad1*cos(ang), outRad1*sin(ang), -z - bevZ,
				outRad1*cos(ang), outRad1*sin(ang), z + bevZ,
				&nx, &ny, &nz);

			glNormal3f(nx, ny, nz);

			// draw square wall right side
			glBegin(GL_POLYGON);
			glVertex3f(rad*cos(ang), rad*sin(ang), -z - bevZ);
			glVertex3f(outRad1*cos(ang), outRad1*sin(ang), -z - bevZ);
			glVertex3f(outRad1*cos(ang), outRad1*sin(ang), z + bevZ);
			glVertex3f(rad*cos(ang), rad*sin(ang), z + bevZ);
			glEnd();

			calcNormal(outRad1*cos(ang), outRad1*sin(ang), -z - bevZ,
				outRad*cos(ang + zChange), outRad*sin(ang + zChange), -z - bevZ,
				outRad*cos(ang + zChange), outRad*sin(ang + zChange), z + bevZ,
				&nx, &ny, &nz);

			glNormal3f(nx, ny, nz);

			//draw bent tooth right wall
			glBegin(GL_POLYGON);
			glVertex3f(outRad1*cos(ang), outRad1*sin(ang), -z - bevZ);
			glVertex3f(outRad*cos(ang + zChange), outRad*sin(ang + zChange), -z - zChange);
			glVertex3f(outRad*cos(ang + zChange), outRad*sin(ang + zChange), z + zChange);
			glVertex3f(outRad1*cos(ang), outRad1*sin(ang), z + bevZ);
			glEnd();

			calcNormal(rad*cos(ang + angInc), rad*sin(ang + angInc), -z - bevZ,
				outRad1*cos(ang + angInc), outRad1*sin(ang + angInc), z + bevZ,
				outRad1*cos(ang + angInc), outRad1*sin(ang + angInc), -z - bevZ,
				&nx, &ny, &nz);

			glNormal3f(nx, ny, nz);

			// draw square bottom for the top teeth left wall
			glBegin(GL_POLYGON);
			glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), -z - bevZ);
			glVertex3f(outRad1*cos(ang + angInc), outRad1*sin(ang + angInc), -z - bevZ);
			glVertex3f(outRad1*cos(ang + angInc), outRad1*sin(ang + angInc), z + bevZ);
			glVertex3f(rad*cos(ang + angInc), rad*sin(ang + angInc), z + bevZ);
			glEnd();

			calcNormal(outRad1*cos(ang + angInc), outRad1*sin(ang + angInc), -z - bevZ,
				outRad*cos(ang - zChange + angInc), outRad*sin(ang - zChange + angInc), z + bevZ,
				outRad*cos(ang - zChange + angInc), outRad*sin(ang - zChange + angInc), -z - bevZ,
				&nx, &ny, &nz);

			glNormal3f(nx, ny, nz);

			//draw bent tooth top wall left
			glBegin(GL_POLYGON);
			glVertex3f(outRad1*cos(ang + angInc), outRad1*sin(ang + angInc), -z - bevZ);
			glVertex3f(outRad*cos(ang - zChange + angInc), outRad*sin(ang - zChange + angInc), -z - zChange);
			glVertex3f(outRad*cos(ang - zChange + angInc), outRad*sin(ang - zChange + angInc), z + zChange);
			glVertex3f(outRad1*cos(ang + angInc), outRad1*sin(ang + angInc), z + bevZ);
			glEnd();

			//********************************* end outer coin *************************************
		}
		ang += angInc;
	}
   glPopMatrix();
}