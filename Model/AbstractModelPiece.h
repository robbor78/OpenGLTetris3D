/*
 * AbstractModelPiece.h
 *
 *  Created on: 22 Dec 2013
 *      Author: bert
 */

#ifndef ABSTRACTMODELPIECE_H_
#define ABSTRACTMODELPIECE_H_

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library

#define GLM_MESSAGES
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>	// TODO Auto-generated destructor stub

#include "../Tetris/Piece.h"
#include "../OpenGL/OpenGLProgram.h"
#include "../Logger.h"

namespace Tetris3D {

struct VertexStructure {
	float coord3d[3];
	float normal[3];
	float colour[3];
};

class AbstractModelPiece {
public:
	AbstractModelPiece(OpenGLProgram* program);
	virtual ~AbstractModelPiece();

	virtual void Render(bool isGenerateBuffers = true);

	void SetIsWireFrame(bool isWireFrame) {
		this->isWireFrame = isWireFrame;
	}

protected:
	OpenGLProgram* program;
	log4cpp::Category* logger;
	bool isWireFrame;
	float sideLength;
	GLint attribute_coord3d, attribute_colour, attribute_normal;
	GLint uniform_model;
	float xOffset, yOffset;

	virtual void GenerateBuffers()=0;
	virtual void InitBuffers();
	virtual void DrawBuffers()=0;
	void PushIntoVector(std::vector<float> &cs, float* coord, float *normal, float* colour);
	void GenerateArrayBuffer(GLuint& vbo, std::vector<float>& vertices);
	void GenerateElementBuffer(GLuint& ibo, std::vector<unsigned short>& elements);


};

} /* namespace Tetris3D */

#endif /* ABSTRACTMODELPIECE_H_ */
