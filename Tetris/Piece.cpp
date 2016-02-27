/*
 * Piece.cpp
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#include "Piece.h"

namespace Tetris3D {

Piece::Piece(unsigned int size) :
		AbstractPiece(size, size, size) {
	this->size = size;
	isMoved = true;
}

Piece::~Piece() {
}

void Piece::Move(int incCol, int incRow, int incDep) {
	AbstractPiece::Move(incCol, incRow, incDep);
	isMoved = true;
//	for (unsigned int c = 0; c < size; c++) {
//		for (unsigned int r = 0; r < size; r++) {
//			for (unsigned int d = 0; d < size; d++) {
//				Voxel* v = container[c][r][d];
//				if (v != 0) {
//					v->Move(incCol, incRow, incDep);
//				}
//			}
//		}
//	}
}

void Piece::RotateZCCW() {
	isMoved = true;
	unsigned int n = size;
	unsigned int colLimit = floor((float) n / 2.0);
	unsigned int rowLimit = ceil((float) n / 2.0);

//	unsigned int topRow = GetTopRow();
//	unsigned int leftCol = GetLeftCol();
//	unsigned int topDep = GetTopDep();

	for (unsigned int d = 0; d < size; d++) {
		for (unsigned int c = 0; c < colLimit; c++) {
			for (unsigned int r = 0; r < rowLimit; r++) {

				Voxel* temp = container[c][r][d];
				if (temp != 0) {
					temp = temp->Copy();
				}

				SwapVoxels(c, r, d, container[n - 1 - r][c][d]); //	container[c][r][d] = container[n - 1 - r][c][d];

				SwapVoxels(n - 1 - r, c, d, container[n - 1 - c][n - 1 - r][d]); //container[n - 1 - r][c][d] = container[n - 1 - c][n - 1 - r][d];

				SwapVoxels(n - 1 - c, n - 1 - r, d, container[r][n - 1 - c][d]); // container[n - 1 - c][n - 1 - r][d] = container[r][n - 1 - c][d];

				SwapVoxels(r, n - 1 - c, d, temp); //container[r][n - 1 - c][d] = temp;

			}
		}
	}
}

void Piece::RotateYCCW() {
	isMoved = true;
	unsigned int n = size;
	unsigned int colLimit = floor((float) n / 2.0);
	unsigned int depLimit = ceil((float) n / 2.0);

	for (unsigned int r = 0; r < size; r++) {
		for (unsigned int c = 0; c < colLimit; c++) {
			for (unsigned int d = 0; d < depLimit; d++) {

				Voxel* temp = container[c][r][d];
				if (temp != 0) {
					temp = temp->Copy();
				}

				//SwapVoxels(c, r, d, container[n - 1 - r][c][d]);
				SwapVoxels(c, r, d, container[n - 1 - d][r][c]);

				//SwapVoxels(n - 1 - r, c, d, container[n - 1 - c][n - 1 - r][d]);
				SwapVoxels(n - 1 - d, r, c, container[n - 1 - c][r][n - 1 - d]);

				//SwapVoxels(n - 1 - c, n - 1 - r, d, container[r][n - 1 - c][d]);
				SwapVoxels(n - 1 - c, r, n - 1 - d, container[d][r][n - 1 - c]);

				//SwapVoxels(r, n - 1 - c, d, temp);
				SwapVoxels(d, r, n - 1 - c, temp);
			}
		}
	}
}

void Piece::RotateXCCW() {
	isMoved = true;
	unsigned int n = size;
	unsigned int colLimit = floor((float) n / 2.0);
	unsigned int rowLimit = ceil((float) n / 2.0);

	for (unsigned int c = 0; c < n; c++) {
		for (unsigned int d = 0; d < colLimit; d++) {
			for (unsigned int r = 0; r < rowLimit; r++) {

				Voxel* temp = container[c][r][d];
				if (temp != 0) {
					temp = temp->Copy();
				}

				//SwapVoxels(c, r, d, container[n - 1 - r][c][d]);
				SwapVoxels(c, r, d, container[c][d][n - 1 - r]);

				//SwapVoxels(n - 1 - r, c, d, container[n - 1 - c][n - 1 - r][d]);
				SwapVoxels(c, d, n - 1 - r, container[c][n - 1 - r][n - 1 - d]);

				//SwapVoxels(n - 1 - c, n - 1 - r, d, container[r][n - 1 - c][d]);
				SwapVoxels(c, n - 1 - r, n - 1 - d, container[c][n - 1 - d][r]);

				//SwapVoxels(r, n - 1 - c, d, temp);
				SwapVoxels(c, n - 1 - d, r, temp);

			}
		}
	}
}

unsigned int Piece::GetLeftCol() {

	for (unsigned int col = 0; col < size; col++) {
		for (unsigned int row = 0; row < size; row++) {
			for (unsigned int dep = 0; dep < size; dep++) {
				if (container[col][row][dep])
					return container[col][row][dep]->GetLocation().col;
			}
		}
	}
	return 0;
}

unsigned int Piece::GetTopRow() {
	for (unsigned int row = 0; row < size; row++) {
		for (unsigned int col = 0; col < size; col++) {
			for (unsigned int dep = 0; dep < size; dep++) {
				if (container[col][row][dep])
					return container[col][row][dep]->GetLocation().row;
			}
		}
	}
	return 0;
}

unsigned int Piece::GetBottomRow() {
	for (unsigned int row = size - 1; row >= 0; row--) {
		for (unsigned int col = 0; col < size; col++) {
			for (unsigned int dep = 0; dep < size; dep++) {
				if (container[col][row][dep])
					return container[col][row][dep]->GetLocation().row;
			}
		}
	}
	return 0;
}

unsigned int Piece::GetTopDep() {
	for (unsigned int dep = 0; dep < size; dep++) {
		for (unsigned int row = 0; row < size; row++) {
			for (unsigned int col = 0; col < size; col++) {
				if (container[col][row][dep])
					return container[col][row][dep]->GetLocation().dep;
			}
		}
	}
	return 0;
}

Voxel* Piece::GetLowestVoxel(unsigned int col, unsigned int dep) {
	if (!Validate(col, 0, dep)) {
		return 0;
	}

	for (int r = size - 1; r >= 0; r--) {
		Voxel* v = container[col][r][dep];
		if (v) {
			return v;
		}
	}

	return 0;

}

} /* namespace Tetris3D */
