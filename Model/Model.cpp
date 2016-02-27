/*
 * Model.cpp
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#include "Model.h"

namespace Tetris3D {

Model::Model(OpenGLProgram* program, TetrisEngine* tetrisEngine) {
	this->program = program;
	this->tetrisEngine = tetrisEngine;

	currentPiece = new ModelPiece(program);

	well = new ModelPiece(program);
	well->SetPiece(tetrisEngine->GetWell());

	grid = new ModelGrid(program);
	grid->SetWell(tetrisEngine->GetWell());

	shadow = new ModelShadow(program);
	shadow->SetWell(tetrisEngine->GetWell());

	isGenerateGrid = true;
}

Model::~Model() {
	delete currentPiece;
	currentPiece = 0;
	delete well;
	well = 0;
	delete grid;
	grid = 0;
	delete shadow;
	shadow = 0;

	tetrisEngine = 0;
}

bool Model::IsNeedToRender() {
	return tetrisEngine->IsCurrentPieceMoved();
}

void Model::Render() {
	grid->Render(isGenerateGrid);
	isGenerateGrid = false;

	currentPiece->SetPiece(tetrisEngine->GetCurrentPiece());
	currentPiece->Render();

	well->Render(tetrisEngine->IsWellChanged());

	shadow->SetPiece(tetrisEngine->GetCurrentPiece());
	shadow->Render();
}

} /* namespace Tetris3D */
