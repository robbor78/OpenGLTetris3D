/*
 * Voxel.cpp
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#include "Voxel.h"

namespace Tetris3D {

Voxel::Voxel() {

}

Voxel::~Voxel() {
}

void Voxel::Move(int incCol, int incRow, int incDep) {
	location.col += incCol;
	location.row += incRow;
	location.dep += incDep;
}

Voxel* Voxel::Copy()
{
	Voxel* v = new Voxel();

	v->colour = VoxelColour(this->colour);
	v->location = VoxelLocation(this->location);
	v->position = VoxelDrawPosition(this->position);

	return v;
}

} /* namespace Tetris3D */
