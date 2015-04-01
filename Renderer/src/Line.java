import java.awt.Color;

/**
 * 3D line
 */
public class Line extends AbstractShape {
	
	private Point3[] points;
	
	private Matrix m;
	
	private Color c;
	
	public Line(float start_x, float start_y, float start_z, float end_x, float end_y, float end_z, 
			final Matrix ctm, final Color new_color) {
		points = new Point3[2];
		points[0] = new Point3(start_x, start_y, start_z);
		points[1] = new Point3(end_x, end_y, end_z);
		m = ctm;
		c = new_color;
		transform();
	}
	
//	public Matrix[] getTransformedPoints(final float keyRotateX, final float keyRotateY) {
//		Matrix transMatrix = new Matrix(4,4);
//		transMatrix.rotateX(keyRotateX);
//		transMatrix.rotateY(keyRotateY);
//		
//		Matrix[] matrices = new Matrix[points.length];
//		for (int i = 0; i < points.length; i++) {
//			float[][] f = {{points[i].x},{points[i].y},{points[i].z},{1}};
//			matrices[i] = (Matrix.matrixMultiply(m, new Matrix(f)));
//			matrices[i] = Matrix.matrixMultiply(transMatrix, matrices[i]);
//		}
//		
//		return matrices;
//	}
	
	private void transform() {
		for (int i = 0; i < points.length; i++) {
			points[i].matrixPointMultiply(m);
		}
	}
	
	public Color getColor() {
		return c;
	}

	@Override
	public Point3[] getPoints() {
		return points;
	}
}
