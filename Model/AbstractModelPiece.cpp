/*
 * AbstractModelPiece.cpp
 *
 *  Created on: 22 Dec 2013
 *      Author: bert
 */

#include "AbstractModelPiece.h"

namespace Tetris3D {

AbstractModelPiece::AbstractModelPiece(OpenGLProgram* program) {
	logger = Logger::GetLogger();
	logger->info("Initialising abstract model piece.");
	this->program = program;
	isWireFrame = false;
	sideLength = 2.0; //!
	xOffset = -5.0; //!
	yOffset = 14.0; //!

	this->attribute_coord3d = program->GetAttributeCoord3d();
	this->attribute_colour = program->GetAttributeColour();
	this->attribute_normal = program->GetAttributeNormal();
	this->uniform_model = program->GetUniformModel();

	logger->info("Initialised abstract model piece.");
}

AbstractModelPiece::~AbstractModelPiece() {
	program = 0;
	logger = 0;
}

void AbstractModelPiece::Render(bool isGenerateBuffers) {

	if (isGenerateBuffers) {
		GenerateBuffers();
	}

	if (isWireFrame) {
		// Turn on wireframe mode
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);
	}

	InitBuffers();

	DrawBuffers();

	if (isWireFrame) {
		// Turn off wireframe mode
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
	}
}

void AbstractModelPiece::PushIntoVector(std::vector<float> &cs, float* coord, float *normal, float* colour) {
	cs.push_back(coord[0]);
	cs.push_back(coord[1]);
	cs.push_back(coord[2]);

	cs.push_back(normal[0]);
	cs.push_back(normal[1]);
	cs.push_back(normal[2]);

	cs.push_back(colour[0]);
	cs.push_back(colour[1]);
	cs.push_back(colour[2]);
}

void AbstractModelPiece::InitBuffers() {
	glEnableVertexAttribArray(attribute_coord3d);
	glEnableVertexAttribArray(attribute_normal);
	glEnableVertexAttribArray(attribute_colour);

	glm::mat4 translate = glm::mat4(1.0f);
	glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(translate));

	glVertexAttribPointer(attribute_coord3d, 3, GL_FLOAT, GL_FALSE, sizeof(struct VertexStructure),  // stride
	0);  // offset

	glVertexAttribPointer(attribute_normal, 3,
	GL_FLOAT,
	GL_FALSE, sizeof(struct VertexStructure),  // stride
	(GLvoid*) offsetof(struct VertexStructure, normal));

	glVertexAttribPointer(attribute_colour, 3,
	GL_FLOAT,
	GL_FALSE, sizeof(struct VertexStructure),  // stride
	(GLvoid*) offsetof(struct VertexStructure, colour));

}

void AbstractModelPiece::GenerateArrayBuffer(GLuint& vbo,std::vector<float>& vertices) {
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &vbo);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void AbstractModelPiece::GenerateElementBuffer(GLuint& ibo,std::vector<unsigned short>& elements) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &ibo);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(unsigned short), &elements[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

} /* namespace Tetris3D */
