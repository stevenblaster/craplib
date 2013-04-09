////////////////////////////////////////////////////////
//	CRAP Library
//!		@file config_logger.h
//
//	Author(s):
//! 	@author Nikolaus Poettler <nikolaus.poettler@gmail.com>
//!		@author Steffen Kopany <steffen@kopany.info>
//
//	Copyright:
//!		@copyright Copyright (c) 2013 Nikolaus Poettler
//
//	Description:
//!		@brief Defines and config for crap logger
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_CONFIG_LOGGER_H
#define CRAP_CONFIG_LOGGER_H



namespace crap
{
	enum log_type 
	{
		log_info = 0,
		log_warning,
		log_error,
		log_verbose
	};

	enum log_channel
	{
		log_core = 0,
		log_memory,
		log_opengl
	};

	//rethink those..
	/*! @info: changed tose to macros (steffen) 
	static log_type CRAP_LOGGER_VERBOSITY_LEVEL = log_error;
	static log_channel CRAP_LOGGER_FILTER_CHANNEL = log_opengl;*/
}

#define CRAP_LOGGER_MSG_SIZE 512
#define CRAP_LOGGER_CHANNEL_SIZE 16
#define CRAP_LOGGER_ALLOW_OVERRULE 1

#define CRAP_LOGGER_VERBOSITY_LEVEL crap::log_error
#define CRAP_LOGGER_FILTER_CHANNEL crap::log_opengl

#endif