/*
 * OpenGLManager.h
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 *
 *  Source: http://www.rastertek.com/gl40tut03.html
 */

#ifndef OPENGLMANAGER_H_
#define OPENGLMANAGER_H_

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library

#define GLM_MESSAGES
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>	// TODO Auto-generated destructor stub

#include "../Logger.h"

namespace Tetris3D {

class OpenGLManager {
public:
	OpenGLManager(int screenWidth, int screenHeight);
	virtual ~OpenGLManager();

	void Init(OpenGLManager* manager);
	void Shutdown();
	void BeginScene(float, float, float, float);
	void EndScene();

	GLFWwindow* GetWindow() {
		return window;
	}

private:
	void OnWindowResize(GLFWwindow* window, int width, int height);
	void OnError(int error, const char* description);
	void onDebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message);

	static void glfw_onResize(GLFWwindow* window, int w, int h) {
		manager->OnWindowResize(window, w, h);
	}

	static void glfw_error_callback(int error, const char* description) {
		manager->OnError(error, description);
	}

	static void APIENTRY gl_debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
			const GLchar* message, GLvoid* userParam) {
		reinterpret_cast<OpenGLManager *>(userParam)->onDebugMessage(source, type, id, severity, length, message);
	}

	static Tetris3D::OpenGLManager* manager;
	GLFWwindow* window;
	int screenWidth;
	int screenHeight;
	log4cpp::Category* logger;
};

} /* namespace Tetris3D */

#endif /* OPENGLMANAGER_H_ */
