
public class Vector {
	float[] data = {0, 0, 0, 0};
	
	public Vector(final float x, final float y, final float z, final float w) {
		data[0] = x;
		data[1] = y;
		data[2] = z;
		data[3] = w;
	}
	
	public Vector() {
		//do nothing
	}
	
	public Matrix toMatrix() {
		Matrix new_matrix = new Matrix(4, 1);
		for (int i = 0; i < data.length; i++) {
			new_matrix.data[i][0] = data[i];
		}
		
		return new_matrix;
	}
	
	public void normalize() {
		float divisor = (float) Math.sqrt(data[0] * data[0] +
				data[1] * data[1] +
				data[2] * data[2]);
		data[0] = data[0] / divisor;
		data[1] = data[1] / divisor;
		data[2] = data[2] / divisor;
		data[3] = 0;
	}
	
	public static Vector crossProduct(final Vector v1, final Vector v2) {
		Vector new_vector = new Vector();
		new_vector.data[0] = v1.data[1] * v2.data[2] - v1.data[2] * v2.data[1];
		new_vector.data[1] = v1.data[2] * v2.data[0] - v1.data[0] * v2.data[2];
		new_vector.data[2] = v1.data[0] * v2.data[1] - v1.data[1] * v2.data[0];
		new_vector.data[3] = 0;
		
		return new_vector;
	}
	
	public String toString() {
		StringBuilder sb = new StringBuilder();
		sb.append("{");
		sb.append(data[0]);
		sb.append(", ");
		sb.append(data[1]);
		sb.append(", ");
		sb.append(data[2]);
		sb.append(", ");
		sb.append(data[3]);
		sb.append("}");
		sb.append(System.lineSeparator());
		
		return sb.toString();
	}
	
	public static Vector subtractPoint(final Point3 p1, final Point3 p2) {
		return new Vector(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z, 0);
	}
}

















