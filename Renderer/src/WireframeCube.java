import java.awt.Color;


public class WireframeCube extends AbstractShape {
	
	private Point3[] points;
	
	private Matrix m;
	
	private Color c;
	
	boolean solid;
	
	public WireframeCube(final Matrix transformation, final Color new_color, final boolean solidFlag) {
		points = new Point3[8];
		m = Matrix.matrixCopy(transformation);
		c = new_color;
		solid = solidFlag;
		points[0] = new Point3((float)-.5, (float).5, (float).5);
		points[1] = new Point3((float).5, (float).5, (float).5);
		points[2] = new Point3((float).5, (float)-.5, (float).5);
		points[3] = new Point3((float)-.5, (float)-.5, (float).5);
		points[4] = new Point3((float)-.5, (float).5, (float)-.5);
		points[5] = new Point3((float).5, (float).5, (float)-.5);
		points[6] = new Point3((float).5, (float)-.5, (float)-.5);
		points[7] = new Point3((float)-.5, (float)-.5, (float)-.5);
				
		transform();
	}
	
	public Matrix[] getTransformedPoints(final float keyRotateX, final float keyRotateY) {
		Matrix transMatrix = new Matrix(4,4);
		transMatrix.rotateX(keyRotateX);
		transMatrix.rotateY(keyRotateY);
		
		Matrix[] matrices = new Matrix[points.length];
		for (int i = 0; i < points.length; i++) {
			float[][] f = {{points[i].x},{points[i].y},{points[i].z},{1}};
			matrices[i] = (Matrix.matrixMultiply(m, new Matrix(f)));
			matrices[i] = Matrix.matrixMultiply(transMatrix, matrices[i]);
		}
		
		return matrices;
	}
	
	private void transform() {
		for (int i = 0; i < points.length; i++) {
			this.points[i].matrixPointMultiply(m);
		}
	}
	
	public Color getColor() {
		return c;
	}

	@Override
	public Point3[] getPoints() {
		return points;
	}
	
	public boolean isSolid() {
		return solid;
	}
}
