/*
 * ModelGrid.h
 *
 *  Created on: 22 Dec 2013
 *      Author: bert
 */

#ifndef MODELGRID_H_
#define MODELGRID_H_

#include <vector>

#include "AbstractModelPiece.h"
#include "../Tetris/Well.h"

namespace Tetris3D {

class ModelGrid: public AbstractModelPiece {
public:
	ModelGrid(OpenGLProgram* program);
	virtual ~ModelGrid();

	void SetWell(Well* well) {
		this->well = well;
	}

protected:
	void GenerateBuffers();
	void InitBuffers();
	void DrawBuffers();

private:
	Well* well;
	GLuint vbo; //vertex buffer object

	void MakeGrid(std::vector<float> &cs);
};

} /* namespace Tetris3D */

#endif /* MODELGRID_H_ */
