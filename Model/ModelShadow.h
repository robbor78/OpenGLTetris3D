/*
 * ModelShadow.h
 *
 *  Created on: 22 Dec 2013
 *      Author: bert
 */

#ifndef MODELSHADOW_H_
#define MODELSHADOW_H_

#include "AbstractModelPiece.h"
#include "../Tetris/Well.h"

namespace Tetris3D {

class ModelShadow: public AbstractModelPiece {
public:
	ModelShadow(OpenGLProgram* program);
	virtual ~ModelShadow();

	void SetPiece(Piece* piece) {
		this->piece = piece;
	}

	void SetWell(Well* well) {
		this->well = well;
	}

protected:
	void GenerateBuffers();
	void InitBuffers();
	void DrawBuffers();

private:
	Piece* piece;
	Well* well;
	glm::mat4 translate;
	GLuint vbo; //vertex buffer object
	GLuint ibo; //index buffer object

	void GenerateCoordinates(std::vector<float>& cs, std::vector<unsigned short>& el);
	void MakeElements(std::vector<unsigned short> &el, int numElements, int shadowNum);
};

} /* namespace Tetris3D */

#endif /* MODELSHADOW_H_ */
