/*
 * Camera.h
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>	// TODO Auto-generated destructor stub

#include "../Logger.h"
#include "../OpenGL/OpenGLProgram.h"
#include "../InputManager.h"

namespace Tetris3D {

class Camera {
public:
	Camera(OpenGLProgram* program, InputManager* inputManager);
	virtual ~Camera();

	void Init(Camera* camera);
	void Render();

	bool IsNeedToRender();
private:
	log4cpp::Category* logger;

	OpenGLProgram* program;
	InputManager* inputManager;
	bool isRotate, isRotateX, isRotateY;
	bool isGetFirstReading;
	bool isNeedToRender;
	double prevxPos;
	double prevyPos;
	double yAngle, xAngle;

	glm::mat4 view;
	glm::vec3 cameraPosition;
	glm::vec3 cameraLookAt;
	glm::vec3 cameraUp;
	glm::vec3 cameraRight;

	void OnMouseButton(int button, int action, int mods);
	void OnMouseMove(double x, double y);
	void InitView();
	void GenerateView();
	bool ToggleButtonPressed(bool isPressed, bool isChecked);

	static Tetris3D::Camera* camera;

	static void SOnMouseButton(int button, int action, int mods) {
		camera->OnMouseButton(button, action, mods);
	}

	static void SOnMouseMove(double x, double y) {
		camera->OnMouseMove(x, y);
	}
};

} /* namespace Tetris3D */

#endif /* CAMERA_H_ */
