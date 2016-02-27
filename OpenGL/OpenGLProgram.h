/*
 * OpenGLProgram.h
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#ifndef OPENGLPROGRAM_H_
#define OPENGLPROGRAM_H_

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library

#define GLM_MESSAGES
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>	// TODO Auto-generated destructor stub

#include "shader_utils.h"

#include "../Logger.h"

namespace Tetris3D {

class OpenGLProgram {
public:
	OpenGLProgram();
	virtual ~OpenGLProgram();

	void Render();

	GLint GetAttributeColour() const {
		return attribute_colour;
	}
	GLint GetAttributeCoord3d() const {
		return attribute_coord3d;
	}
	GLint GetAttributeNormal() const {
		return attribute_normal;
	}
	GLint GetUniformModel() const {
		return uniform_m;
	}
	GLint GetUniformProjection() const {
		return uniform_p;
	}
	GLint GetUniformView() const {
		return uniform_v;
	}

private:
	GLuint program;
	GLuint vs, fs;
	GLint attribute_coord3d, attribute_colour, attribute_normal;
	GLint uniform_m, uniform_v, uniform_p;
	log4cpp::Category* logger;

	int Init();
};

} /* namespace Tetris3D */

#endif /* OPENGLPROGRAM_H_ */
