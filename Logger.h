/*
 * Logger.h
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <log4cpp/Category.hh>
#include <log4cpp/PropertyConfigurator.hh>

namespace Tetris3D {

class Logger {
public:
	Logger();
	virtual ~Logger();

	static log4cpp::Category* GetLogger();

public:
	static log4cpp::Category* root;
};

} /* namespace Tetris3D */

#endif /* LOGGER_H_ */
