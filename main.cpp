/*
 * main.cpp
 *
 *  Created on: 20 Dec 2013
 *      Author: bert
 */

#include "Application.h"

int main() {

	Tetris3D::Application* app = new Tetris3D::Application();

	app->Init();
	app->Run();

	delete app;

	return 0;
}

