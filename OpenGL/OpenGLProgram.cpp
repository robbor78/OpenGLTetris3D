/*
 * OpenGLProgram.cpp
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#include "OpenGLProgram.h"

namespace Tetris3D {

OpenGLProgram::OpenGLProgram() {
	logger = Logger::GetLogger();
	logger->info("Initialising OpenGL program.");
	Init();
	logger->info("Initialised OpenGL program.");

}

OpenGLProgram::~OpenGLProgram() {
	logger->info("Stopping OpenGL program.");

	glUseProgram(0);

	glDetachShader(program, vs);
	glDetachShader(program, fs);

	glDeleteShader(fs);
	glDeleteShader(vs);

	glDeleteProgram(program);

	program = -1;
	vs = -1;
	fs = -1;

	logger->info("Stopped OpenGL program.");
	logger = 0;
}

int OpenGLProgram::Init() {
	program = create_program("cube.v.glsl", "cube.f.glsl", vs, fs);
	if (program == 0)
		return 0;
	attribute_coord3d = get_attrib(program, "vertex_position");
	attribute_normal = get_attrib(program, "vertex_normal");
	attribute_colour = get_attrib(program, "vertex_colour");

	uniform_m = get_uniform(program, "model");
	uniform_v = get_uniform(program, "view");
	uniform_p = get_uniform(program, "projection");

	return 1;
}

void OpenGLProgram::Render() {
	glUseProgram(program);
}

} /* namespace Tetris3D */
