/*
 * GraphicsEngine.h
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#ifndef GRAPHICSENGINE_H_
#define GRAPHICSENGINE_H_

#include "../Logger.h"
#include "../OpenGL/OpenGLManager.h"
#include "../OpenGL/OpenGLProgram.h"
#include "Camera.h"
#include "../Model/Model.h"
#include "../Tetris/TetrisEngine.h"

namespace Tetris3D {

class GraphicsEngine {
public:
	GraphicsEngine(TetrisEngine* tetrisEngine,InputManager* inputManager);
	virtual ~GraphicsEngine();

	void Render();
	void Shutdown();

	OpenGLManager*& GetManager() {
		return manager;
	}

private:
	log4cpp::Category* logger;

	int screenWidth;
	int screenHeight;

	TetrisEngine* tetrisEngine;
	InputManager* inputManager;
	OpenGLManager* manager;
	OpenGLProgram* program;
	Model* model;
	Camera* camera;

	void Init();
};

} /* namespace Tetris3D */

#endif /* GRAPHICSENGINE_H_ */
