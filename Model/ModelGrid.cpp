/*
 * ModelGrid.cpp
 *
 *  Created on: 22 Dec 2013
 *      Author: bert
 */

#include "ModelGrid.h"

namespace Tetris3D {

ModelGrid::ModelGrid(OpenGLProgram* program) :
		AbstractModelPiece(program) {
	well = 0;
	vbo = -1;
}

ModelGrid::~ModelGrid() {
	program = 0;
	well = 0;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &vbo);
}

void ModelGrid::GenerateBuffers() {
	std::vector<float> grid;
	MakeGrid(grid);
	GenerateArrayBuffer(vbo, grid);
}

void ModelGrid::InitBuffers() {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	AbstractModelPiece::InitBuffers();
}

void ModelGrid::DrawBuffers() {
	int size = 0;
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawArrays(GL_LINES, 0, size / sizeof(VertexStructure));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ModelGrid::MakeGrid(std::vector<float> &cs) {
	cs.clear();

	unsigned int maxCol = well->GetCol();
	unsigned int maxRow = well->GetRow();
	unsigned int maxDep = well->GetDep();

	for (unsigned int row = 0; row <= maxRow; row++) {

		float xStart = xOffset;
		float y = -(float) (row * sideLength) + yOffset;

		float xEnd = (float) (maxCol * sideLength) + xOffset;

		float zStart = 0.0; //sideLength * maxDep;
		PushIntoVector(cs, new float[3] { xStart, y, zStart }, new float[3] { 0.0, 0.0, -1.0 }, new float[4] { 1.0, 1.0,
				0.0, 1.0 });
		PushIntoVector(cs, new float[3] { xEnd, y, zStart }, new float[3] { 0.0, 0.0, -1.0 }, new float[4] { 1.0, 1.0, 0.0,
				1.0 });

		float zEnd = sideLength * maxDep;
		PushIntoVector(cs, new float[3] { xStart, y, zStart }, new float[3] { 0.0, 0.0, -1.0 }, new float[4] { 1.0, 1.0,
				0.0, 1.0 });
		PushIntoVector(cs, new float[3] { xStart, y, zEnd }, new float[3] { 0.0, 0.0, -1.0 }, new float[4] { 1.0, 1.0, 0.0,
				1.0 });

		PushIntoVector(cs, new float[3] { xEnd, y, zStart }, new float[3] { 0.0, 0.0, -1.0 }, new float[4] { 1.0, 1.0, 0.0,
				1.0 });
		PushIntoVector(cs, new float[3] { xEnd, y, zEnd }, new float[3] { 0.0, 0.0, -1.0 }, new float[4] { 1.0, 1.0, 0.0,
				1.0 });

	}

	for (unsigned int col = 0; col <= maxCol; col++) {

		float yStart = yOffset;
		float yEnd = -(float) (maxRow * sideLength) + yOffset;

		float x = (float) (col * sideLength) + xOffset;

		float zStart = 0.0;
		float zEnd = sideLength * maxDep;

		PushIntoVector(cs, new float[3] { x, yStart, zStart }, new float[3] { 0.0, 0.0, -1.0 }, new float[4] { 1.0, 0.0, 1.0, 1.0 });
		PushIntoVector(cs, new float[3] { x, yEnd, zStart }, new float[3] { 0.0, 0.0, -1.0 }, new float[4] { 1.0, 0.0, 1.0, 1.0 });

		PushIntoVector(cs, new float[3] { x, yEnd, zStart }, new float[3] { 0.0, 0.0, -1.0 }, new float[4] { 1.0, 1.0, 0.0,
				1.0 });
		PushIntoVector(cs, new float[3] { x, yEnd, zEnd }, new float[3] { 0.0, 0.0, -1.0 }, new float[4] { 1.0, 1.0, 0.0,
				1.0 });

	}

	for (unsigned int dep = 1; dep <= maxDep; dep++) {

		float z = dep * sideLength;

		float xStart = xOffset;
		float xEnd = (float) (maxCol * sideLength) + xOffset;

		float yStart = 14.0;
		float yEnd = -(float) (maxRow * sideLength) + yOffset;

		PushIntoVector(cs, new float[3] { xStart, yStart, z }, new float[3] { 0.0, 0.0, -1.0 }, new float[4] { 1.0, 1.0,
				0.0, 1.0 });
		PushIntoVector(cs, new float[3] { xStart, yEnd, z }, new float[3] { 0.0, 0.0, -1.0 }, new float[4] { 1.0, 1.0, 0.0,
				1.0 });

		PushIntoVector(cs, new float[3] { xEnd, yStart, z }, new float[3] { 0.0, 0.0, -1.0 }, new float[4] { 1.0, 1.0, 0.0,
				1.0 });
		PushIntoVector(cs, new float[3] { xEnd, yEnd, z }, new float[3] { 0.0, 0.0, -1.0 }, new float[4] { 1.0, 1.0, 0.0,
				1.0 });

		PushIntoVector(cs, new float[3] { xStart, yEnd, z }, new float[3] { 0.0, 0.0, -1.0 }, new float[4] { 1.0, 1.0, 0.0,
				1.0 });
		PushIntoVector(cs, new float[3] { xEnd, yEnd, z }, new float[3] { 0.0, 0.0, -1.0 }, new float[4] { 1.0, 1.0, 0.0,
				1.0 });
	}

}

} /* namespace Tetris3D */
