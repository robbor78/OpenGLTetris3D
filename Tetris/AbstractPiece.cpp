/*
 * AbstractPiece.cpp
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#include "AbstractPiece.h"

namespace Tetris3D {

AbstractPiece::AbstractPiece(int col, int row, int dep) {
	this->col = col;
	this->row = row;
	this->dep = dep;
	location.col = 0;
	location.row = 0;
	location.dep = 0;
	CreateContainer();
}

AbstractPiece::~AbstractPiece() {
	for (unsigned int c = 0; c < col; c++) {
		for (unsigned int r = 0; r < row; r++) {
			for (unsigned int d = 0; d < dep; d++) {
				Voxel* v = container[c][r][d];
				if (v != 0) {
					delete v;
					v = 0;
				}
				container[c][r][d] = 0;
			}
		}
	}
}

void AbstractPiece::Move(int incCol, int incRow, int incDep) {
	VoxelLocation newLocation(location);
	newLocation.col += incCol;
	newLocation.row += incRow;
	newLocation.dep += incDep;

	location = newLocation;
}

void AbstractPiece::Set(unsigned int col, unsigned int row, unsigned int dep, bool flag) {
	if (!Validate(col, row, dep))
		return;

	Voxel* v = 0;
	if (flag) {
		v = new Voxel();

		VoxelColour colour;
		colour.alpha = 1.0;
		colour.red = 0.0;
		colour.green = 0.0;
		colour.blue = 1.0;
		v->SetColour(colour);

		VoxelLocation location;
		location.col = col;
		location.row = row;
		location.dep = dep;
		v->SetLocation(location);

		VoxelDrawPosition position;
		position.x = 0.0;
		position.y = 0.0;
		position.z = 0.0;
		v->SetPosition(position);
	}
	Set(col, row, dep, v);
}

void AbstractPiece::Set(unsigned int col, unsigned int row, unsigned int dep, Voxel* voxel) {
	if (!Validate(col, row, dep))
		return;

	Voxel* oldVoxel = container[col][row][dep];

	if (oldVoxel != 0) {
		delete oldVoxel;
		oldVoxel = 0;
	}
	container[col][row][dep] = voxel;

}

Voxel* AbstractPiece::operator()(const unsigned int col, const unsigned int row, const unsigned int dep) {
	if (!Validate(col, row, dep))
		return 0;
	return container[col][row][dep];
}

void AbstractPiece::CreateContainer() {
	container = PieceArray(col);
	for (unsigned int c = 0; c < col; c++) {
		container[c] = RowArray(row);
		for (unsigned int r = 0; r < row; r++) {
			container[c][r] = DepthArray(dep);
			for (unsigned int d = 0; d < dep; d++) {
				container[c][r][d] = 0;
			}
		}
	}
}

int AbstractPiece::GetFirstRow() {
	for (unsigned int r = 0; r < row; r++) {
		for (unsigned int c = 0; c < col; c++) {
			for (unsigned int d = 0; d < dep; d++) {
				if (container[col][row][dep])
					return row;
			}
		}
	}
	return 0;
}

void AbstractPiece::SwapVoxels(unsigned int dest_c, unsigned int dest_r, unsigned int dest_d, Voxel* src) {

	Voxel* dest = container[dest_c][dest_r][dest_d];
	if (src == 0) {
		if (dest != 0) {
			delete container[dest_c][dest_r][dest_d];
		}
		container[dest_c][dest_r][dest_d] = 0;
		return;
	}

	if (dest == 0) {
		Voxel* v = new Voxel();
		v->GetLocation().col = dest_c;
		v->GetLocation().row = dest_r;
		v->GetLocation().dep = dest_d;
		container[dest_c][dest_r][dest_d] = v;
		dest = container[dest_c][dest_r][dest_d];
	}

	dest->GetColour().red = src->GetColour().red;
	dest->GetColour().blue = src->GetColour().blue;
	dest->GetColour().green = src->GetColour().green;
	dest->GetColour().alpha = src->GetColour().alpha;

}


} /* namespace Tetris3D */
