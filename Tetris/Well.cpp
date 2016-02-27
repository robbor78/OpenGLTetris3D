/*
 * Well.cpp
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#include "Well.h"

namespace Tetris3D {

Well::Well(unsigned int col, unsigned int row, unsigned int dep) :
		AbstractPiece(col, row, dep) {
	isAdded = false;
}

Well::~Well() {
}

bool Well::CanMove(Piece* piece, int incCol, int incRow, int incDep) {
	unsigned int pieceBottomRow = piece->GetBottomRow();
	if (pieceBottomRow >= this->row - 1)
		return false;

	Location offset = piece->GetLocation();

	int otherSize = piece->GetSize();
	for (int r = pieceBottomRow; r >= 0; r--) {
		for (int c = 0; c < otherSize; c++) {
			for (int d = 0; d < otherSize; d++) {
				Voxel* v = (*piece)(c, r, d);

				if (!v)
					continue;

				Location newLocation = v->GetLocation().Move(incCol + offset.col, incRow + offset.row, incDep + offset.dep);
				if (newLocation.col >= this->col)
					return false;
				if (newLocation.row >= this->row)
					return false;
				if (newLocation.dep >= this->dep)
					return false;
				if (this->container[newLocation.col][newLocation.row][newLocation.dep])
					return false;

			}
		}
	}
	return true;
}

void Well::Add(Piece* other) {
	int otherSize = other->GetSize();
	for (int c = 0; c < otherSize; c++) {

		for (int r = 0; r < otherSize; r++) {

			for (int d = 0; d < otherSize; d++) {

				Voxel* v = (*other)(c, r, d);

				if (!v)
					continue;

				VoxelLocation l = v->GetLocation();

				VoxelLocation locInWell = l.Move(other->GetLocation().col, other->GetLocation().row, other->GetLocation().dep);

				this->Set(locInWell.col, locInWell.row, locInWell.dep, true); //make a new voxel
				Voxel* newV = this->container[locInWell.col][locInWell.row][locInWell.dep];
				VoxelColour vc = VoxelColour(v->GetColour());
				newV->SetColour(vc); //this should make a copy
			}
		}
	}

	RemoveFullPlane();

	isAdded = true;
}

void Well::Drop(Piece* piece) {

	int dropDistance = row;

	unsigned int size = piece->GetSize();

	for (unsigned int d = 0; d < size; d++) {
		for (int r = size - 1; r >= 0; r--) {
			for (int c = size - 1; c >= 0; c--) {
				Voxel* v = (*piece)(c, r, d);

				if (!v)
					continue;

				int pieceRowInWell = v->GetLocation().row + piece->GetLocation().row;

				//get drop distance for empty well
				dropDistance = GetSmallestDistance(row - 1, pieceRowInWell, dropDistance);

				//get drop distance when well contains pieces
				int wellCol = v->GetLocation().col + piece->GetLocation().col;
				int wellDep = v->GetLocation().dep + piece->GetLocation().dep;
				for (int wellRow = row - 1; wellRow >= 0; wellRow--) {
					//check for piece
					if (this->container[wellCol][wellRow][wellDep]) {
						dropDistance = GetSmallestDistance(wellRow - 1, pieceRowInWell, dropDistance);
					}
				}
			}
		}
	}
	piece->Move(0, dropDistance, 0);
}

int Well::GetSmallestDistance(int wellRow, int pieceRowInWell, int currentDistance) {
	int newDD = wellRow - pieceRowInWell; //calculate distance
	if (newDD < currentDistance) {
		return newDD;
	} else {
		return currentDistance;
	}
}

bool Well::CanRotateZCCW(Piece* piece) {
	unsigned int size = piece->GetSize();

	for (unsigned int d = 0; d < size; d++) {
		for (unsigned int r = 0; r < size; r++) {
			for (unsigned int c = 0; c < size; c++) {
				Voxel* v = (*piece)(c, r, d);
				if (v == 0)
					continue;

				VoxelLocation l = v->GetLocation();

				int newCol = l.row + piece->GetLocation().col;
				int newRow = size - 1 - l.col + piece->GetLocation().row;
				int newDep = l.dep + piece->GetLocation().dep;

				if (!IsThereSpaceHere(newCol, newRow, newDep))
					return false;

			}
		}
	}
	return true;

}

bool Well::CanRotateYCCW(Piece* piece) {
	unsigned int size = piece->GetSize();

	for (unsigned int r = 0; r < size; r++) {
		for (unsigned int c = 0; c < size; c++) {
			for (unsigned int d = 0; d < size; d++) {

				Voxel* v = (*piece)(c, r, d);
				if (v == 0)
					continue;

				VoxelLocation l = v->GetLocation();

				int newCol = l.dep + piece->GetLocation().col;
				int newRow = l.row + piece->GetLocation().row;
				int newDep = size - 1 - l.col + piece->GetLocation().dep;

				if (!IsThereSpaceHere(newCol, newRow, newDep))
					return false;
			}
		}
	}
	return true;
}

bool Well::CanRotateXCCW(Piece* piece) {
	unsigned int size = piece->GetSize();

	for (unsigned int c = 0; c < size; c++) {
		for (unsigned int r = 0; r < size; r++) {
			for (unsigned int d = 0; d < size; d++) {

				Voxel* v = (*piece)(c, r, d);
				if (v == 0)
					continue;

				VoxelLocation l = v->GetLocation();

				int newCol = l.col + piece->GetLocation().col;
				int newRow = size - 1 - l.dep + piece->GetLocation().row;
				int newDep = l.row + piece->GetLocation().dep;

				if (!IsThereSpaceHere(newCol, newRow, newDep))
					return false;
			}
		}
	}
	return true;
}

bool Well::IsThereSpaceHere(int col, int row, int dep) {
	if (!Validate(col, row, dep))
		return false;

	return container[col][row][dep] == 0;
}

void Well::RemoveFullPlane() {
//go through all rows and look for full planes
	for (unsigned int r = 0; r < row; r++) {
		bool isPlaneFull = true;
		for (unsigned int c = 0; c < col && isPlaneFull; c++) {
			for (unsigned int d = 0; d < dep && isPlaneFull; d++) {
				isPlaneFull &= container[c][r][d] != 0;
			}
		}

		if (isPlaneFull) {
//			//remove the full row
//			for (unsigned int c = 0; c < col; c++) {
//				for (unsigned int d = 0; d < dep; d++) {
//					Voxel* v = 0;
//					this->Set(c, r, d, v);
//				}
//			}

			//drop everything above the removed row
			for (int dropRow = r - 1; dropRow >= 0; dropRow--) {
				for (unsigned int c = 0; c < col; c++) {
					for (unsigned int d = 0; d < dep; d++) {
						SwapVoxels(c, dropRow + 1, d, container[c][dropRow][d]);
						if (container[c][dropRow][d] != 0) {
							delete container[c][dropRow][d];
							container[c][dropRow][d] = 0;
						}
					}
				}
			}
		}
	}

}

Voxel* Well::GetHighestVoxel(unsigned int col, unsigned int dep) {

	if (!Validate(col, 0, dep)) {
		return 0;
	}

	for (unsigned int r = 0; r<row; r++) {
		Voxel* v = container[col][r][dep];
		if (v) {
			return v;
		}
	}

	return 0;


}

} /* namespace Tetris3D */

