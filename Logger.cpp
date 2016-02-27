/*
 * Logger.cpp
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#include "Logger.h"

log4cpp::Category* Tetris3D::Logger::root = 0;

namespace Tetris3D {

Logger::Logger() {
}

Logger::~Logger() {
}

log4cpp::Category* Logger::GetLogger() {
		if (root == 0) {
			std::string initFileName = "log4cpp.properties";
			log4cpp::PropertyConfigurator::configure(initFileName);
			root = &(log4cpp::Category::getRoot());
		}
		return root;

	}

} /* namespace Tetris3D */
