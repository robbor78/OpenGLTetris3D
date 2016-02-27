/*
 * VoxelModel.h
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#ifndef MODELPIECE_H_
#define MODELPIECE_H_

#include "AbstractModelPiece.h"

namespace Tetris3D {

class ModelPiece : public AbstractModelPiece {
public:
	ModelPiece(OpenGLProgram* program);
	virtual ~ModelPiece();

	AbstractPiece& GetPiece() {
		return *piece;
	}

	void SetPiece(AbstractPiece* piece) {
		this->piece = piece;
	}

	bool IsNeedToRedraw()
	{
		return piece->IsChanged();
	}

protected:
	void GenerateBuffers();
	void InitBuffers();
	void DrawBuffers();

private:
	AbstractPiece* piece;
	glm::mat4 translate;
	GLuint vbo; //vertex buffer object
	GLuint ibo; //index buffer object

	void Convert(std::vector<float> &cs, std::vector<unsigned short> &el);
	void MakeElements(std::vector<unsigned short> &el, int numElements, int cubeNum);

};

} /* namespace Tetris3D */

#endif /* MODELPIECE_H_ */
