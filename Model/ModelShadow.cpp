/*
 * ModelShadow.cpp
 *
 *  Created on: 22 Dec 2013
 *      Author: bert
 */

#include "ModelShadow.h"

namespace Tetris3D {

ModelShadow::ModelShadow(OpenGLProgram* program) :
		AbstractModelPiece(program) {
	logger->info("Initialising model shadow.");

	piece = 0;
	well = 0;
	vbo = -1;
	ibo = -1;
	isWireFrame = false;

	logger->info("Initialised model sgadow.");
}

ModelShadow::~ModelShadow() {
	piece = 0;
	well = 0;

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void ModelShadow::GenerateBuffers() {
	std::vector<float> cs;
	std::vector<unsigned short> el;
	GenerateCoordinates(cs, el);

	GenerateArrayBuffer(vbo, cs);
	GenerateElementBuffer(ibo, el);
}

void ModelShadow::InitBuffers() {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	AbstractModelPiece::InitBuffers();
}

void ModelShadow::DrawBuffers() {
	int size = 0;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ModelShadow::GenerateCoordinates(std::vector<float>& cs, std::vector<unsigned short>& el) {
	cs.clear();
	el.clear();

	unsigned int size = piece->GetSize();
	Location pieceLocation = piece->GetLocation();

	unsigned int numElements = 4; //number of elements (vertices) used for each shadow
	unsigned int shadowNum = 0;
	float rowOffset = 0.05;

	for (unsigned int c = 0; c < size; c++) {
		for (unsigned int d = 0; d < size; d++) {
			Voxel* pieceVoxel = piece->GetLowestVoxel(c, d);
			if (pieceVoxel == 0) {
				//no voxel at the location => nothing to do
				continue;
			}

			Location l = pieceLocation.Move(c, 0, d);
			Voxel* wellVoxel = well->GetHighestVoxel(l.col, l.dep);
			unsigned int row = 0;
			if (wellVoxel) {
				row = wellVoxel->GetLocation().row;
			} else {
				row = well->GetRow();
			}

			float f_l[3] = { (float) (l.col * sideLength + xOffset), -(float) row * sideLength + yOffset + rowOffset,
					(float) l.dep * sideLength };
			float f_r[3] = { f_l[0] + sideLength, f_l[1], f_l[2] };
			float b_l[3] = { f_l[0], f_l[1], f_l[2] + sideLength };
			float b_r[3] = { f_r[0], f_l[1], b_l[2] };

//			float f_l[3] = { -5.0 - 14.0, 0.0 };
//			float f_r[3] = { 5.0, -14.0, 0.0 };
//			float b_l[3] = { 5.0, 14.0, 0.0 };
//			float b_r[3] = { -5.0, 14.0, 0.0 };

			float colour[4] = { 1.0, 1.0, 1.0, 1.0 };
			float normal[3] = { 0.0, -1.0, 0.0 };

			PushIntoVector(cs, f_l, normal, colour);
			PushIntoVector(cs, f_r, normal, colour);
			PushIntoVector(cs, b_r, normal, colour);
			PushIntoVector(cs, b_l, normal, colour);

			MakeElements(el, numElements, shadowNum);
			shadowNum++;

		}
	}
}

void ModelShadow::MakeElements(std::vector<unsigned short> &el, int numElements, int shadowNum) {

	int offset = numElements * shadowNum;
//front
	el.push_back(0 + offset);
	el.push_back(1 + offset);
	el.push_back(2 + offset);
	el.push_back(2 + offset);
	el.push_back(3 + offset);
	el.push_back(0 + offset);
}

} /* namespace Tetris3D */
