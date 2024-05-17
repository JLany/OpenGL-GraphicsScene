#pragma once

#include <gl/GL.h>
#include <gl/GLU.h>
#include "Vertex.h"
#include <vector>


void DrawPlane(std::vector<Vertex>& plane, float color[3])
{
	glBegin(GL_TRIANGLES);
	glColor3f(color[0], color[1], color[2]); glVertex3f(plane[1].x, plane[1].y, plane[1].z); // top right
	glColor3f(color[0], color[1], color[2]); glVertex3f(plane[3].x, plane[3].y, plane[3].z); // bottom right
	glColor3f(color[0], color[1], color[2]); glVertex3f(plane[2].x, plane[2].y, plane[2].z); // bottom left

	glColor3f(color[0], color[1], color[2]); glVertex3f(plane[0].x, plane[0].y, plane[0].z); // top left
	glColor3f(color[0], color[1], color[2]); glVertex3f(plane[1].x, plane[1].y, plane[1].z); // top right
	glColor3f(color[0], color[1], color[2]); glVertex3f(plane[2].x, plane[2].y, plane[2].z); // bottom left
	glEnd();
}


void DrawCube(std::vector<Vertex>& cube, float color[3])
{
	std::vector<Vertex> plane(4);

	//plane.clear();

	// front face
	plane[0] = cube[0]; // top left
	plane[1] = cube[1]; // top right
	plane[2] = cube[2]; // bottom left
	plane[3] = cube[3]; // bottom right

	DrawPlane(plane, color);

	//plane.clear();

	// right side
	plane[0] = cube[1]; // top left
	plane[1] = cube[5]; // top right
	plane[2] = cube[3]; // bottom left
	plane[3] = cube[7]; // bottom right

	DrawPlane(plane, color);

	//plane.clear();

	// left side
	plane[0] = cube[4]; // top left
	plane[1] = cube[0]; // top right
	plane[2] = cube[6]; // bottom left
	plane[3] = cube[2]; // bottom right

	DrawPlane(plane, color);

	//plane.clear();

	// back face
	plane[0] = cube[4]; // top left
	plane[1] = cube[5]; // top right
	plane[2] = cube[6]; // bottom left
	plane[3] = cube[7]; // bottom right

	DrawPlane(plane, color);

	//plane.clear();

	// top 
	plane[0] = cube[4]; // top left
	plane[1] = cube[5]; // top right
	plane[2] = cube[0]; // bottom left
	plane[3] = cube[1]; // bottom right

	DrawPlane(plane, color);

	//plane.clear();

	// bottom
	plane[0] = cube[6]; // top left
	plane[1] = cube[7]; // top right
	plane[2] = cube[2]; // bottom left
	plane[3] = cube[3]; // bottom right

	DrawPlane(plane, color);
}



void DrawBeam(float thetax, float thetay, float thetaz, float scalex, float scaley, float scalez, std::vector<Vertex>& cube, float color[])
{
	glRotatef(thetax, 1.0f, 0.0f, 0.0f);
	glRotatef(thetay, 0.0f, 1.0f, 0.0f);
	glRotatef(thetaz, 0.0f, 0.0f, 1.0f);
	glScalef(scalex, scaley, scalez);
	DrawCube(cube, color);
	glScalef(1.0f / scalex, 1.0f / scaley, 1.0f / scalez);
	glRotatef(-thetaz, 0.0f, 0.0f, 1.0f);
	glRotatef(-thetay, 0.0f, 1.0f, 0.0f);
	glRotatef(-thetax, 1.0f, 0.0f, 0.0f);
}
