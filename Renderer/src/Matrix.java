/**
 * Row-major matrix
 * @author Jared Helm
 *
 */
public class Matrix {
	float[][] data;

	/**
	 * Creates a new matrix with given rows and columns. If it is n x n then it is the identity.
	 * 
	 * @param rows
	 * @param columns
	 */
	public Matrix(final int rows, final int columns) {
		if (rows < 1 || columns < 1) {
			throw new IllegalArgumentException("Too few rows or columns.");
		}
		data = new float[rows][columns];
		if (rows == columns) {
			this.loadIdentity();
		}
	}
	
	public Matrix(final float[][] the_data) {
		data = the_data;
	}
	
	/**
	 * Fill the matrix with the identity Matrix.
	 */
	public void loadIdentity() {
		if (data.length != data[0].length) {
			throw new IllegalStateException("This is not an n x n matrix.");
		}
		for (int i = 0; i < data.length; i++) {
			for (int j = 0; j < data[0].length; j++) {
				if (i == j) {
					data[i][j] = 1;
				} else {
					data[i][j] = 0;
				}
			}
		}
	}
	
	public static Matrix matrixCopy(final Matrix the_matrix) {
		float[][] f = new float[the_matrix.data.length][the_matrix.data[0].length];
		for (int i = 0; i < the_matrix.data.length; i++) {
			for (int j = 0; j < the_matrix.data[0].length; j++) {
				f[i][j] = the_matrix.data[i][j];
			}
		}
		return new Matrix(f);
	}
	
	/**
	 * Multiplies two matrices.
	 * 
	 * @param m1 Left Matrix
	 * @param m2 Right Matrix
	 * @return The result of the multiply.
	 */
	public static Matrix matrixMultiply(final Matrix m1, final Matrix m2) {
		Matrix new_matrix = new Matrix(m1.data.length, m2.data[0].length);
		
		if (m1.data[0].length != m2.data.length) {
			throw new IllegalArgumentException("Cannot multiply a " + m1.data.length + " x " + m1.data[0].length +
					" matrix by a " + m2.data.length + " x " + m2.data[0].length + " matrix.");
		}
		
		for (int row = 0; row < new_matrix.data.length; row++) {
			for (int col = 0; col < new_matrix.data[0].length; col++) {
				float total = 0;
				for (int k = 0; k < m1.data[0].length; k++) {
					total += m1.data[row][k] * m2.data[k][col];
				}
				new_matrix.data[row][col] = total;
			}
		}
		return new_matrix;
	}
	
	/**
	 * Creates a matrix that creates a new axis system based on the location of the camera,
	 * what the camera is pointing at, and which direction is up.
	 * 
	 * @param eye
	 * @param at
	 * @param up
	 * @return
	 */
	public static Matrix lookAt(final Point3 eye, final Point3 at, final Vector up) {
		Matrix lookAt_matrix;
		Vector n = Vector.subtractPoint(eye, at);
		n.normalize();
		Vector u = Vector.crossProduct(up, n);
		u.normalize();
		Vector v = Vector.crossProduct(n, u);
		v.normalize();
		float[][] f = {{u.data[0], u.data[1], u.data[2], 0},
				{v.data[0], v.data[1], v.data[2], 0},
				{n.data[0], n.data[1], n.data[2], 0},
				{0, 0, 0, 1}};
		lookAt_matrix = new Matrix(f);
		Matrix translate = new Matrix(4, 4);
		translate.translate(-eye.x, -eye.y, -eye.z);
		
		return Matrix.matrixMultiply(lookAt_matrix, translate);
	}
	
	public static Matrix projectFrustum(final float left, final float right, 
			final float bottom, final float top, 
			final float near, final float far) {
		float[][] f = {{(2 * near) / (right - left), 0, (right + left) / (right - left), 0},
				{0, (2 * near) / (top - bottom), (top + bottom) / (top - bottom), 0},
				{0, 0, -(far + near) / (far - near), -(2 * far * near) / (far - near)},
				{0, 0, -1, 0}};
		Matrix projectionMatrix = new Matrix(f);
		
		return projectionMatrix;
	}
	
	public static Matrix projectOrtho(final float left, final float right, 
			final float bottom, final float top, 
			final float near, final float far) {
		float[][] f = {{2 / (right - left), 0, 0, (right + left) / (right - left)},
				{0, 2 / (top - bottom), 0, (top + bottom) / (top - bottom)},
				{0, 0, -2 / (far - near), (far + near) / (far - near)},
				{0, 0, 0, 1}};
		Matrix projectionMatrix = new Matrix(f);
		
		return projectionMatrix;
	}
	
	
	/**
	 * Creates a string representaion of a matrix.
	 */
	public String toString() {
		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < data.length; i++) {
			for (int j = 0; j < data[0].length; j++) {
				sb.append(data[i][j]);
				sb.append(" ");
			}
			sb.append(System.lineSeparator());
		}
		return sb.toString();
	}
	
	/**
	 * Adds a translate effect to the tranformation matrix.
	 * @param translate_x
	 * @param translate_y
	 * @param translate_z
	 */
	public void translate (final float translate_x, final float translate_y, final float translate_z) {
		if (data.length != 4 && data[0].length != 4) {
			throw new IllegalArgumentException("Left matrix is not 4 x 4");
		}
		Matrix translate_matrix = new Matrix(new float[4][4]);
		
		translate_matrix.loadIdentity();
		translate_matrix.data[0][3] = translate_x;
		translate_matrix.data[1][3] = translate_y;
		translate_matrix.data[2][3] = translate_z;
		
		data = matrixMultiply(translate_matrix, this).data;
	}
	
	/**
	 * Adds a scale effect to the transformation matrix.
	 * @param scale_x
	 * @param scale_y
	 * @param scale_z
	 */
	public void scale(final float scale_x, final float scale_y, final float scale_z) {
		if (data.length != 4 && data[0].length != 4) {
			throw new IllegalArgumentException("Left matrix is not 4 x 4");
		}
		Matrix scale_matrix = new Matrix(new float[4][4]);
		
		scale_matrix.loadIdentity();
		scale_matrix.data[0][0] = scale_x;
		scale_matrix.data[1][1] = scale_y;
		scale_matrix.data[2][2] = scale_z;
		
		data = matrixMultiply(scale_matrix, this).data;
	}
	
	/**
	 * Adds a rotate effect to the tranformation matrix.
	 * 
	 * @param degrees
	 */
	public void rotateX(final float degrees) {
		if (data.length != 4 && data[0].length != 4) {
			throw new IllegalArgumentException("Left matrix is not 4 x 4");
		}
		Matrix rotate_matrix = new Matrix(new float[4][4]);
		
		rotate_matrix.loadIdentity();
		rotate_matrix.data[1][1] = (float) Math.cos(Math.toRadians(degrees));
		rotate_matrix.data[1][2] = -1 * (float) Math.sin(Math.toRadians(degrees));
		rotate_matrix.data[2][1] = (float) Math.sin(Math.toRadians(degrees));
		rotate_matrix.data[2][2] = (float) Math.cos(Math.toRadians(degrees));
		
		data = matrixMultiply(rotate_matrix, this).data;
	}
	
	/**
	 * Adds a rotate effect to the tranformation matrix.
	 * 
	 * @param degrees
	 */
	public void rotateY(final float degrees) {
		if (data.length != 4 && data[0].length != 4) {
			throw new IllegalArgumentException("Left matrix is not 4 x 4");
		}
		Matrix rotate_matrix = new Matrix(new float[4][4]);
		
		rotate_matrix.loadIdentity();
		rotate_matrix.data[0][0] = (float) Math.cos(Math.toRadians(degrees));
		rotate_matrix.data[0][2] = (float) Math.sin(Math.toRadians(degrees));
		rotate_matrix.data[2][0] = -1 * (float) Math.sin(Math.toRadians(degrees));
		rotate_matrix.data[2][2] = (float) Math.cos(Math.toRadians(degrees));
		
		data = matrixMultiply(rotate_matrix, this).data;
	}
	
	/**
	 * Adds a rotate effect to the tranformation matrix.
	 * 
	 * @param degrees
	 */
	public void rotateZ(final float degrees) {
		if (data.length != 4 && data[0].length != 4) {
			throw new IllegalArgumentException("Left matrix is not 4 x 4");
		}
		Matrix rotate_matrix = new Matrix(new float[4][4]);
		
		rotate_matrix.loadIdentity();
		rotate_matrix.data[0][0] = (float) Math.cos(Math.toRadians(degrees));
		rotate_matrix.data[0][1] = -1 * (float) Math.sin(Math.toRadians(degrees));
		rotate_matrix.data[1][0] = (float) Math.sin(Math.toRadians(degrees));
		rotate_matrix.data[1][1] = (float) Math.cos(Math.toRadians(degrees));
		
		data = matrixMultiply(rotate_matrix, this).data;
	}
	
	public static void main(String args[]) {
		float right = 1;
		float left = -4;
		float top = 6;
		float bottom = -7;
		float near = 9;
		float far = 11;
		
		Matrix proj = Matrix.projectFrustum(left, right, bottom, top, near, far);
		System.out.println(proj);
	}
}




















