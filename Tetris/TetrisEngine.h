/*
 * TetrisEngine.h
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#ifndef TETRISENGINE_H_
#define TETRISENGINE_H_

#include <time.h>

#include "../Logger.h"
#include "../InputManager.h"
#include "Piece.h"
#include "Well.h"

namespace Tetris3D {

class TetrisEngine {
public:
	TetrisEngine(InputManager* inputManager);
	virtual ~TetrisEngine();

	void Run();

	Piece* GetCurrentPiece() {
		return currentPiece;
	}

	Well* GetWell() {
		return well;
	}

	bool IsCurrentPieceMoved() const {
		return currentPiece->IsChanged();
	}

	bool IsWellChanged() {
		bool result = isWellChanged;
		isWellChanged = false;
		return result;
	}

private:
	log4cpp::Category* logger;
	InputManager* inputManager;
	Piece* currentPiece;
	Well* well;
	time_t timer;
	bool isNeedToMove;
	bool isWellChanged;
	double moveDelay;
	bool isCanStartMoveDelay;
	bool isDrop;
	bool isGameOver;
	bool isPaused;

	void PickPiece();
	bool IsNeedToMove();

};

} /* namespace Tetris3D */

#endif /* TETRISENGINE_H_ */
