/*
 * Voxel.h
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#ifndef VOXEL_H_
#define VOXEL_H_

#include "TetrisCommon.h"

namespace Tetris3D {

class Voxel {
public:
	Voxel();
	virtual ~Voxel();

	void Move(int incCol, int incRow, int incDep);

	Voxel* Copy();

	VoxelColour& GetColour() {
		return colour;
	}

	void SetColour(VoxelColour& colour) {
		this->colour = colour;
	}

	VoxelLocation& GetLocation() {
		return location;
	}

	void SetLocation(VoxelLocation& location) {
		this->location = location;
	}

	VoxelDrawPosition& GetPosition() {
		return position;
	}

	void SetPosition(VoxelDrawPosition& position) {
		this->position = position;
	}

private:
	VoxelLocation location;
	VoxelDrawPosition position;
	VoxelColour colour;

};

} /* namespace Tetris3D */

#endif /* VOXEL_H_ */
