/*****************************************************************************
 * Larmor-Physx Version 1.0 2013
 * Copyright (c) 2013 Pier Paolo Ciarravano - http://www.larmor.com
 * All rights reserved.
 *
 * This file is part of Larmor-Physx (http://code.google.com/p/larmor-physx/).
 *
 * Larmor-Physx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Larmor-Physx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Larmor-Physx. If not, see <http://www.gnu.org/licenses/>.
 *
 * Licensees holding a valid commercial license may use this file in
 * accordance with the commercial license agreement provided with the
 * software.
 *
 * Author: Pier Paolo Ciarravano
 * $Id$
 *
 ****************************************************************************/

#include <iostream>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

#include "util.h"

#define REAL float


//Funzione di utilita per convertire da ListCTriangle3d a std::list<Triangle>
std::list<Triangle> toTriangles(ListCTriangle3d triangles)
{
	std::list<Triangle> output;

	ListCTriangle3d::iterator triangleIter;
	for(triangleIter=triangles.begin(); triangleIter!= triangles.end(); ++triangleIter)
	{
		CTriangle3d t = *triangleIter;
		Triangle triangle3d(Point(t.aX, t.aY, t.aZ), Point(t.bX, t.bY, t.bZ), Point(t.cX, t.cY, t.cZ));
		output.push_back(triangle3d);
	}

	return output;
}


//Funzione di utilita per convertire da std::list<Triangle> a ListCTriangle3d
ListCTriangle3d fromTriangles(std::list<Triangle> triangles)
{
	ListCTriangle3d output;

	std::list<Triangle>::iterator triangleIter;
	for(triangleIter=triangles.begin(); triangleIter!= triangles.end(); ++triangleIter)
	{
		Triangle t = *triangleIter;

		CTriangle3d tri;
		tri.aX = CGAL::to_double(t.vertex(0).x());
		tri.aY = CGAL::to_double(t.vertex(0).y());
		tri.aZ = CGAL::to_double(t.vertex(0).z());
		tri.bX = CGAL::to_double(t.vertex(1).x());
		tri.bY = CGAL::to_double(t.vertex(1).y());
		tri.bZ = CGAL::to_double(t.vertex(1).z());
		tri.cX = CGAL::to_double(t.vertex(2).x());
		tri.cY = CGAL::to_double(t.vertex(2).y());
		tri.cZ = CGAL::to_double(t.vertex(2).z());

		output.push_back(tri);

	}

	return output;
}

ListCTriangle3d fromTriangles(std::list<Triangle> triangles, std::list<TriangleInfo> trianglesInfoInput)
{
	//error se diversi size in input
	if (triangles.size() != trianglesInfoInput.size())
	{
		std::cout << "ERROR: fromTriangles: triangles.size() != trianglesInfoInput.size()" << std::endl;
		exit(-1);
	}

	ListCTriangle3d output;

	std::list<Triangle>::iterator triangleIter;
	std::list<TriangleInfo>::iterator triangleInfoIter;
	for(triangleIter=triangles.begin(), triangleInfoIter=trianglesInfoInput.begin();
			triangleIter!= triangles.end();
			++triangleIter, ++triangleInfoIter)
	{
		Triangle t = *triangleIter;
		TriangleInfo tInfo = *triangleInfoIter;

		CTriangle3d tri;
		tri.aX = CGAL::to_double(t.vertex(0).x());
		tri.aY = CGAL::to_double(t.vertex(0).y());
		tri.aZ = CGAL::to_double(t.vertex(0).z());
		tri.bX = CGAL::to_double(t.vertex(1).x());
		tri.bY = CGAL::to_double(t.vertex(1).y());
		tri.bZ = CGAL::to_double(t.vertex(1).z());
		tri.cX = CGAL::to_double(t.vertex(2).x());
		tri.cY = CGAL::to_double(t.vertex(2).y());
		tri.cZ = CGAL::to_double(t.vertex(2).z());

		tri.type = tInfo.cutType;

		output.push_back(tri);

	}

	return output;
}

void fromTriangles(ListCTriangle3d &output, std::list<Triangle> triangles, std::list<TriangleInfo> trianglesInfoInput)
{
	//error se diversi size in input
	if (triangles.size() != trianglesInfoInput.size())
	{
		std::cout << "ERROR: fromTriangles: triangles.size() != trianglesInfoInput.size()" << std::endl;
		exit(-1);
	}

	std::list<Triangle>::iterator triangleIter;
	std::list<TriangleInfo>::iterator triangleInfoIter;
	for(triangleIter=triangles.begin(), triangleInfoIter=trianglesInfoInput.begin();
			triangleIter!= triangles.end();
			++triangleIter, ++triangleInfoIter)
	{
		Triangle t = *triangleIter;
		TriangleInfo tInfo = *triangleInfoIter;

		CTriangle3d tri;
		tri.aX = CGAL::to_double(t.vertex(0).x());
		tri.aY = CGAL::to_double(t.vertex(0).y());
		tri.aZ = CGAL::to_double(t.vertex(0).z());
		tri.bX = CGAL::to_double(t.vertex(1).x());
		tri.bY = CGAL::to_double(t.vertex(1).y());
		tri.bZ = CGAL::to_double(t.vertex(1).z());
		tri.cX = CGAL::to_double(t.vertex(2).x());
		tri.cY = CGAL::to_double(t.vertex(2).y());
		tri.cZ = CGAL::to_double(t.vertex(2).z());

		tri.type = tInfo.cutType;

		output.push_back(tri);

	}

}

std::list<Triangle> readPlyMeshToTriangles(const char* meshFile)
{
	int numVertexs, numFaces;

	std::list<Triangle> output;
	std::vector<Point> vertices;

	printf("Read PLY Points/Triangles Exact mesh from: %s\n", meshFile);

	FILE * pFile;
	pFile = fopen (meshFile, "r");
	char valStr[100];
	while (true)
	{
	  fscanf (pFile, "%s", valStr);

	  if (strcmp(valStr,"vertex") == 0) {
		  fscanf(pFile, "%d", &numVertexs);
	  }
	  if (strcmp(valStr,"face") == 0) {
	  	  fscanf(pFile, "%d", &numFaces);
	  }
	  if (strcmp(valStr,"end_header") == 0) {
		  break;
	  }
	}
	printf("Reading %d vertex and %d faces...\n", numVertexs, numFaces);

	//For dragon shatter static animation
	double xTrs = (-10.8324 +9.65662) / 2.0;
	double yTrs = ( 5.2729 +19.7173) / 2.0;
	double zTrs = (-5.04143 +4.12075) / 2.0;

	//Reading Vertexs
	double xp, yp, zp;
	double t1, t2;
	for (int i = 0;  i < numVertexs; ++i)
	{
		fscanf (pFile, "%lf %lf %lf", &xp, &yp, &zp);
		//fscanf (pFile, "%lf %lf %lf %lf %lf", &xp, &yp, &zp, &t1, &t2);
		//xp = xp /1000; yp = yp /1000; zp = zp /1000;
		//printf("%f,%f,%f\n", xp, yp, zp );
		Point vertex(xp, yp, zp);
		//For dragon shatter static animation
		//Point vertex(xp * 100.0 - xTrs, yp * 100.0 - yTrs, zp * 100.0 - zTrs);
		vertices.push_back(vertex);
	}
	//printf("%f,%f,%f\n", xp, yp, zp );

	//Reading Faces
	int ii, v1,v2,v3;
	for (int i = 0;  i < numFaces; ++i) //numFaces
	{
		fscanf (pFile, "%d %d %d %d", &ii, &v1, &v2, &v3);
		//printf("%d,%d,%d\n", v1, v2, v3 );
		Triangle triangle(vertices.at(v1), vertices.at(v2), vertices.at(v3));
		output.push_back(triangle);
	}
	//printf("%d,%d,%d\n", v1, v2, v3 );

	printf("Mesh Readed\n");
	fclose (pFile);

	return output;
}

std::list<Triangle> readOffMeshToTriangles(const char* meshFile)
{
	int numVertexs, numFaces, temp;

	std::list<Triangle> output;
	std::vector<Point> vertices;

	printf("Read OFF Points/Triangles Exact mesh from: %s\n", meshFile);

	FILE * pFile;
	pFile = fopen (meshFile, "r");
	char valStr[100];
	fscanf(pFile, "%s", valStr);
	fscanf(pFile, "%d", &numVertexs);
	fscanf(pFile, "%d", &numFaces);
	fscanf(pFile, "%d", &temp);

	printf("Reading %d vertex and %d faces...\n", numVertexs, numFaces);

	//Reading Vertexs
	double xp, yp, zp;
	for (int i = 0;  i < numVertexs; ++i)
	{
		fscanf (pFile, "%lf %lf %lf", &xp, &yp, &zp);
		//printf("%f,%f,%f\n", xp, yp, zp );
		Point vertex(xp, yp, zp);
		vertices.push_back(vertex);
	}
	//printf("%f,%f,%f\n", xp, yp, zp );

	//Reading Faces
	int ii, v1,v2,v3;
	for (int i = 0;  i < numFaces; ++i) //numFaces
	{
		fscanf (pFile, "%d %d %d %d", &ii, &v1, &v2, &v3);
		//printf("%d,%d,%d\n", v1, v2, v3 );
		Triangle triangle(vertices.at(v1), vertices.at(v2), vertices.at(v3));
		output.push_back(triangle);
	}
	//printf("%d,%d,%d\n", v1, v2, v3 );

	printf("Mesh Readed\n");
	fclose (pFile);

	return output;
}

std::list<Triangle> readObjMeshToTriangles(const char* meshFile)
{

	std::list<Triangle> output;
	std::vector<Point> vertices;

	printf("Read OBJ Points/Triangles Exact mesh from: %s\n", meshFile);

	FILE * pFile;
	pFile = fopen (meshFile, "r");
	char valStr[1000];

	//Read two start lines
	while ( fgetc(pFile) != '\n' );
	while ( fgetc(pFile) != '\n' );

	//Add fake vertex 0
	Point vertex(0, 0, 0);
	vertices.push_back(vertex);

	//Reading Vertexs
	double xp, yp, zp;
	int v1,v2,v3, u1, u2, u3;
	while (! feof(pFile) )
	{
		fscanf (pFile, "%s", valStr);
		//printf("----------> %s\n", valStr);

		if ( (strcmp(valStr,"v") == 0) || (strcmp(valStr,"vn") == 0) ) {

			fscanf (pFile, "%lf %lf %lf", &xp, &yp, &zp);
			//printf("%f,%f,%f (%d)\n", xp, yp, zp, vertices.size() );
			Point vertex(xp, yp, zp);
			vertices.push_back(vertex);

		} else if ( strcmp(valStr,"f") == 0 ) {

			fscanf (pFile, "%d//%d %d//%d %d//%d", &v1, &u1, &v2, &u2, &v3, &u3);
			//printf("%d,%d,%d\n", v1, v2, v3 );
			Triangle triangle(vertices.at(v1), vertices.at(v2), vertices.at(v3));
			output.push_back(triangle);

		}
		//else if ( strcmp(valStr,"end") == 0 ) {
		//	break;
		//}

	}

	printf("Mesh Readed\n");
	fclose (pFile);

	return output;
}


bool equalCSegment2d(CSegment2d a, CSegment2d b)
{
	if (a.startX != b.startX)
		return false;
	if (a.startY != b.startY)
		return false;
	if (a.endX != b.endX)
		return false;
	if (a.endY != b.endY)
		return false;

	return true;
}

void printDouble(double val)
{
	unsigned char * desmond = (unsigned char *) & val;
	int i;

	for (i = 0; i < sizeof (double); i++) {
		 printf ("%02X ", desmond[i]);
	}
	printf ("\n");
}


//DEPRECATED: USARE readMeshToTriangles in CutterMesher.h
ListCTriangle3d readMesh(const char* meshFile)
{
	std::cout << "DEPRECATED READ MESH!!!\n\n";

	int numVertexs, numFaces;
	REAL* gVertices; //[NUM_VERTICES * 3];
	int* gIndices; //[NUM_TRIANGLES][3];

	ListCTriangle3d output;

	printf("Read mesh from: %s\n", meshFile);

	FILE * pFile;
	pFile = fopen (meshFile, "r");
	char valStr[100];
	while (true)
	{
	  fscanf (pFile, "%s", valStr);

	  if (strcmp(valStr,"vertex") == 0) {
		  fscanf(pFile, "%d", &numVertexs);
	  }
	  if (strcmp(valStr,"face") == 0) {
	  	  fscanf(pFile, "%d", &numFaces);
	  }
	  if (strcmp(valStr,"end_header") == 0) {
		  break;
	  }
	}
	printf("Reading %d vertex and %d faces...\n", numVertexs, numFaces);

	gVertices = (REAL*)malloc(sizeof(REAL) * numVertexs * 3);
	gIndices = (int*)malloc(sizeof(int) * numFaces * 3);

	//Reading Vertexs
	float xp, yp, zp;
	for (int i = 0;  i < numVertexs; ++i)
	{
		fscanf (pFile, "%f %f %f", &xp, &yp, &zp);
		//printf("%f,%f,%f\n", xp, yp, zp );
		gVertices[i*3+0] = xp;
		gVertices[i*3+1] = yp;
		gVertices[i*3+2] = zp;
	}
	//printf("%f,%f,%f\n", xp, yp, zp );

	//Reading Faces
	int ii, v1,v2,v3;
	for (int i = 0;  i < numFaces; ++i) //numFaces
	{
		fscanf (pFile, "%d %d %d %d", &ii, &v1, &v2, &v3);
		//printf("%d,%d,%d\n", v1, v2, v3 );
		gIndices[i*3+0] = v1;
		gIndices[i*3+1] = v2;
		gIndices[i*3+2] = v3;
	}
	//printf("%d,%d,%d\n", v1, v2, v3 );

	printf("Mesh Readed\n");
	fclose (pFile);


	int i = 0;
	for (i = 0;  i < numFaces; ++i) //numFaces
	{
		CTriangle3d triangle;

		int vertex1 = gIndices[i*3+0];
		triangle.aX = gVertices[vertex1*3];
		triangle.aY = gVertices[vertex1*3 +1];
		triangle.aZ = gVertices[vertex1*3 +2];

		int vertex2 = gIndices[i*3+1];
		triangle.bX = gVertices[vertex2*3];
		triangle.bY = gVertices[vertex2*3 +1];
		triangle.bZ = gVertices[vertex2*3 +2];

		int vertex3 = gIndices[i*3+2];
		triangle.cX = gVertices[vertex3*3];
		triangle.cY = gVertices[vertex3*3 +1];
		triangle.cZ = gVertices[vertex3*3 +2];

		output.push_back(triangle);

	}

	//TODO: liberare memoria: gVertices and gIndices

	return output;
}



