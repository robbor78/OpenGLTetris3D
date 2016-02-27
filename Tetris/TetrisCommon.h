/*
 * TetrisCommon.h
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#ifndef TETRISCOMMON_H_
#define TETRISCOMMON_H_

#include <vector>

namespace Tetris3D {
struct VoxelColour {
	float red;
	float green;
	float blue;
	float alpha;

public:
	float* AsFV() {
		return new float[4] { red, green, blue, alpha };
	}
};

struct VoxelLocation {
	unsigned int col;
	unsigned int row;
	unsigned int dep;

	VoxelLocation Move(int incCol, int incRow, int incDep) {
		VoxelLocation v;
		v.col = this->col + incCol;
		v.row = this->row + incRow;
		v.dep = this->dep + incDep;
		return v;
	}
};

typedef VoxelLocation Location;

struct VoxelDrawPosition {
	float x;
	float y;
	float z;
};

}

#endif /* TETRISCOMMON_H_ */
