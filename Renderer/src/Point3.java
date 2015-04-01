/**
 * 3D point
 */
public class Point3 {
	float x;
	float y;
	float z;
	
	public Point3(final float the_x, final float the_y, final float the_z) {
		x = the_x;
		y = the_y;
		z = the_z;
	}
	
	public void matrixPointMultiply(final Matrix m) {
		Matrix pointMatrix = new Matrix(4, 1);
		pointMatrix.data[0][0] = x;
		pointMatrix.data[1][0] = y;
		pointMatrix.data[2][0] = z;
		pointMatrix.data[3][0] = 1;
		Matrix transform = Matrix.matrixMultiply(m, pointMatrix);
		x = transform.data[0][0] / transform.data[3][0];
		y = transform.data[1][0] / transform.data[3][0];
		z = transform.data[2][0] / transform.data[3][0];
	}
	
	public Point3 transformPoint(final Matrix transformationMatrix) {
		Point3 new_point = new Point3(x, y, z);
		new_point.matrixPointMultiply(transformationMatrix);
		return new_point;
	}
	
//	public static void main(String[] args) {
//		Point3 p = new Point3(1, 2, 3);
//		float[][] f = {{(float).5, (float).6, (float).7, (float).8},
//				{(float).1, (float).2, (float).3, (float).4},
//				{(float).5, (float).5, (float).5, (float).5},
//				{0, 0, 0, 1}};
//		p.matrixPointMultiply(new Matrix(f));
//		System.out.println(p);
//	}

	@Override
	public String toString() {
		return "Point3 [x=" + x + ", y=" + y + ", z=" + z + "]";
	}
}
