/*
 * TetrisEngine.cpp
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#include "TetrisEngine.h"

namespace Tetris3D {

TetrisEngine::TetrisEngine(InputManager* inputManager) {

	logger = Logger::GetLogger();

	logger->info("Initialised Tetris engine.");

	this->inputManager = inputManager;
	isGameOver = false;
	isCanStartMoveDelay = true;
	moveDelay = 0.0;
	isPaused = false;

	time(&timer);

	well = new Well(10, 14, 4);
	isWellChanged = true;

	currentPiece = 0;
	PickPiece();

}

TetrisEngine::~TetrisEngine() {
	logger->info("Stopping Tetris engine.");
	delete currentPiece;
	currentPiece = 0;
	delete well;
	well = 0;
	logger->info("Stopped Tetris engine.");
}

void TetrisEngine::Run() {

	if (isGameOver)
	{
		logger->debug("Game over.");
		return;
	}

	if (inputManager->IsPPressed())
	{
		isPaused = !isPaused;
	}
	if (isPaused)
	{
		time(&timer);
		return;
	}

	bool isKeyPressed = false;
	int incDep = 0;
	int incCol = 0;
	if (inputManager->IsDownPressed()) {
		isKeyPressed = true;
		incDep = 1;
	} else if (inputManager->IsUpPressed()) {
		isKeyPressed = true;
		incDep = -1;
	} else if (inputManager->IsLeftPressed()) {
		isKeyPressed = true;
		incCol = -1;
	} else if (inputManager->IsRightPressed()) {
		isKeyPressed = true;
		incCol = 1;
	}
	if (isKeyPressed && well->CanMove(currentPiece, incCol, 0, incDep)) {
		logger->debug("Piece moved by user.");
		currentPiece->Move(incCol, 0, incDep);
	}
	if (inputManager->IsAPressed()) {
		if (well->CanRotateZCCW(currentPiece)) {
			logger->debug("Piece rotated (Z-CCW) by user.");
			currentPiece->RotateZCCW();
		}
	}
	if (inputManager->IsSPressed()) {
		if (well->CanRotateYCCW(currentPiece)) {
			logger->debug("Piece rotated (Y-CCW) by user.");
			currentPiece->RotateYCCW();
		}
	}
	if (inputManager->IsDPressed()) {
		if (well->CanRotateXCCW(currentPiece)) {
			logger->debug("Piece rotated (X-CCW) by user.");
			currentPiece->RotateXCCW();
		}
	}
	if (inputManager->IsSpacebarPressed()) {
		well->Drop(currentPiece);
		isDrop = true;
	}
	if (IsNeedToMove()) {
		if (isCanStartMoveDelay && well->CanMove(currentPiece, 0, 1, 0)) {
			logger->debug("Piece moved.");

			currentPiece->Move(0, 1, 0);

		} else if (isCanStartMoveDelay && !isDrop) {
			logger->debug("Entering move delay.");

			isCanStartMoveDelay = false;
			moveDelay = 0;
		} else if (isDrop || moveDelay > 2.0) {
			logger->debug("Fixing piece.");

			moveDelay = 0;
			isCanStartMoveDelay = true;
			isDrop = false;
			isWellChanged = true;

			well->Add(currentPiece);

			PickPiece();

			if (well->CanMove(currentPiece)) {
				isGameOver = false;
			} else {
				logger->debug("Game over condition detected.");
				isGameOver = true;
			}
		}

	}
}

bool TetrisEngine::IsNeedToMove() {
	time_t now;

	time(&now);

	double seconds = 0.0;
	seconds = difftime(now, timer);

	isNeedToMove = seconds >= 2.0;

	if (!isCanStartMoveDelay) {
		moveDelay += seconds;
	}

	if (isNeedToMove) {
		std::ostringstream strs;
		strs << "Need to move. Elapsed time:" << seconds << "(sec)";
		logger->debug(strs.str());

		timer = now;
	}

	return isNeedToMove;
}

void TetrisEngine::PickPiece() {
	if (currentPiece != 0) {
		logger->debug("Deleting previous piece.");
		delete currentPiece;
		currentPiece = 0;
	}

	logger->debug("Making new piece.");

	currentPiece = new Piece(2);
	Voxel* v = new Voxel();
	v->GetColour().alpha = 1.0;
	v->GetColour().blue = 0.0;
	v->GetColour().green = 1.0;
	v->GetColour().red = 0.0;
	v->GetLocation().col = 0;
	v->GetLocation().row = 0;
	v->GetLocation().dep = 0;
	v->GetPosition().x = 0.0;
	v->GetPosition().y = 0.0;
	v->GetPosition().z = 0.0;
	currentPiece->Set(v->GetLocation().col, v->GetLocation().row, v->GetLocation().dep, v);

	v = new Voxel();
	v->GetColour().alpha = 1.0;
	v->GetColour().blue = 0.0;
	v->GetColour().green = 0.0;
	v->GetColour().red = 1.0;
	v->GetLocation().col = 1;
	v->GetLocation().row = 0;
	v->GetLocation().dep = 0;
	v->GetPosition().x = 0.0;
	v->GetPosition().y = 0.0;
	v->GetPosition().z = 0.0;
	currentPiece->Set(v->GetLocation().col, v->GetLocation().row, v->GetLocation().dep, v);

	v = new Voxel();
	v->GetColour().alpha = 1.0;
	v->GetColour().blue = 1.0;
	v->GetColour().green = 1.0;
	v->GetColour().red = 1.0;
	v->GetLocation().col = 0;
	v->GetLocation().row = 1;
	v->GetLocation().dep = 0;
	v->GetPosition().x = 0.0;
	v->GetPosition().y = 0.0;
	v->GetPosition().z = 0.0;
	currentPiece->Set(v->GetLocation().col, v->GetLocation().row, v->GetLocation().dep, v);

	v = new Voxel();
	v->GetColour().alpha = 1.0;
	v->GetColour().blue = 1.0;
	v->GetColour().green = 0.0;
	v->GetColour().red = 0.2;
	v->GetLocation().col = 1;
	v->GetLocation().row = 1;
	v->GetLocation().dep = 0;
	v->GetPosition().x = 0.0;
	v->GetPosition().y = 0.0;
	v->GetPosition().z = 0.0;
	currentPiece->Set(v->GetLocation().col, v->GetLocation().row, v->GetLocation().dep, v);
}

} /* namespace Tetris3D */
