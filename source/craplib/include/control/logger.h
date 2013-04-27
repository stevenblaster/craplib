////////////////////////////////////////////////////////
//	CRAP Library
//!		@file logger.h
//
//	Author(s):
//! 	@author Nikolaus Poettler <nikolaus.poettler@gmail.com>
//!		@author Steffen Kopany <steffen@kopany.info>
//
//	Copyright:
//!		@copyright Copyright (c) 2013 Nikolaus Poettler Credit Stefan Reinalter
//
//	Description:
//!		@brief The base of a policy based logger
//
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////


#pragma once

#ifndef CRAP_CONTROL_LOGGER_H
#define CRAP_CONTROL_LOGGER_H

#include "crap.h"
#include "control/converter.h"
#include "container/fixedstring.h"
#include "container/intrusivelist.h"

#ifndef CRAP_CONFIG_NODEBUG 
#define CRAP_LOG_INFO(channel,msg, ...) do{ \
		crap::intrusive_list<crap::base_logger>::iterator it; \
		for(it = crap::intr_logger_list.begin(); it != crap::intr_logger_list.end(); ++it) \
		{ \
			it->log(channel,crap::log_info,__FILE__,__LINE__,msg,__VA_ARGS__); \
		} \
	} while(0)

#define CRAP_LOG_WARN(channel,msg, ...) do{ \
		crap::intrusive_list<crap::base_logger>::iterator it; \
		for(it = crap::intr_logger_list.begin(); it != crap::intr_logger_list.end(); ++it) \
		{ \
			it->log(channel,crap::log_warn,__FILE__,__LINE__,msg,__VA_ARGS__); \
		} \
	} while(0)
#define CRAP_LOG_ERROR(channel,msg, ...) do{ \
		crap::intrusive_list<crap::base_logger>::iterator it; \
		for(it = crap::intr_logger_list.begin(); it != crap::intr_logger_list.end(); ++it) \
		{ \
			it->log(channel,crap::log_error,__FILE__,__LINE__,msg,__VA_ARGS__); \
		} \
	} while(0)

#define CRAP_LOG_VERBOSE(channel,msg, ...) do{ \
		crap::intrusive_list<crap::base_logger>::iterator it; \
		for(it = crap::intr_logger_list.begin(); it != crap::intr_logger_list.end(); ++it) \
		{ \
			it->log(channel,crap::log_verbose,__FILE__,__LINE__,msg,__VA_ARGS__); \
		} \
	} while(0)
#else
	#define CRAP_LOG_INFO(channel,msg, ...)
	#define CRAP_LOG_WARN(channel,msg, ...)
	#define CRAP_LOG_ERROR(channel,msg, ...)
	#define CRAP_LOG_VERBOSE(channel,msg, ...)
#endif

namespace crap
{
	
//the current maximum is 10 (i dont think there is need for more)
const crap::fixed_string<CRAP_LOGGER_MSG_SIZE> channel_string[] = 
{
	"[CORE    ]",
	"[MEMORY  ]",
	"[OPENGL  ]"
};

const crap::fixed_string<CRAP_LOGGER_MSG_SIZE> type_string[] = 
{
	"(INFO   )",
	"(WARNING)",
	"(OPENGL )",
	"(VERBOSE)"
};

namespace filter_policy 
{
	struct no_filter_policy
	{
		bool filter(const log_channel channel, const log_type type)
		{
			// no filter at all
            return sizeof(channel) == sizeof(type); //returns true
		}
	};

	struct verbosity_filter_policy
	{
		bool filter(const log_channel channel, const log_type type)
		{
            return ( type <= CRAP_LOGGER_VERBOSITY_LEVEL ) && sizeof(channel) == sizeof(type);
		}
	};

	struct channel_filter_policy
	{
		bool filter(const log_channel channel, const log_type type)
		{
            return ( channel == CRAP_LOGGER_FILTER_CHANNEL ) && sizeof(channel) == sizeof(type);
		}
	};
	
#if CRAP_LOGGER_ALLOW_OVERRULE == 2
	//not yet evaluated
	template <log_type N> 
	struct verbosity_filter_policy
	{
		bool filter(const log_channel channel, const log_type type)
		{
			#if CRAP_LOGGER_ALLOW_OVERRULE == 1
				return type <= N;
			#else
				return type <= CRAP_LOGGER_VERBOSITY_LEVEL;
			#endif
		}
	};
	
	template <log_channel N>
	struct channel_filter_policy
	{
		bool filter(const log_channel channel, const log_type type)
		{
			#if CRAP_LOGGER_ALLOW_OVERRULE == 1
				return channel == N;
			#else
				return channel == CRAP_LOGGER_FILTER_CHANNEL;
			#endif
		}
	};
#endif

	template <class FilterPolicy1, class FilterPolicy2>
	struct composite_filter_policy
	{
		bool filter(const log_channel channel, const log_type type)
		{
			return (_policy1.filter(channel,type) && _policy2.filter(channel,type));
		}
 
	private:
		FilterPolicy1 _policy1;
		FilterPolicy2 _policy2;
	};
}

namespace format_policy 
{
	struct no_format_policy
	{
		i32 format(crap::fixed_string<CRAP_LOGGER_MSG_SIZE>* buffer = 0, log_channel channel = crap::log_core, log_type type = crap::log_info, string_t* file = 0, const i32 line = 0)
		{
			//"MSG"
			return 0;
		}
	};

	struct simple_format_policy
	{
		i32 format(crap::fixed_string<CRAP_LOGGER_MSG_SIZE>* buffer, log_channel channel, log_type type , string_t* file = 0, const i32 line = 0)
		{
			//"[Channel] (TYPE) MSG"
			*buffer = crap::channel_string[ channel ];
			*buffer += " ";
			*buffer += crap::type_string[ type ];
			*buffer += " ";
			return buffer->size();
		}
	};

	struct extended_format_policy
	{
		i32 format(crap::fixed_string<CRAP_LOGGER_MSG_SIZE>* buffer, log_channel channel, log_type type , string_t* file, const i32 line)
		{
			//"File.cpp:line [Channel] (Type) MSG"
			*buffer = file;
			*buffer += ":";
			*buffer += crap::convert< i32, fixed_string< CRAP_LOGGER_MSG_SIZE > >( line );
			*buffer += " ";
			*buffer += crap::channel_string[ channel ];
			*buffer += " ";
			*buffer += crap::type_string[ type ];
			*buffer += " ";
			return buffer->size();
		}
	};
}

namespace writer_policy
{	
	struct console_writer_policy
	{
		void write(string_t* buffer)
		{
			printf("%s\n",buffer); 
		}
	};

	struct stream_writer_policy
	{
		void write(string_t* buffer)
		{
			std::cout << buffer << std::endl; 
		}
	};
}

//struct IntrusiveListNode 
//{
//  IntrusiveListNode* next;
//  IntrusiveListNode* prev;
//};
//
//struct IntrusiveList 
//{
//	IntrusiveListNode root;
//	size_t32 _offset;
//
//	IntrusiveList(size_t32 offset) {
//		_offset = offset;
//		root.next = &root;
//		root.prev = &root;
//	}
//
//	void add(IntrusiveListNode* node, IntrusiveListNode* prev, IntrusiveListNode* next) 
//	{
//		node->next = next;
//		node->prev = prev;
//		next->prev = node;
//		prev->next = node;
//	}
//
//	void remove(IntrusiveListNode* node) 
//	{
//		node->next->prev = node->prev;
//		node->prev->next = node->next;
//		node->next = NULL;
//		node->prev = NULL;
//	}
//
//	void add_head(IntrusiveListNode * node) 
//	{
//		add(node, &root, root.next);
//	}
//};

//extern IntrusiveList logger_list;

class base_logger;

extern intrusive_list<base_logger> intr_logger_list;

class base_logger
{
	public:
		base_logger() : logger_list_node(this,&intr_logger_list,false) {};
		virtual ~base_logger(void) {}
		virtual void log(log_channel channel, log_type type,  string_t* file, const i32 line, string_t* format, ...) = 0;
		//IntrusiveListNode logger_list_node;
		intrusive_list_node<base_logger> logger_list_node;
};




template <typename filter, typename format, typename writer>
class logger : public base_logger
{
	private:
		filter _filter;
		format _formater;
		writer _writer;
	public:
		logger() 
		{
			//logger_list.add_head(&logger_list_node);
			intr_logger_list.push_back( &(this->logger_list_node) );
		}

		~logger(void) 
		{
			//logger_list.remove(&logger_list_node);
			intr_logger_list.remove( &(this->logger_list_node) );
		}

		virtual void log(log_channel channel, log_type type,  string_t* file, const i32 line, string_t* format_str, ...)

		{
			if (_filter.filter(channel,type))
			{
				crap::fixed_string<CRAP_LOGGER_MSG_SIZE> buffer;
				i32 c = _formater.format(&buffer, channel, type ,file,line);
				va_list args;
				va_start( args, format_str );
				c8* ptr = &buffer[c];
				vsprintf(ptr, format_str, args );
				va_end( args );
				_writer.write(buffer.cstring());
			}
		}
};

}

#endif // CRAP_CONTROL_LOGGER_H
