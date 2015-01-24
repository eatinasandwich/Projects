void auggGear(int numTeeth, int numSpokes);
void alpertGear(int numTeeth, int numSpokes, double radius);
void chenGear(int numTeeth, int numSpokes);
void helmGear(int numTeeth, int numSpokes, int mode);
void colemanGear(int numTeeth, int numSpokes);
void calcNormal(float x1, float y1, float z1,
	float x2, float y2, float z2,
	float x3, float y3, float z3,
	float* nx, float* ny, float* nz);
void normalize(float* nx, float* ny, float* nz);
