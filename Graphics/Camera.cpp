/*
 * Camera.cpp
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#include "Camera.h"

Tetris3D::Camera* Tetris3D::Camera::camera = 0;

namespace Tetris3D {

Camera::Camera(OpenGLProgram* program, InputManager* inputManager) {
	logger = Logger::GetLogger();
	logger->info("Starting Camera.");
	this->program = program;
	this->inputManager = inputManager;
	this->inputManager->RegisterOnMouseButton(Camera::SOnMouseButton);
	this->inputManager->RegisterOnMouseMove(Camera::SOnMouseMove);
	isRotate = false;
	isGetFirstReading = false;
	isRotateX = false;
	isRotateY = false;
	isNeedToRender = false;
	prevxPos = prevyPos = 0.0;
	yAngle = xAngle = 0.0;
	logger->info("Started Camera.");
}

Camera::~Camera() {
	logger->info("Stopping Camera.");
	program = 0;
	logger->info("Stopped Camera.");
}

void Camera::Init(Camera* camera) {
	logger->info("Initialising Camera.");
	Camera::camera = camera;

	InitView();

	logger->info("Initialised Camera.");
}

void Camera::InitView() {
	cameraPosition = glm::vec3(0.0, 0.0, 40.0);  // the position of your camera, in world space
	cameraLookAt = glm::vec3(0.0, 0.0, 0.0);  // where you want to look at, in world space
	cameraUp = glm::vec3(0.0, 1.0, 0.0); //up direction; probably glm::vec3(0,1,0), but (0,-1,0) would make you looking upside-down, which can be great too
	cameraRight = glm::vec3(1.0, 0.0, 0.0); //required when rotating the camera
	GenerateView();
}

void Camera::GenerateView() {
	view = glm::lookAt(cameraPosition, cameraLookAt, cameraUp);
	isNeedToRender = true;
}

bool Camera::ToggleButtonPressed(bool isPressed, bool isChecked) {

	if (isPressed) {
		return !isChecked;
	}
	return isChecked;
}

bool Camera::IsNeedToRender() {

	isRotateX = ToggleButtonPressed(inputManager->IsXPressed(), isRotateX);
	isRotateY = ToggleButtonPressed(inputManager->IsYPressed(), isRotateY);

	if (inputManager->IsCPressed()) {
		InitView();
	}
	return isNeedToRender;
}

void Camera::Render() {
	glUniformMatrix4fv(program->GetUniformView(), 1, GL_FALSE, glm::value_ptr(view));
}

void Camera::OnMouseButton(int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		std::ostringstream strs;
		strs << "MouseButton Left Press. Starting rotation. isRotateX:" << isRotateX << " isRotateY:" << isRotateY;
		logger->debug(strs.str());

		isRotate = true;
		isGetFirstReading = true;
	} else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		logger->debug("MouseButton Left Release. Stoping rotation.");
		isRotate = false;
	}
}

void Camera::OnMouseMove(double x, double y) {

	if (isRotate) {

		//std::ostringstream strs;
		//strs << "Rotate OnMouseMove X:" << x << " Y:" << y;
		//logger->debug(strs.str());

		if (isGetFirstReading) {
			isGetFirstReading = false;
			prevxPos = x;
			prevyPos = y;
			return;
		}
		isNeedToRender = false;
		if (isRotateX) {
			//pitch
			//logger->debug("RotateX");

			int delta = prevyPos - y;
			xAngle += (float) delta * 0.05f;

			glm::mat4 rotate = glm::mat4(1.0f);
			rotate = glm::rotate(rotate, (float) delta, cameraRight);
			cameraUp = glm::vec3(glm::normalize(rotate * glm::vec4(cameraUp, 0.0)));
			cameraPosition = glm::vec3(rotate * glm::vec4(cameraPosition, 0.0));

			isNeedToRender = true;
		}

		if (isRotateY) {
			//yaw
			//logger->debug("RotateY");

			int delta = x - prevxPos;
			yAngle += (float) delta * 0.05f;

			glm::mat4 rotate = glm::mat4(1.0f);
			rotate = glm::rotate(rotate, (float) delta, cameraUp);
			cameraRight = glm::vec3(glm::normalize(rotate * glm::vec4(cameraRight, 0.0)));
			cameraPosition = glm::vec3(rotate * glm::vec4(cameraPosition, 0.0));

			isNeedToRender = true;
		}

		if (isNeedToRender) {
			prevxPos = x;
			prevyPos = y;

			if (yAngle >= 360.0f)
				yAngle -= 360.0f;
			if (xAngle <= 0.0f)
				xAngle += 360.0f;

			GenerateView();
		}
	}
}

} /* namespace Tetris3D */
