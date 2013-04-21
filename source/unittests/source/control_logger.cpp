#include "UnitTest++.h"
#include "crap.h"

//lib includes
#include "control/logger.h"

/*
#define CRAP_LOGGER_MSG_SIZE 512
#define CRAP_LOGGER_CHANNEL_SIZE 16
#define CRAP_LOGGER_ALLOW_OVERRULE 1

#define CRAP_LOGGER_VERBOSITY_LEVEL crap::log_error
#define CRAP_LOGGER_FILTER_CHANNEL crap::log_opengl
*/

namespace
{
	typedef crap::logger<crap::filter_policy::no_filter_policy,crap::format_policy::no_format_policy,crap::writer_policy::console_writer_policy> NoNoConsoleLogger;
	typedef crap::logger<crap::filter_policy::channel_filter_policy,crap::format_policy::no_format_policy,crap::writer_policy::console_writer_policy> ChNoConsoleLogger;

TEST(ControlLoggerTitle)
{
    std::cout << "Testing \"control/logger.h\"" << std::endl;
}

TEST(ControlLoggerNoNoC)
{	
	std::cout << "\tcrap::no filter no format console logger" << std::endl;
	NoNoConsoleLogger nnc;
	CRAP_LOG_INFO(crap::log_core,"Core Channel Test %d.",10);
	//CHECK_EQUAL( true, less_object(10,11) );
}

TEST(ControlLoggerNoNoCToBig)
{
	//std::cout << "\tcrap::no filter no format console logger MSG Size to big" << std::endl;
	//NoNoConsoleLogger nnc;
	//CRAP_LOG_INFO(crap::log_channel::log_core,"Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test Test  %d.",10);
	////CHECK_EQUAL( false, less_object(11,10) );
}

TEST(ControlLoggerNoNoCNothing)
{
	std::cout << "\tcrap::no filter no format console logger no msg no va_args" << std::endl;
	NoNoConsoleLogger nnc;
	CRAP_LOG_INFO(crap::log_core,"", 1);
	//CHECK_EQUAL( false, less_object(11,11) );
}

TEST(ControlLoggerNoNoCNothingWithArgs)
{
	std::cout << "\tcrap::no filter no format console logger no msg but va_args" << std::endl;
	NoNoConsoleLogger nnc;
	CRAP_LOG_INFO(crap::log_core,"",1,2,3,4);
	//CHECK_EQUAL( true, greater_object(11,10) );
}
}   // namespace

