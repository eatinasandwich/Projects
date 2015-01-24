//best number for spokes are roughly 4 - 12
//teeth need to be an even number

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#define false 0
#define true 1

#define curvesEnabled true

int firstCall;



void smithGear(int numTeeth, int numSpokes) {
    //if this is the first time being called we can set our textures
    if(!firstCall){
        init();
    }
    firstCall = true;
    
    //initialize values
    numSpokes = 2 * numSpokes;
    int numSmooth = 360;
    float red[] = {1,0,0};
    float green[] = {0,1,0};
    float blue[] = {0,0,1};
    float gray[] = {0.709,0.651,0.259};
    
    
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, gray);
    
    float rad = 1.0;
    float innerTeethPointRad = 0.22;
    float innerTeethRad = 0.32;
    float innerGearRad = 0.3;
    float smallRad = 0.4;
    float spokeRad = 0.8;
    float outRad = rad * 1.05;
    float toothRad = rad * 1.20;
    float angInc = 2*3.14159/numTeeth;
    float angIncSpoke = 2*3.14159/numTeeth;
    float angSmooth = 2*3.14159/numSmooth;
    float ang = 0;
    float z = 0.1;
    
	// smallest circle on the gear, front side
    glNormal3f(0,0,1);
    ang = 0;
    for (int i = 0; i < numSmooth; i++) {                
        glBegin(GL_POLYGON);
        glVertex3f(innerGearRad*cos(ang),innerGearRad*sin(ang),z);
        glVertex3f(smallRad*cos(ang),smallRad*sin(ang),z);
        glVertex3f(smallRad*cos(ang+angSmooth),smallRad*sin(ang+angSmooth),z);
        glVertex3f(innerGearRad*cos(ang+angSmooth),innerGearRad*sin(ang+angSmooth),z);
        glEnd();
        ang += angSmooth;
    }
    
	// Draws spokes, front side, and sides
    ang = 0;
    int drawTooth = false;
    for (int i = 0; i < numSmooth; i++) {                
        if(i % (numSmooth / numSpokes) == 0){
			//if we are starting a spoke draw the side of it
            drawTooth = !drawTooth;
            if (drawTooth) {
                
                float nx,ny,nz;
                //inside wall of spoke
                calcNormal( smallRad*cos(ang),   smallRad*sin(ang),-(z/2),
                spokeRad*cos(ang),spokeRad*sin(ang),-(z/2),
                spokeRad*cos(ang),spokeRad*sin(ang),(z/2),
                &nx,&ny,&nz);
                
                glNormal3f(nx,ny,nz);
                glBegin(GL_POLYGON);
                glVertex3f(   smallRad*cos(ang),   smallRad*sin(ang),-(z/2));
                glVertex3f(spokeRad*cos(ang),spokeRad*sin(ang),-(z/2));
                glVertex3f(spokeRad*cos(ang),spokeRad*sin(ang),(z/2));
                glVertex3f(   smallRad*cos(ang),   smallRad*sin(ang),(z/2));
                glEnd();
                
                float spokeAngel = (angSmooth * ((numSmooth / numSpokes)));
                //inside wall of spoke
                calcNormal( smallRad*cos(ang+spokeAngel),   smallRad*sin(ang+spokeAngel),-(z/2),
                spokeRad*cos(ang+spokeAngel),spokeRad*sin(ang+spokeAngel),(z/2),
                spokeRad*cos(ang+spokeAngel),spokeRad*sin(ang+spokeAngel),-(z/2),
                &nx,&ny,&nz);
                
                glNormal3f(nx,ny,nz);
                
                glBegin(GL_POLYGON);
                glVertex3f(   smallRad*cos(ang+spokeAngel),   smallRad*sin(ang+spokeAngel),-(z/2));
                glVertex3f(spokeRad*cos(ang+spokeAngel),spokeRad*sin(ang+spokeAngel),-(z/2));
                glVertex3f(spokeRad*cos(ang+spokeAngel),spokeRad*sin(ang+spokeAngel),(z/2));
                glVertex3f(   smallRad*cos(ang+spokeAngel),   smallRad*sin(ang+spokeAngel),(z/2));
                glEnd();
            }
        }
		//draw spoke
        if (drawTooth) {
            glBegin(GL_POLYGON);
            glVertex3f(smallRad*cos(ang),smallRad*sin(ang),(z/2));
            glVertex3f(spokeRad*cos(ang),spokeRad*sin(ang),(z/2));
            glVertex3f(spokeRad*cos(ang+angSmooth),spokeRad*sin(ang+angSmooth),(z/2));
            glVertex3f(smallRad*cos(ang+angSmooth),smallRad*sin(ang+angSmooth),(z/2));
            glEnd();
            
        }
        glNormal3f(0,0,1);
        ang += angSmooth;
    }
    
	//outer circle, front face
    ang = 0;
    for (int i = 0; i < numSmooth; i++) {                
        glBegin(GL_POLYGON);
        glVertex3f(spokeRad*cos(ang),spokeRad*sin(ang),z);
        glVertex3f(rad*cos(ang),rad*sin(ang),z);
        glVertex3f(rad*cos(ang+angSmooth),rad*sin(ang+angSmooth),z);
        glVertex3f(spokeRad*cos(ang+angSmooth),spokeRad*sin(ang+angSmooth),z);
        glEnd();
        ang += angSmooth;
    }
	//curved surface on the inside of the outer circle, front side, it can be enabled and disabled due to the performance issues with running it
	//change to false if better performance is wanted
    if(curvesEnabled) {
        
        //go around the gear in a circle
        ang = 0;
        for (int i = 0; i < numSmooth; i++) {     
			//at each point on the circle create a quarter circle, this gives us our curved surface
            float ang2 = 0;
            for (int j = 0; j < numSmooth / 4; j++) {
                
                float nx,ny,nz;
                calcNormal( spokeRad*cos(ang)-(z*cos(ang2) * cos(ang)),                          spokeRad*sin(ang)-(z*cos(ang2) * sin(ang)),                            z*sin(ang2),
                spokeRad*cos(ang)-(z*cos(ang2+angSmooth) * cos(ang)),                spokeRad*sin(ang)-(z*cos(ang2+angSmooth) * sin(ang)),                    z*sin(ang2+angSmooth),
                spokeRad*cos(ang+angSmooth)-(z*cos(ang2+angSmooth)  * cos(ang)),    spokeRad*sin(ang+angSmooth)-(z*cos(ang2+angSmooth) * sin(ang)),        z*sin(ang2+angSmooth),
                &nx,&ny,&nz);
                
				//draw a small polygon shifting away and up(towards the -z or +z)
                glNormal3f(nx,ny,nz);
                glBegin(GL_POLYGON);
                glVertex3f(spokeRad*cos(ang)-(z*cos(ang2) * cos(ang)),                            spokeRad*sin(ang)-(z*cos(ang2) * sin(ang)),                            z*sin(ang2));
                glVertex3f(spokeRad*cos(ang)-(z*cos(ang2+angSmooth) * cos(ang)),                spokeRad*sin(ang)-(z*cos(ang2+angSmooth) * sin(ang)),                    z*sin(ang2+angSmooth));
                glVertex3f(spokeRad*cos(ang+angSmooth)-(z*cos(ang2+angSmooth)  * cos(ang)),    spokeRad*sin(ang+angSmooth)-(z*cos(ang2+angSmooth) * sin(ang)),        z*sin(ang2+angSmooth));
                glVertex3f(spokeRad*cos(ang+angSmooth)-(z*cos(ang2) * cos(ang)),                spokeRad*sin(ang+angSmooth)-(z*cos(ang2) * sin(ang)),                    z*sin(ang2));
                glEnd();
                ang2 += angSmooth;
            }
            ang += angSmooth;
        }
    }
    
    glPushMatrix();
    glRotatef(180, 0,1,0);
    
	//curved surface on the inside of the outer circle, back side, it can be enabled and disabled due to the performance issues with running it
    if(curvesEnabled) {
        //go around the gear in a circle
        ang = 0;
        for (int i = 0; i < numSmooth; i++) {     
			//at each point on the circle create a quarter circle, this gives us our curved surface           
            float ang2 = 0;
            for (int j = 0; j < numSmooth / 4; j++) {
                
                float nx,ny,nz;
                calcNormal( spokeRad*cos(ang)-(z*cos(ang2) * cos(ang)),                          spokeRad*sin(ang)-(z*cos(ang2) * sin(ang)),                            z*sin(ang2),
                spokeRad*cos(ang)-(z*cos(ang2+angSmooth) * cos(ang)),                spokeRad*sin(ang)-(z*cos(ang2+angSmooth) * sin(ang)),                    z*sin(ang2+angSmooth),
                spokeRad*cos(ang+angSmooth)-(z*cos(ang2+angSmooth)  * cos(ang)),    spokeRad*sin(ang+angSmooth)-(z*cos(ang2+angSmooth) * sin(ang)),        z*sin(ang2+angSmooth),
                &nx,&ny,&nz);
                
				//draw a small polygon shifting away and up(towards the -z or +z)
                glNormal3f(nx,ny,nz);
                glBegin(GL_POLYGON);
                glVertex3f(spokeRad*cos(ang)-(z*cos(ang2) * cos(ang)),                            spokeRad*sin(ang)-(z*cos(ang2) * sin(ang)),                            z*sin(ang2));
                glVertex3f(spokeRad*cos(ang)-(z*cos(ang2+angSmooth) * cos(ang)),                spokeRad*sin(ang)-(z*cos(ang2+angSmooth) * sin(ang)),                    z*sin(ang2+angSmooth));
                glVertex3f(spokeRad*cos(ang+angSmooth)-(z*cos(ang2+angSmooth)  * cos(ang)),    spokeRad*sin(ang+angSmooth)-(z*cos(ang2+angSmooth) * sin(ang)),        z*sin(ang2+angSmooth));
                glVertex3f(spokeRad*cos(ang+angSmooth)-(z*cos(ang2) * cos(ang)),                spokeRad*sin(ang+angSmooth)-(z*cos(ang2) * sin(ang)),                    z*sin(ang2));
                glEnd();
                ang2 += angSmooth;
            }
            ang += angSmooth;
        }
    }
	
	
	// smallest circle on the gear, back side
    
    ang = 0;
    for (int i = 0; i < numSmooth; i++) {                
        glBegin(GL_POLYGON);
        glVertex3f(innerGearRad*cos(ang),innerGearRad*sin(ang),z);
        glVertex3f(smallRad*cos(ang),smallRad*sin(ang),z);
        glVertex3f(smallRad*cos(ang+angSmooth),smallRad*sin(ang+angSmooth),z);
        glVertex3f(innerGearRad*cos(ang+angSmooth),innerGearRad*sin(ang+angSmooth),z);
        glEnd();
        ang += angSmooth;
    }
    
	// backside of the spokes
    ang = 0;
    drawTooth = true;
    for (int i = 0; i < numSmooth; i++) {                
        if(i % (numSmooth / numSpokes) == 0){
            drawTooth = !drawTooth;
        }
        if (drawTooth) {
            glNormal3f(0,0,1);
            glBegin(GL_POLYGON);
            glVertex3f(smallRad*cos(ang),smallRad*sin(ang),(z/2));
            glVertex3f(spokeRad*cos(ang),spokeRad*sin(ang),(z/2));
            glVertex3f(spokeRad*cos(ang+angSmooth),spokeRad*sin(ang+angSmooth),(z/2));
            glVertex3f(smallRad*cos(ang+angSmooth),smallRad*sin(ang+angSmooth),(z/2));
            glEnd();
            
        }
        ang += angSmooth;
    }
    
	//outer circle near, back side
    ang = 0;
    for (int i = 0; i < numSmooth; i++) {                
        glBegin(GL_POLYGON);
        glVertex3f(spokeRad*cos(ang),spokeRad*sin(ang),z);
        glVertex3f(rad*cos(ang),rad*sin(ang),z);
        glVertex3f(rad*cos(ang+angSmooth),rad*sin(ang+angSmooth),z);
        glVertex3f(spokeRad*cos(ang+angSmooth),spokeRad*sin(ang+angSmooth),z);
        glEnd();
        ang += angSmooth;
    }
    glPopMatrix();
    
	
    // Outer Teeth, straight portion, front side
    ang = 0;
    drawTooth = false;
    for (int i = 0; i < numTeeth; i++) {       
        drawTooth = !drawTooth;
        if (drawTooth) {
            glBegin(GL_POLYGON);
            glVertex3f(   rad*cos(ang),   rad*sin(ang),z);
            glVertex3f(outRad*cos(ang),outRad*sin(ang),z);
            glVertex3f(outRad*cos(ang+angInc),outRad*sin(ang+angInc),z);
            glVertex3f(   rad*cos(ang+angInc),   rad*sin(ang+angInc),z);
            glEnd();
        }
        ang += angInc;
    }
    //outer teeth, pointed portion, front side
    ang = 0;
    drawTooth = false;
    for (int i = 0; i < numTeeth; i++) {       
        drawTooth = !drawTooth;
        if (drawTooth) {
            glBegin(GL_POLYGON);
            glVertex3f(   outRad*cos(ang),   outRad*sin(ang),z);
            glVertex3f(toothRad*cos(ang + (angInc / 4)),toothRad*sin(ang + (angInc / 4)),0.05);
            glVertex3f(toothRad*cos(ang+(3 * angInc / 4)),toothRad*sin(ang+(3 * angInc / 4)),0.05);
            glVertex3f(   outRad*cos(ang+angInc),   outRad*sin(ang+angInc),z);
            glEnd();
        }
        ang += angInc;
    }
	
	
    // Inner Teeth straight portion, front side (currently configured to not be visible)
    int smallTeeth = numTeeth / 2;
    float smallToothAngInc = angInc * 2;
    ang = 0;
    drawTooth = false;
    for (int i = 0; i < smallTeeth; i++) {       // face of the teeth
        drawTooth = !drawTooth;
        if (drawTooth) {
            glBegin(GL_POLYGON);
            glVertex3f(   innerGearRad*cos(ang),   innerGearRad*sin(ang),z);
            glVertex3f(innerTeethRad*cos(ang),innerTeethRad*sin(ang),z);
            glVertex3f(innerTeethRad*cos(ang+smallToothAngInc),innerTeethRad*sin(ang+smallToothAngInc),z);
            glVertex3f(   innerGearRad*cos(ang+smallToothAngInc),   innerGearRad*sin(ang+smallToothAngInc),z);
            glEnd();
        }
        ang += smallToothAngInc;
    }
	
	//inner teeth, pointed portion, front side
    ang = 0;
    drawTooth = false;
    for (int i = 0; i < smallTeeth; i++) {       // face of the teeth
        drawTooth = !drawTooth;
        if (drawTooth) {
            glBegin(GL_POLYGON);
            glVertex3f(   innerTeethRad*cos(ang),   innerTeethRad*sin(ang),z);
            glVertex3f(innerTeethPointRad*cos(ang + (smallToothAngInc / 4)),innerTeethPointRad*sin(ang + (smallToothAngInc / 4)),0.05);
            glVertex3f(innerTeethPointRad*cos(ang+(3 * smallToothAngInc / 4)),innerTeethPointRad*sin(ang+(3 * smallToothAngInc / 4)),0.05);
            glVertex3f(   innerTeethRad*cos(ang+smallToothAngInc),   innerTeethRad*sin(ang+smallToothAngInc),z);
            glEnd();
        }
        ang += smallToothAngInc;
    }
    
    glPushMatrix();
    glRotatef(180, 0,1,0);
    
    // Outer Teeth, straight portion, back side
    ang = 0;
    drawTooth = true;
    for (int i = 0; i < numTeeth; i++) {       // face of the teeth, flip side
        drawTooth = !drawTooth;
        if (drawTooth) {
            glBegin(GL_POLYGON);
            glVertex3f(   rad*cos(ang),   rad*sin(ang),z);
            glVertex3f(outRad*cos(ang),outRad*sin(ang),z);
            glVertex3f(outRad*cos(ang+angInc),outRad*sin(ang+angInc),z);
            glVertex3f(   rad*cos(ang+angInc),   rad*sin(ang+angInc),z);
            glEnd();
        }
        ang += angInc;
    }
    
    // Outer Teeth, pointed portion, back side
    ang = 0;
    drawTooth = true;
    for (int i = 0; i < numTeeth; i++) {       // face of the teeth
        drawTooth = !drawTooth;
        if (drawTooth) {
            glBegin(GL_POLYGON);
            glVertex3f(   outRad*cos(ang),   outRad*sin(ang),z);
            glVertex3f(toothRad*cos(ang + (angInc / 4)),toothRad*sin(ang + (angInc / 4)),0.05);
            glVertex3f(toothRad*cos(ang+(3 * angInc / 4)),toothRad*sin(ang+(3 * angInc / 4)),0.05);
            glVertex3f(   outRad*cos(ang+angInc),   outRad*sin(ang+angInc),z);
            glEnd();
        }
        ang += angInc;
    }
    // Inner Teeth straight portion, back side (currently configured to not be visible)
    ang = 0;
    drawTooth = true;
    for (int i = 0; i < smallTeeth; i++) {       // face of the teeth
        drawTooth = !drawTooth;
        if (drawTooth) {
            glBegin(GL_POLYGON);
            glVertex3f(   innerGearRad*cos(ang),   innerGearRad*sin(ang),z);
            glVertex3f(innerTeethRad*cos(ang),innerTeethRad*sin(ang),z);
            glVertex3f(innerTeethRad*cos(ang+smallToothAngInc),innerTeethRad*sin(ang+smallToothAngInc),z);
            glVertex3f(   innerGearRad*cos(ang+smallToothAngInc),   innerGearRad*sin(ang+smallToothAngInc),z);
            glEnd();
        }
        ang += smallToothAngInc;
    }
	
	//inner teeth, pointed portion, back side
    ang = 0;
    drawTooth = true;
    for (int i = 0; i < smallTeeth; i++) {       // face of the teeth
        drawTooth = !drawTooth;
        if (drawTooth) {
            glBegin(GL_POLYGON);
            glVertex3f(   innerTeethRad*cos(ang),   innerTeethRad*sin(ang),z);
            glVertex3f(innerTeethPointRad*cos(ang + (smallToothAngInc / 4)),innerTeethPointRad*sin(ang + (smallToothAngInc / 4)),0.05);
            glVertex3f(innerTeethPointRad*cos(ang+(3 * smallToothAngInc / 4)),innerTeethPointRad*sin(ang+(3 * smallToothAngInc / 4)),0.05);
            glVertex3f(   innerTeethRad*cos(ang+smallToothAngInc),   innerTeethRad*sin(ang+smallToothAngInc),z);
            glEnd();
        }
        ang += smallToothAngInc;
    }
    
    glPopMatrix();
    
    ang = 0;
    for (int i = 0; i < numSmooth; i++) {
        // surface facing out of the outer circle (the space between teeth)
        glNormal3f(rad*cos(ang+angSmooth/2),rad*sin(ang+angSmooth/2),0);
        glBegin(GL_POLYGON);
        glVertex3f(rad*cos(ang),rad*sin(ang),-z);
        glVertex3f(rad*cos(ang+angSmooth),rad*sin(ang+angSmooth),-z);
        glVertex3f(rad*cos(ang+angSmooth),rad*sin(ang+angSmooth),z);
        glVertex3f(rad*cos(ang),rad*sin(ang),z);
        glEnd();
        
		//space between inner gear teeth
        glNormal3f(innerGearRad*cos(ang+angSmooth/2 + 135),innerGearRad*sin(ang+angSmooth/2 + 135),0);
        glBegin(GL_POLYGON);
        glVertex3f(innerGearRad*cos(ang),innerGearRad*sin(ang),z);
        glVertex3f(innerGearRad*cos(ang+angSmooth),innerGearRad*sin(ang+angSmooth),z);
        glVertex3f(innerGearRad*cos(ang+angSmooth),innerGearRad*sin(ang+angSmooth),-z);
        glVertex3f(innerGearRad*cos(ang),innerGearRad*sin(ang),-z);
        glEnd();
        
		//inside of the outer circle (space between spokes)
        glNormal3f(spokeRad*cos(ang+angSmooth/2 + 135),spokeRad*sin(ang+angSmooth/2 + 135),0);
        glBegin(GL_POLYGON);
        glVertex3f(spokeRad*cos(ang),spokeRad*sin(ang),z);
        glVertex3f(spokeRad*cos(ang+angSmooth),spokeRad*sin(ang+angSmooth),z);
        glVertex3f(spokeRad*cos(ang+angSmooth),spokeRad*sin(ang+angSmooth),-z);
        glVertex3f(spokeRad*cos(ang),spokeRad*sin(ang),-z);
        glEnd();
        
		//outside of the inner circle (space between spokes)
        glNormal3f(smallRad*cos(ang+angSmooth/2),smallRad*sin(ang+angSmooth/2),0);
        glBegin(GL_POLYGON);
        glVertex3f(smallRad*cos(ang),smallRad*sin(ang),z);
        glVertex3f(smallRad*cos(ang+angSmooth),smallRad*sin(ang+angSmooth),z);
        glVertex3f(smallRad*cos(ang+angSmooth),smallRad*sin(ang+angSmooth),-z);
        glVertex3f(smallRad*cos(ang),smallRad*sin(ang),-z);
        glEnd();
        
        ang += angSmooth;
    }
    
    // end of tooth
    ang = 0;
    drawTooth = false;
    for (int i = 0; i < numTeeth; i++) {
        drawTooth = !drawTooth;
        if (drawTooth) {
            glNormal3f(toothRad*cos(ang+angInc/2),toothRad*sin(ang+angInc/2),0);
            glBegin(GL_POLYGON);
            glVertex3f(toothRad*cos(ang + (angInc / 4)),toothRad*sin(ang + (angInc / 4)),-0.05);
            glVertex3f(toothRad*cos(ang + (3 * angInc / 4)),toothRad*sin(ang + (3 * angInc / 4)),-0.05);
            glVertex3f(toothRad*cos(ang + (3 * angInc / 4)),toothRad*sin(ang + (3 * angInc / 4)),0.05);
            glVertex3f(toothRad*cos(ang + (angInc / 4)),toothRad*sin(ang + (angInc / 4)),0.05);
            glEnd();
        }
        ang += angInc;
    }
    
	//end of tooth (small gear teeth on the inside)
    ang = 0;
    drawTooth = false;
    for (int i = 0; i < smallTeeth; i++) {
        drawTooth = !drawTooth;
        if (drawTooth) {
            glNormal3f(innerTeethPointRad*cos(ang+smallToothAngInc/2 + 135),innerTeethPointRad*sin(ang+smallToothAngInc/2 + 135),0);
            glBegin(GL_POLYGON);
            glVertex3f(innerTeethPointRad*cos(ang + (smallToothAngInc / 4)),innerTeethPointRad*sin(ang + (smallToothAngInc / 4)),-0.05);
            glVertex3f(innerTeethPointRad*cos(ang + (3 * smallToothAngInc / 4)),innerTeethPointRad*sin(ang + (3 * smallToothAngInc / 4)),-0.05);
            glVertex3f(innerTeethPointRad*cos(ang + (3 * smallToothAngInc / 4)),innerTeethPointRad*sin(ang + (3 * smallToothAngInc / 4)),0.05);
            glVertex3f(innerTeethPointRad*cos(ang + (smallToothAngInc / 4)),innerTeethPointRad*sin(ang + (smallToothAngInc / 4)),0.05);
            glEnd();
        }
        ang += smallToothAngInc;
    }
    
    
    // inside wall of teeth, straight portion
    ang = 0;
    drawTooth = false;
    for (int i = 0; i < numTeeth; i++) {
        drawTooth = !drawTooth;
        if (drawTooth) {
            float nx,ny,nz;
            
            calcNormal( rad*cos(ang),   rad*sin(ang),-z,
            outRad*cos(ang),outRad*sin(ang),-z,
            outRad*cos(ang),outRad*sin(ang),z,
            &nx,&ny,&nz);
            
            glNormal3f(nx,ny,nz);
            glBegin(GL_POLYGON);
            glVertex3f(   rad*cos(ang),   rad*sin(ang),-z);
            glVertex3f(outRad*cos(ang),outRad*sin(ang),-z);
            glVertex3f(outRad*cos(ang),outRad*sin(ang),z);
            glVertex3f(   rad*cos(ang),   rad*sin(ang),z);
            glEnd();
            
            
            calcNormal( rad*cos(ang+angInc),   rad*sin(ang+angInc),-z,
            outRad*cos(ang+angInc),outRad*sin(ang+angInc),z,
            outRad*cos(ang+angInc),outRad*sin(ang+angInc),-z,
            &nx,&ny,&nz);
            
            glNormal3f(nx,ny,nz);
            
            glBegin(GL_POLYGON);
            glVertex3f(   rad*cos(ang+angInc),   rad*sin(ang+angInc),-z);
            glVertex3f(outRad*cos(ang+angInc),outRad*sin(ang+angInc),-z);
            glVertex3f(outRad*cos(ang+angInc),outRad*sin(ang+angInc),z);
            glVertex3f(   rad*cos(ang+angInc),   rad*sin(ang+angInc),z);
            glEnd();
            
        }
        ang += angInc;
    }
    
    // inside wall of teeth, pointed portion
    ang = 0;
    drawTooth = false;
    for (int i = 0; i < numTeeth; i++) {
        drawTooth = !drawTooth;
        if (drawTooth) {
            float nx,ny,nz;
            
            calcNormal( outRad*cos(ang),   outRad*sin(ang),-z,
            toothRad*cos(ang),toothRad*sin(ang),-z,
            toothRad*cos(ang),toothRad*sin(ang),z,
            &nx,&ny,&nz);
            
            glNormal3f(nx,ny,nz);
            glBegin(GL_POLYGON);
            glVertex3f(   outRad*cos(ang),   outRad*sin(ang),-z);
            glVertex3f(toothRad*cos(ang + (angInc / 4)),toothRad*sin(ang + (angInc / 4)),-(z/2));
            glVertex3f(toothRad*cos(ang + (angInc / 4)),toothRad*sin(ang + (angInc / 4)),(z/2));
            glVertex3f(   outRad*cos(ang),   outRad*sin(ang),z);
            glEnd();
            
            
            calcNormal( outRad*cos(ang+angInc),   outRad*sin(ang+angInc),-z,
            toothRad*cos(ang+angInc),toothRad*sin(ang+angInc),z,
            toothRad*cos(ang+angInc),toothRad*sin(ang+angInc),-z,
            &nx,&ny,&nz);
            
            glNormal3f(nx,ny,nz);
            
            glBegin(GL_POLYGON);
            glVertex3f(   outRad*cos(ang+angInc),   outRad*sin(ang+angInc),-z);
            glVertex3f(toothRad*cos(ang+ ( 3 * angInc / 4)),toothRad*sin(ang+( 3 * angInc / 4)),-(z/2));
            glVertex3f(toothRad*cos(ang+( 3 * angInc / 4)),toothRad*sin(ang+( 3 * angInc / 4)),(z/2));
            glVertex3f(   outRad*cos(ang+angInc),   outRad*sin(ang+angInc),z);
            glEnd();
            
        }
        ang += angInc;
    }
    
    // inside wall of inner teeth
    ang = 0;
    drawTooth = false;
    for (int i = 0; i < smallTeeth; i++) {
        drawTooth = !drawTooth;
        if (drawTooth) {
            float nx,ny,nz;
            
            calcNormal( innerTeethRad*cos(ang + 90),   innerTeethRad*sin(ang+ 90),-z,
            innerTeethPointRad*cos(ang+ 90),innerTeethPointRad*sin(ang+ 90),-z,
            innerTeethPointRad*cos(ang+ 90),innerTeethPointRad*sin(ang+ 90),z,
            &nx,&ny,&nz);
            
            glNormal3f(nx,ny,nz);
            glBegin(GL_POLYGON);
            glVertex3f(   innerTeethRad*cos(ang),   innerTeethRad*sin(ang),-z);
            glVertex3f(innerTeethPointRad*cos(ang + (smallToothAngInc / 4)),innerTeethPointRad*sin(ang + (smallToothAngInc / 4)),-(z/2));
            glVertex3f(innerTeethPointRad*cos(ang + (smallToothAngInc / 4)),innerTeethPointRad*sin(ang + (smallToothAngInc / 4)),(z/2));
            glVertex3f(   innerTeethRad*cos(ang),   innerTeethRad*sin(ang),z);
            glEnd();
            
            
            calcNormal( innerTeethRad*cos(ang+smallToothAngInc  - 90),   innerTeethRad*sin(ang+smallToothAngInc - 90),-z,
            innerTeethPointRad*cos(ang+smallToothAngInc - 90),innerTeethPointRad*sin(ang+smallToothAngInc - 90),z,
            innerTeethPointRad*cos(ang+smallToothAngInc - 90),innerTeethPointRad*sin(ang+smallToothAngInc - 90),-z,
            &nx,&ny,&nz);
            
            glNormal3f(nx,ny,nz);
            
            glBegin(GL_POLYGON);
            glVertex3f(   innerTeethRad*cos(ang+smallToothAngInc),   innerTeethRad*sin(ang+smallToothAngInc),-z);
            glVertex3f(innerTeethPointRad*cos(ang+ ( 3 * smallToothAngInc / 4)),innerTeethPointRad*sin(ang+( 3 * smallToothAngInc / 4)),-(z/2));
            glVertex3f(innerTeethPointRad*cos(ang+( 3 * smallToothAngInc / 4)),innerTeethPointRad*sin(ang+( 3 * smallToothAngInc / 4)),(z/2));
            glVertex3f(   innerTeethRad*cos(ang+smallToothAngInc),   innerTeethRad*sin(ang+smallToothAngInc),z);
            glEnd();
            
        }
        ang += smallToothAngInc;
    }
    
    
}