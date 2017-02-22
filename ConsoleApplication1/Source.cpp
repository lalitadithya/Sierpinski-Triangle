#include "Dependecies\glew\glew.h"
#include "Dependecies\freeglut\freeglut.h"
#include <cmath>
#include <vector>

#define NUM_SPLIT 5

using std::vector;
using std::pair;
using std::make_pair;

typedef pair<GLfloat, GLfloat> Vertex; // a vertex for a 2D triangle is a pair of points
typedef vector<Vertex> Triangle; // a 2D triangle is a list of vertices (north, west, east in that order)

// the initial triagle
Triangle initial_trinagle;

/*
 * Helper method to draw a triangle on the screen
 * triangle - triangle that has to be drawn
 */
void draw_triangle(Triangle triangle)
{
	glBegin(GL_POLYGON);
	glVertex2f(triangle[0].first, triangle[0].second);
	glVertex2f(triangle[1].first, triangle[1].second);
	glVertex2f(triangle[2].first, triangle[2].second);
	glEnd();
	glFlush();
}

/*
 * Helper method to get the mid point between two vertices
 * vertex1 - the first vertex
 * vertex2 - the second vertex
 * returns - the mid point 
 */
Vertex get_midpoint(Vertex &vertex1, Vertex &vertex2)
{
	return make_pair((vertex1.first + vertex2.first) / 2.0, (vertex1.second + vertex2.second) / 2.0);
}

/*
 * Helper method to construct a triangle given the vertices
 * vertex1 - the north vertex of the triangle
 * vertex2 - the west vertex of the triangle
 * vertex3 - the east vertex of the triangle
 * returns - the triangle
 */
Triangle construct_trinagle(Vertex &vertex1, Vertex &vertex2, Vertex &vertex3)
{
	Triangle triangle;
	triangle.push_back(vertex1);
	triangle.push_back(vertex2);
	triangle.push_back(vertex3);
	return triangle;
}

/*
 * Method to recursively generate the Sierpinski Triangle
 * triangle - the triangle that has to be split
 * number_split - the number of times the triangle has to be split
 */
void split_triangle(Triangle &triangle, int number_splits)
{
	if (number_splits == 0)
	{
		draw_triangle(triangle);
	}
	else
	{
		// calculate the midpoints of all the sides of the triangle
		Triangle midpoints;
		midpoints.push_back(get_midpoint(triangle[0], triangle[1]));
		midpoints.push_back(get_midpoint(triangle[1], triangle[2]));
		midpoints.push_back(get_midpoint(triangle[0], triangle[2]));

		// recursively split the triangle
		split_triangle(construct_trinagle(triangle[0], midpoints[0], midpoints[2]), number_splits - 1);
		split_triangle(construct_trinagle(midpoints[0], triangle[1], midpoints[1]), number_splits - 1);
		split_triangle(construct_trinagle(midpoints[2], midpoints[1], triangle[2]), number_splits - 1);
	}
}

/*
 * GLUT function to draw the ouput
 */
void display()
{
	// clear the buffer
	glClear(GL_COLOR_BUFFER_BIT);

	// set the color
	glColor3f(1.0f, 0.0f, 0.0f);

	// draw the initial triangle
	glBegin(GL_LINES);
	glVertex2f(initial_trinagle[0].first, initial_trinagle[0].second);
	glVertex2f(initial_trinagle[1].first, initial_trinagle[1].second);
	glVertex2f(initial_trinagle[1].first, initial_trinagle[1].second);
	glVertex2f(initial_trinagle[2].first, initial_trinagle[2].second);
	glVertex2f(initial_trinagle[2].first, initial_trinagle[2].second);
	glVertex2f(initial_trinagle[0].first, initial_trinagle[0].second);
	glEnd();
	glFlush();

	// split the initial triangle
	split_triangle(initial_trinagle, NUM_SPLIT);
}

/*
 * Helper method to initialize the required variables and GLUT
 */
void init()
{
	// initialize the initial triangle
	initial_trinagle.push_back(make_pair(20, 20));
	initial_trinagle.push_back(make_pair(10, 10));
	initial_trinagle.push_back(make_pair(30, 10));

	// set the backgroud color
	glClearColor(0.0, 0.0, 0.0, 0.0);

	// set the ortho space
	gluOrtho2D(10.0, 30.0, 10.0, 20.0);
}

/*
 * Main function
 */
int main(int argc, char **argv)
{
	// initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// create the window
	glutInitWindowSize(500, 500);
	glutCreateWindow("Sierpinski Triangle");

	// initialize the callbacks
	glutDisplayFunc(display);

	// initialize the variables
	init();

	// main loop 
	glutMainLoop();
	return 0;
}