import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.image.BufferedImage;
import java.awt.image.WritableRaster;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

@SuppressWarnings("serial")
public class TCSS458Paint extends JPanel implements KeyListener
{
    int width;
    int height;
    int imageSize;
    int[] pixels;
    private Color currentColor;
    
    private Matrix CTM;
    private Matrix lookerMatrix;
    private Matrix projectionMatrix;
    
    private boolean frustum;
    private boolean volumeIsSet;
    private boolean hsr = true;
    
    private ArrayList<AbstractShape> shapes;
    
    private float keyRotateXDegrees = 0;
    private float keyRotateYDegrees = 0;
    
    private float[][] zBuffer;
    private Range[] scans;
    private ViewVolume vv;
    
    void drawPixel(int x, int y, int r, int g, int b) {
    	try {
        pixels[(height-y-1)*width*3+x*3] = r;
        pixels[(height-y-1)*width*3+x*3+1] = g;
        pixels[(height-y-1)*width*3+x*3+2] = b;
    	} catch (ArrayIndexOutOfBoundsException e) {
    		
    	}
    }
    
    void drawPixel(final int x, final int y, final float z) {
    	if (z > zBuffer[x][y]) {
    		zBuffer[x][y] = z;
    		drawPixel(x, y, currentColor.getRed(), currentColor.getGreen(), currentColor.getBlue());
    	}
    }
    
    /**
     * Parses the input file and constructs the image.
     */
    void createImage() {
    	CTM = new Matrix(4, 4);
    	lookerMatrix = new Matrix(4, 4);
    	projectionMatrix = new Matrix(4, 4);
    	vv = new ViewVolume(-1, 1, -1, 1, -1, 1);
    	frustum = false;
    	volumeIsSet = false;
    	currentColor = Color.WHITE;
    	
    	Scanner input = getInputFile();
    	try {
    		String dim = input.nextLine();
    		Scanner lineScanner = new Scanner(dim);
    		
    		if (!lineScanner.next().equals("DIM")) {
    			lineScanner.close();
    			throw new IllegalArgumentException();
    		} else {
    			width = lineScanner.nextInt() - 1;
    			height = lineScanner.nextInt() - 1;
    			imageSize = width * height;
    			pixels = new int[imageSize * 3];
    			zBuffer = new float[width][height];
    		}
    		
	    	while (input.hasNextLine()) {
	    		String paintThis = input.nextLine();
	    		lineScanner = new Scanner(paintThis);
	    		String myShape = lineScanner.next();
	    		myShape = myShape.toUpperCase();
	    		if (myShape.equals("RGB")) {
	    			currentColor = new Color(
	    					Float.parseFloat(lineScanner.next()), Float.parseFloat(lineScanner.next()), 
	    					Float.parseFloat(lineScanner.next()));
	    		} else if (myShape.equals("LINE")) {
	    			shapes.add(new Line(Float.parseFloat(lineScanner.next()), Float.parseFloat(lineScanner.next()),
	    					Float.parseFloat(lineScanner.next()), Float.parseFloat(lineScanner.next()),
	    					Float.parseFloat(lineScanner.next()), Float.parseFloat(lineScanner.next()), CTM, currentColor));
	    		} else if (myShape.equals("TRI")) {
	    			shapes.add(new Triangle(Float.parseFloat(lineScanner.next()), Float.parseFloat(lineScanner.next()),
	    					Float.parseFloat(lineScanner.next()), Float.parseFloat(lineScanner.next()),
	    					Float.parseFloat(lineScanner.next()), Float.parseFloat(lineScanner.next()),
	    					Float.parseFloat(lineScanner.next()), Float.parseFloat(lineScanner.next()),
	    					Float.parseFloat(lineScanner.next()), CTM, currentColor));
	    		} else if (myShape.equals("WIREFRAME_CUBE")) {
	    			shapes.add(new WireframeCube(CTM, currentColor, false));
	    		} else if (myShape.equals("SOLID_CUBE")) {
	    			shapes.add(new WireframeCube(CTM, currentColor, true));
	    		} else if (myShape.equals("LOAD_IDENTITY_MATRIX")) {
	    			CTM = new Matrix(4, 4);
	    			CTM.loadIdentity();
	    		} else if (myShape.equals("ROTATEX")) {
	    			CTM.rotateX(Float.parseFloat(lineScanner.next()));
	    		} else if (myShape.equals("ROTATEY")) {
	    			CTM.rotateY(Float.parseFloat(lineScanner.next()));
	    		} else if (myShape.equals("ROTATEZ")) {
	    			CTM.rotateZ(Float.parseFloat(lineScanner.next()));
	    		} else if (myShape.equals("SCALE")) {
	    			CTM.scale(Float.parseFloat(lineScanner.next()), Float.parseFloat(lineScanner.next()), 
	    					Float.parseFloat(lineScanner.next()));
	    		} else if (myShape.equals("TRANSLATE")) {
	    			CTM.translate(Float.parseFloat(lineScanner.next()), Float.parseFloat(lineScanner.next()), 
	    					Float.parseFloat(lineScanner.next()));
	    		} else if (myShape.equals("FRUSTUM")) {
	    			frustum = true;
	    			volumeIsSet = true;
	    			vv = new ViewVolume(Float.parseFloat(lineScanner.next()), Float.parseFloat(lineScanner.next()),
	    					Float.parseFloat(lineScanner.next()), Float.parseFloat(lineScanner.next()),
	    					Float.parseFloat(lineScanner.next()), Float.parseFloat(lineScanner.next()));
	    		} else if (myShape.equals("ORTHO")) {
	    			frustum = false;
	    			volumeIsSet = true;
	    			vv = new ViewVolume(Float.parseFloat(lineScanner.next()), Float.parseFloat(lineScanner.next()),
	    					Float.parseFloat(lineScanner.next()), Float.parseFloat(lineScanner.next()),
	    					Float.parseFloat(lineScanner.next()), Float.parseFloat(lineScanner.next()));
	    		} else if (myShape.equals("LOOKAT")) {
	    			lookerMatrix = Matrix.lookAt(new Point3(Float.parseFloat(lineScanner.next()), Float.parseFloat(lineScanner.next()), Float.parseFloat(lineScanner.next())), 
	    					new Point3(Float.parseFloat(lineScanner.next()), Float.parseFloat(lineScanner.next()), Float.parseFloat(lineScanner.next())), 
	    	    			new Vector(Float.parseFloat(lineScanner.next()), Float.parseFloat(lineScanner.next()), Float.parseFloat(lineScanner.next()), 0));
	    		} else {
	    			lineScanner.close();
	    			throw new IllegalArgumentException();
	    		}
	    	}
	    	lineScanner.close();
    	} catch (IllegalArgumentException e) {
    		System.err.println("Input file is not properly formatted.");
    		return;
    	}
    	
//    	rasterizeShapes(shapes);
    	input.close();
    }
    
    public void rasterizeShapes(final ArrayList<AbstractShape> the_shapes) {
    	whiteOut();
//    	System.out.println("x rotate: " + keyRotateXDegrees + "   y rotate: " + keyRotateYDegrees);
    	for (int i = 0; i < the_shapes.size(); i++) {
    		AbstractShape s = the_shapes.get(i);
    		Point3[] shape_points = s.getPoints();
    		Point3[] new_points = new Point3[shape_points.length];
    		Matrix keyRotateMatrix = new Matrix(4, 4);
    		keyRotateMatrix.rotateX(keyRotateXDegrees);
    		keyRotateMatrix.rotateY(keyRotateYDegrees);
    		
    		if (volumeIsSet) {
	    		if (frustum) {
	    			projectionMatrix = Matrix.projectFrustum(vv.left, vv.right, vv.bottom, vv.top, vv.near, vv.far);
	    		} else {
	    			projectionMatrix = Matrix.projectOrtho(vv.left, vv.right, vv.bottom, vv.top, vv.near, vv.far);
	    		}
    		}
    		for (int j = 0; j < shape_points.length; j++) {
    			new_points[j] = shape_points[j].transformPoint(keyRotateMatrix);
    			new_points[j] = new_points[j].transformPoint(lookerMatrix);
    			new_points[j] = new_points[j].transformPoint(projectionMatrix);
    			if (frustum) {
    				new_points[j].z = new_points[j].z * -1;
    			}
    		}
	    	//draw line
	    	if (s instanceof Line) {
	    		Line l = (Line) the_shapes.get(i);
	    		Point3[] line_points = new_points;
	    		currentColor = l.getColor();
	    		if (!hsr) {
		    		drawLine((line_points[0].x + 1) * (width / 2), (line_points[0].y + 1) * (height / 2), 
		    				(line_points[1].x + 1) * (width / 2), (line_points[1].y + 1) * (height / 2), null);
	    		} else {
		    		drawLine((line_points[0].x + 1) * (width / 2), (line_points[0].y + 1) * (height / 2), line_points[0].z, 
		    				(line_points[1].x + 1) * (width / 2), (line_points[1].y + 1) * (height / 2), line_points[1].z, false);
	    		}
	    	}
	    	//draw triangle
	    	else if (s instanceof Triangle) {
	    		Triangle t = (Triangle) the_shapes.get(i);
	    		Point3[] tri_points = new_points;
	    		currentColor = t.getColor();
	    		if (!hsr) {
		    		drawTriangle(((tri_points[0].x + 1) * (width / 2)), ((tri_points[0].y + 1) * (height / 2)),
		    				((tri_points[1].x + 1) * (width / 2)), ((tri_points[1].y + 1) * (height / 2)),
		    				((tri_points[2].x + 1) * (width / 2)), ((tri_points[2].y + 1) * (height / 2)));
	    		} else {
		    		drawTriangle(((tri_points[0].x + 1) * (width / 2)), ((tri_points[0].y + 1) * (height / 2)), tri_points[0].z,
		    				((tri_points[1].x + 1) * (width / 2)), ((tri_points[1].y + 1) * (height / 2)), tri_points[1].z,
		    				((tri_points[2].x + 1) * (width / 2)), ((tri_points[2].y + 1) * (height / 2)), tri_points[2].z);
	    		}
	    	}
	    	//draw box
	    	else if (s instanceof WireframeCube) {
	    		WireframeCube c = (WireframeCube) s;
	    		if (c.isSolid()) {
	    			drawSolidCube(new_points, c.getColor());
	    		} else {
	    			drawCube(new_points, c.getColor());
	    		}
	    	}
    	}
    }
    
    private Scanner getInputFile() {
    	boolean valid = false;
    	Scanner in = new Scanner(System.in);
    	Scanner inFile = null;
    	while (!valid) {
    		int choice = JOptionPane.showConfirmDialog(null, "Would you like to view with zBuffer on? (its slightly broken)");
    		if (choice == JOptionPane.YES_OPTION) {
    			hsr = true;
    		} else {
    			hsr = false;
    		}
	    	String inputFile = JOptionPane.showInputDialog("Relinqish the name of your input file puny human!" +
	    			"\n(Or type \"choose\" for a file chooser)");
	    	try {
	    		if (inputFile.equals("choose")) {
		    		JFileChooser chooser = new JFileChooser();
		    		chooser.showOpenDialog(null);
		    		inFile = new Scanner(chooser.getSelectedFile());
		    	} else {
		    		inFile = new Scanner(new File(inputFile));
		    	}
	    		valid = true;
	    	} catch(FileNotFoundException e) {
	    		JOptionPane.showMessageDialog(null, "Your insolence is exceeded only by your ability to give me the wrong input file!");
	    	}
    	}
    	in.close();
    	return inFile;
    }
    
    private void drawLine(final float x1, final float y1, final float x2, final float y2, final int[][] minMax) {
    	Point p1 = new Point(Math.round(x1), Math.round(y1));
    	Point p2 = new Point(Math.round(x2), Math.round(y2));
    	boolean triLine = (minMax == null ? false : true);
    	
    	//switch start and end when start point is to the right of end point
    	//and when start is vertically above end
    	if (p1.x > p2.x || (p1.x == p2.x && p1.y > p2.y)) { 
    		Point temp = p1;
    		p1 = p2;
    		p2 = temp;
    	}
    	
    	int dx = p2.x - p1.x;
    	int dy = p2.y - p1.y;
    	int p, k; //p is Pk at a given point. k is Yk or Xk depending on the angle of the line.
    	int addP;
    	int subP;
    	if (dy > 1) { //0 to 45 degrees
    		if (dx >= dy) {
    			p = 2 * dy - dx;
    			k = p1.y;
    			addP = 2 * dy;
    			subP = addP - 2 * dx;
    			for (int i = p1.x; i <= p2.x; i++) {
    				drawPixel(i, k, currentColor.getRed(), currentColor.getGreen(), currentColor.getBlue());
    				if (triLine) {
    					if (k > 0) {
	    					if (i < minMax[k][0]) minMax[k][0] = i;
	    					if (i > minMax[k][1]) minMax[k][1] = i;
    					} else {
    						if (i < minMax[0][0]) minMax[0][0] = i;
	    					if (i > minMax[0][1]) minMax[0][1] = i;
    					}
    				}
    				if (p >= 0) {
    					k++;
    					p += subP;
    				} else {
    					p += addP;
    				}
    			}
    		} else { //46 to 90 degrees
    			p = 2 * dx - dy;
    			k = p1.x;
    			addP = 2 * dx;
    			subP = addP - 2 * dy;
    			for (int i = p1.y; i <= p2.y; i++) {
    				drawPixel(k, i, currentColor.getRed(), currentColor.getGreen(), currentColor.getBlue());
    				if (triLine) {
    					if (i > 0) {
	    					if (k < minMax[i][0]) minMax[i][0] = k;
	    					if (k > minMax[i][1]) minMax[i][1] = k;
    					} else {
	    					if (k < minMax[0][0]) minMax[0][0] = k;
	    					if (k > minMax[0][1]) minMax[0][1] = k;    						
    					}
    				}
    				if (p >= 0) {
    					k++;
    					p += subP;
    				} else {
    					p += addP;
    				}
    			}
    		}
    	} else { // -45 to -1 degrees
    		dy *= -1;
    		if (dx >= dy) {
    			p = 2 * dy - dx;
    			k = p1.y;
    			addP = 2 * dy;
    			subP = addP - 2 * dx;
    			for (int i = p1.x; i <= p2.x; i++) {
    				drawPixel(i, k, currentColor.getRed(), currentColor.getGreen(), currentColor.getBlue());
    				if (triLine) {
    					if (k > 0) {
    						if (i < minMax[k][0]) minMax[k][0] = i;
    						if (i > minMax[k][1]) minMax[k][1] = i;
    					} else {
    						if (i < minMax[0][0]) minMax[0][0] = i;
    						if (i > minMax[0][1]) minMax[0][1] = i;
    					}
    				}
    				if (p >= 0) {
    					k--;
    					p += subP;
    				} else {
    					p += addP;
    				}
    			}
    		} else { //-46 to -89 degrees
    			p = 2 * dx - dy;
    			k = p1.x;
    			addP = 2 * dx;
    			subP = addP - 2 * dy;
    			for (int i = p1.y; i >= p2.y; i--) {
    				drawPixel(k, i, currentColor.getRed(), currentColor.getGreen(), currentColor.getBlue());
    				if (triLine) {
    					if (i > 0) {
	    					if (k < minMax[i][0]) minMax[i][0] = k;
	    					if (k > minMax[i][1]) minMax[i][1] = k;
    					} else {
    						if (k < minMax[0][0]) minMax[0][0] = k;
	    					if (k > minMax[0][1]) minMax[0][1] = k;
    					}
    				}
    				if (p >= 0) {
    					k++;
    					p += subP;
    				} else {
    					p += addP;
    				}
    			}
    		}
    	}
    }
    
    
    /**
     * Draws a line given the coordinates if triangle = false and
     * it just keeps the coordinates of where each pixel would be drawn when
     * triangle = true (in this case it doesn't draw the pixels, just keeps track
     * of their locations).
     * 
     * @param x1 X coordinate of the first point.
     * @param y1 Y coordinate of the first point.
     * @param x2 X coordinate of the second point.
     * @param y2 Y coordinate of the second point.
     * @param triangle Decides whether the method should draw the pixels (false) or just
     * 				   keep track of them (true);
     */
    private void drawLine(float sx1, float sy1, float sz1, float sx2, float sy2, float sz2, boolean triangle) {
    	float slope, zSlope;
    	
    	int x1 = Math.round(sx1);
    	int y1 = Math.round(sy1);
    	int x2 = Math.round(sx2);
    	int y2 = Math.round(sy2);
    	
    	// avoids division by 0 and sets appropriate slope value
		if (x2 - x1 == 0) {
			slope = Float.MAX_VALUE;
		} else {
			slope = (float) (y2 - y1) / (x2 - x1); 
		}
		
		
		int start, end;
		if (slope >= -1 && slope <= 1) {
			float y, z;
			
			// choose start and end points
			if (x1 < x2) {
				start = x1;
				end = x2;
				y = y1;
				zSlope = (sz2 - sz1) / Math.abs(x2 - x1);
				z = sz1;
			} else {
				start = x2;
				end = x1;
				y = y2;
				zSlope = (sz1 - sz2) / Math.abs(x2 - x1);
				z = sz2;
			}
			
			for(int x = start; x <= end; x++) {
				int newY = Math.round(y);
				if (newY < 0 || newY >= height) continue;
				
				if (newY >= height) {
					newY = height - 1;
				}
				
				if (triangle) {
					// just keep track of where pixels would be placed
//					System.out.println(x + " " + y + " " + z + " " + currentColor.getGreen());
					if (scans[newY] == null) {
						scans[newY] = new Range(x,x);
					} else {
						if (scans[newY].min > x) {
							scans[newY].min = x;
							scans[newY].minZ = z;
						} else if (scans[newY].max < x) {
							scans[newY].max = x;
							scans[newY].maxZ = z;
						}
						
					}
				} else {
//					drawPixel(x, newY, currentColor.getRed(), currentColor.getGreen(), currentColor.getBlue());
					drawPixel(x, Math.round(y), z);
				}
				y += slope;
				z += zSlope;
			}
		} else if (slope > 1  || slope < -1) {
			
			float x, z;
			// choose start and end points
			if (y1 < y2) {
				start = y1;
				end = y2;
				x = x1;
				zSlope = (sz2 - sz1) / Math.abs(y2 - y1);
				z = sz1;
			} else {
				start = y2;
				end = y1;
				x = x2;
				zSlope = (sz1 - sz2) / Math.abs(y2 - y1);
				z = sz2;
			}
			
//			System.out.println("line");
			for(int y = start; y <= end; y++) {
				int newX = Math.round(x);
//				System.out.println(x + " " + y + " " + z + " " + currentColor.getGreen());
				if (triangle) {
					if (y < 0 || y >= height) continue;
					// keep track of where the pixels would be placed
					if (scans[y] == null) {
						scans[y] = new Range(newX, newX, z, z);
					} else {
						if (scans[y].min > newX) {
							scans[y].min = newX;
							scans[y].minZ = z;
						} else if (scans[y].max < newX) {
							scans[y].max = newX;
							scans[y].maxZ = z;
						}
					}
				} else {
//					drawPixel(newX, y, currentColor.getRed(), currentColor.getGreen(), currentColor.getBlue());
					drawPixel(Math.round(x), y, z);
				}
				x += 1/slope;
				z += zSlope;
			}
		} 
    }
    
    /**
     * Draws a triangle with the given coordinates.
     * 
     * @param sx0 X coordinate of the first point.
     * @param sy0 Y coordinate of the first point.
     * @param sz0 Z coordinate of the first point.
     * @param sx1 X coordinate of the second point.
     * @param sy1 Y coordinate of the second point.
     * @param sz1 Z coordinate of the second point.
     * @param sx2 X coordinate of the third point.
     * @param sy2 Y coordinate of the third point.
     * @param sz2 Z coordinate of the third point.
     */
    private void drawTriangle(float sx0, float sy0, float sz0, 
    		float sx1, float sy1, float sz1, 
    		float sx2, float sy2, float sz2) {
    	
		// initialize array to keep track of all pixel positions
    	scans = new Range[height];
    	
		drawLine(sx0, sy0, sz0, sx1, sy1, sz1, true);
		drawLine(sx0, sy0, sz0, sx2, sy2, sz2, true);
		drawLine(sx1, sy1, sz1, sx2, sy2, sz2, true);
		
		int largest_y = Math.round(Math.max(sy0, Math.max(sy1, sy2)));
		int smallest_y = Math.round(Math.min(sy0, Math.min(sy1, sy2)));
		
		for (int i = smallest_y; i <= largest_y; i++) {
			// only draw the lines that we've covered/initialized
			if (i < 0 || i >= height) continue;
			if (scans[i] != null) {
				drawLine(scans[i].min, i, scans[i].minZ, scans[i].max, i, scans[i].maxZ, false);
			}	
		}	
	}
    
    
    
    
    
    
    private void drawTriangle(final float x1, final float y1, final float x2, final float y2, final float x3, final float y3) {
    	int[][] minMax = new int[height][2];
    	for (int i = 0; i < minMax.length; i++) {
    		minMax[i][0] = width + 1;
    		minMax[i][1] = -1;
    	}
    	drawLine(x1, y1, x2, y2, minMax);
    	drawLine(x2, y2, x3, y3, minMax);
    	drawLine(x3, y3, x1, y1, minMax);
    	for (int i = 0; i < minMax.length; i++) {
    		if (minMax[i][1] == -1 || minMax[i][0] == width + 1) continue;
    		for (int j = minMax[i][0] + 1; j < minMax[i][1]; j++) {
    			drawPixel(j, i, currentColor.getRed(), currentColor.getGreen(), currentColor.getBlue());
    		}
    	}
    }
    
    private void drawCube(final Point3[] cube_points, final Color the_color) {
    	currentColor = the_color;
    	
    	drawLine((cube_points[0].x + 1) * (width / 2), (cube_points[0].y + 1) * (height / 2), 
    			(cube_points[1].x + 1) * (width / 2), (cube_points[1].y + 1) * (height / 2), null);
    	drawLine((cube_points[0].x + 1) * (width / 2), (cube_points[0].y + 1) * (height / 2), 
    			(cube_points[3].x + 1) * (width / 2), (cube_points[3].y + 1) * (height / 2), null);
    	drawLine((cube_points[0].x + 1) * (width / 2), (cube_points[0].y + 1) * (height / 2), 
    			(cube_points[4].x + 1) * (width / 2), (cube_points[4].y + 1) * (height / 2), null);
    	drawLine((cube_points[1].x + 1) * (width / 2), (cube_points[1].y + 1) * (height / 2), 
    			(cube_points[2].x + 1) * (width / 2), (cube_points[2].y + 1) * (height / 2), null);
    	drawLine((cube_points[1].x + 1) * (width / 2), (cube_points[1].y + 1) * (height / 2), 
    			(cube_points[5].x + 1) * (width / 2), (cube_points[5].y + 1) * (height / 2), null);
    	drawLine((cube_points[2].x + 1) * (width / 2), (cube_points[2].y + 1) * (height / 2), 
    			(cube_points[3].x + 1) * (width / 2), (cube_points[3].y + 1) * (height / 2), null);
    	drawLine((cube_points[2].x + 1) * (width / 2), (cube_points[2].y + 1) * (height / 2), 
    			(cube_points[6].x + 1) * (width / 2), (cube_points[6].y + 1) * (height / 2), null);
    	drawLine((cube_points[3].x + 1) * (width / 2), (cube_points[3].y + 1) * (height / 2), 
    			(cube_points[7].x + 1) * (width / 2), (cube_points[7].y + 1) * (height / 2), null);
    	drawLine((cube_points[4].x + 1) * (width / 2), (cube_points[4].y + 1) * (height / 2), 
    			(cube_points[5].x + 1) * (width / 2), (cube_points[5].y + 1) * (height / 2), null);
    	drawLine((cube_points[4].x + 1) * (width / 2), (cube_points[4].y + 1) * (height / 2), 
    			(cube_points[7].x + 1) * (width / 2), (cube_points[7].y + 1) * (height / 2), null);
    	drawLine((cube_points[5].x + 1) * (width / 2), (cube_points[5].y + 1) * (height / 2), 
    			(cube_points[6].x + 1) * (width / 2), (cube_points[6].y + 1) * (height / 2), null);
    	drawLine((cube_points[6].x + 1) * (width / 2), (cube_points[6].y + 1) * (height / 2), 
    			(cube_points[7].x + 1) * (width / 2), (cube_points[7].y + 1) * (height / 2), null);
    }
    
    private void drawSolidCube(final Point3[] cube_points, final Color the_color) {
    	currentColor = the_color;
    	drawSolidSquare(cube_points[0], cube_points[1], cube_points[2], cube_points[3]);
    	drawSolidSquare(cube_points[4], cube_points[5], cube_points[6], cube_points[7]);
    	drawSolidSquare(cube_points[0], cube_points[1], cube_points[4], cube_points[5]);
    	drawSolidSquare(cube_points[3], cube_points[2], cube_points[6], cube_points[7]);
    	drawSolidSquare(cube_points[0], cube_points[3], cube_points[7], cube_points[5]);
    	drawSolidSquare(cube_points[1], cube_points[2], cube_points[6], cube_points[5]);
    	
    }
    
    private void drawSolidSquare(final Point3 p1, final Point3 p2, final Point3 p3, final Point3 p4) {
    	if (!hsr) {
	    	drawTriangle((p1.x + 1) * (width / 2), (p1.y + 1) * (height / 2), 
	    			(p2.x + 1) * (width / 2), (p2.y + 1) * (height / 2),
	    			(p3.x + 1) * (width / 2), (p3.y + 1) * (height / 2));
	    	drawTriangle((p3.x + 1) * (width / 2), (p3.y + 1) * (height / 2),
	    			(p4.x + 1) * (width / 2), (p4.y + 1) * (height / 2),
	    			(p1.x + 1) * (width / 2), (p1.y + 1) * (height / 2));
    	} else {
	    	drawTriangle((p1.x + 1) * (width / 2), (p1.y + 1) * (height / 2), p1.z, 
	    			(p2.x + 1) * (width / 2), (p2.y + 1) * (height / 2), p2.z,
	    			(p3.x + 1) * (width / 2), (p3.y + 1) * (height / 2), p3.z);
	    	drawTriangle((p3.x + 1) * (width / 2), (p3.y + 1) * (height / 2), p3.z,
	    			(p4.x + 1) * (width / 2), (p4.y + 1) * (height / 2), p4.z,
	    			(p1.x + 1) * (width / 2), (p1.y + 1) * (height / 2), p1.z);
    	}
    }
    
    
    /**
     * Changes the background to be all white. Should only be called once.
     */
    private void whiteOut() {
    	currentColor = Color.WHITE;
    	for (int i = 0; i < pixels.length; i++) {
    		pixels[i] = currentColor.getBlue();
    	}
    	for (int i = 0; i < zBuffer.length; i++) {
    		for (int j = 0; j < zBuffer[0].length; j++) {
    			zBuffer[i][j] = -1000;
    		}
    	}
    }
    
    public void keyReleased(KeyEvent e){
        //do nothing        
    }

    public void keyPressed(KeyEvent e){
    	if (e.getKeyCode() == KeyEvent.VK_UP) {
            keyRotateXDegrees += 2;
        } else if (e.getKeyCode() == KeyEvent.VK_DOWN) {
        	keyRotateXDegrees -= 2;
        } else if (e.getKeyCode() == KeyEvent.VK_LEFT) {
        	keyRotateYDegrees += 2;
        } else if (e.getKeyCode() == KeyEvent.VK_RIGHT) {  
        	keyRotateYDegrees -= 2;
        } else if (e.getKeyCode() == KeyEvent.VK_O) {
        	frustum = false;
        } else if (e.getKeyCode() == KeyEvent.VK_P) {
        	frustum = true;
        } else if (e.getKeyCode() == KeyEvent.VK_L) {
        	if (!e.isShiftDown()) {
        		vv.left -= (float) .1 * (vv.right - vv.left);
        	} else {
        		vv.left += (float) .1 * (vv.right - vv.left);
        	}
        } else if (e.getKeyCode() == KeyEvent.VK_R) {
        	if (!e.isShiftDown()) {
        		vv.right += (float) .1 * (vv.right - vv.left);
        	} else {
        		vv.right -= (float) .1 * (vv.right - vv.left);
        	}
        } else if (e.getKeyCode() == KeyEvent.VK_B) {
        	if (!e.isShiftDown()) {
        		vv.bottom -= (float) .1 * (vv.top - vv.bottom);
        	} else {
        		vv.bottom += (float) .1 * (vv.top - vv.bottom);
        	}
        } else if (e.getKeyCode() == KeyEvent.VK_T) {
        	if (!e.isShiftDown()) {
        		vv.top += (float) .1 * (vv.top - vv.bottom);
        	} else {
        		vv.top -= (float) .1 * (vv.top - vv.bottom);
        	}
        } else if (e.getKeyCode() == KeyEvent.VK_N) {
        	if (!e.isShiftDown()) {
        		vv.near += (float) .1 * (vv.near - vv.far);
        	} else {
        		vv.near -= (float) .1 * (vv.near - vv.far);
        	}
        } else if (e.getKeyCode() == KeyEvent.VK_F) {
        	if (!e.isShiftDown()) {
        		vv.far -= (float) .1 * (vv.near - vv.far);
        	} else {
        		vv.far -= (float) .1 * (vv.near - vv.far);
        	}
        }
        repaint();
    }
    
    public void keyTyped(KeyEvent e) {
    	//do nothing
    }
    
    public void paintComponent(Graphics g) {
    	whiteOut();
        rasterizeShapes(shapes);
        BufferedImage image = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
        WritableRaster raster = image.getRaster();
        
        for (int i = 0; i < pixels.length; i += 3) {
        	int sum = (pixels[i] + pixels[i + 1] + pixels[i + 2]);
        	pixels[i] = sum;
        	pixels[i + 1] = sum;
        	pixels[i + 2] = sum;
        }
        
        
        raster.setPixels(0, 0, width, height, pixels);       
        g.drawImage(image, 0, 0, null);
    }
    
    /**
     * Constructor for the class.
     */
    public TCSS458Paint() {
    	/****Added these to save input file data***/
    	shapes = new ArrayList<AbstractShape>();
    	/******************************************/
        createImage();
        setPreferredSize(new Dimension(width,height));
        setFocusable(true);
        addKeyListener(this);
    }


    public static void main(String args[]) {
    	JFrame frame = new JFrame("Paint Demo");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().add(new TCSS458Paint());
        frame.pack();      
        frame.setLocationRelativeTo( null );
        frame.setVisible( true );
    }
    
    private class Range {
    	@Override
		public String toString() {
			return "Range [min=" + min + ", max=" + max + ", minZ=" + minZ
					+ ", maxZ=" + maxZ + "]";
		}

		int min, max;
    	float minZ, maxZ;
    	
    	public Range(final int the_min, final int the_max) {
    		min = the_min;
    		max = the_max;
    	}
    	
    	public Range(final int the_min, final int the_max, final float the_minZ, final float the_maxZ) {
    		min = the_min;
    		max = the_max;
    		minZ = the_minZ;
    		maxZ = the_maxZ;
    	}
    }
    
    private class ViewVolume {
    	float left;
    	float right;
    	float bottom;
    	float top;
    	float near;
    	float far;
    	
    	public ViewVolume(final float l, final float r, final float b, final float t, final float n, final float f) {
    		left = l;
    		right = r;
    		bottom = b;
    		top = t;
    		near = n;
    		far = f;
    	}
    }
}