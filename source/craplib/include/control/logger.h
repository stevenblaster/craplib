////////////////////////////////////////////////////////
//	CRAP Library
//!		@file logger.h
//
//	Author(s):
//! 	@author Nikolaus Poettler <nikolaus.poettler@gmail.com>
//!		@author Steffen Kopany <steffen@kopany.info>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Nikolaus Poettler Credit Stefan Reinalter
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
/* all configs are in the crap header which
should be included first in every cpp of crap 
#include "config/config_types.h"
#include "config/config_logger.h"*/

#ifndef CRAP_CONFIG_NODEBUG 
#define CRAP_LOG_INFO(channel,msg, ...) do{ \
	crap::IntrusiveListNode* t; \
	t = crap::logger_list.root.next; \
	while(t != &crap::logger_list.root) { \
        reinterpret_cast<crap::base_logger *>(reinterpret_cast<c8*>(t) - crap::logger_list._offset)->log(channel,crap::log_info,__FILE__,__LINE__,msg,__VA_ARGS__); \
		t = t->next; \
	} \
} while(0)

#define CRAP_LOG_WARN(channel,msg, ...) do{ \
	crap::IntrusiveListNode* t; \
	t = crap::logger_list.root.next; \
	while(t != &crap::logger_list.root) { \
        reinterpret_cast<crap::base_logger *>(reinterpret_cast<c8*>(t) - crap::logger_list._offset)->log(channel,crap::log_warn,__FILE__,__LINE__,msg,__VA_ARGS__); \
		t = t->next; \
	} \
} while(0)

#define CRAP_LOG_ERROR(channel,msg, ...) do{ \
	crap::IntrusiveListNode* t; \
	t = crap::logger_list.root.next; \
	while(t != &crap::logger_list.root) { \
        reinterpret_cast<crap::base_logger *>(reinterpret_cast<c8*>(t) - crap::logger_list._offset)->log(channel,crap::log_error,__FILE__,__LINE__,msg,__VA_ARGS__); \
		t = t->next; \
	} \
} while(0)

#define CRAP_LOG_VERBOSE(channel,msg, ...) do{ \
	crap::IntrusiveListNode* t; \
	t = crap::logger_list.root.next; \
	while(t != &crap::logger_list.root) { \
		reinterpret_cast<crap::base_logger *>(reinterpret_cast<c8*>(t) - crap::logger_list._offset)->log(channel,crap::log_type::log_verbose,__FILE__,__LINE__,msg,__VA_ARGS__); \
		t = t->next; \
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
            return sizeof(channel) == sizeof(type);
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
		i32 format(crap::string512* buffer = 0, log_channel channel = crap::log_core, log_type type = crap::log_info, string_t* file = 0, const i32 line = 0)
		{
			//"MSG"
			return 0;
		}
	};

	struct simple_format_policy
	{
		i32 format(crap::string512* buffer, log_channel channel, log_type type , string_t* file = 0, const i32 line = 0)
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
		i32 format(crap::string512* buffer, log_channel channel, log_type type , string_t* file, const i32 line)
		{
			//"File.cpp:line [Channel] (Type) MSG"
			*buffer = file;
			*buffer += ":";
			*buffer += crap::convert<i32, string512>( line );
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
}

struct IntrusiveListNode 
{
  IntrusiveListNode* next;
  IntrusiveListNode* prev;
};

struct IntrusiveList 
{
	IntrusiveListNode root;
	size_t32 _offset;

	IntrusiveList(size_t32 offset) {
		_offset = offset;
		root.next = &root;
		root.prev = &root;
	}

	void add(IntrusiveListNode* node, IntrusiveListNode* prev, IntrusiveListNode* next) 
	{
		node->next = next;
		node->prev = prev;
		next->prev = node;
		prev->next = node;
	}

	void remove(IntrusiveListNode* node) 
	{
		node->next->prev = node->prev;
		node->prev->next = node->next;
		node->next = NULL;
		node->prev = NULL;
	}

	void add_head(IntrusiveListNode * node) 
	{
		add(node, &root, root.next);
	}
};

class base_logger
{
	public:
		virtual ~base_logger(void) {}
		virtual void log(size_t channel, size_t type,  string_t* file, const i32 line, string_t* format, ...) = 0;
		IntrusiveListNode logger_list_node;
};

extern IntrusiveList logger_list;

template <class filter_policy, class format_policy, class writer_policy>
class logger : public base_logger
{
	private:
		filter_policy _filter;
		format_policy _formatter;
		writer_policy _writer;
	public:
		logger() 
		{
			logger_list.add_head(&logger_list_node);
			//listByData.InsertHead(this);
		}

		~logger(void) 
		{
			logger_list.remove(&logger_list_node);
		}

		virtual void log(size_t channel, size_t type,  string_t* file, const i32 line, string_t* format, ...)
		{
			if (_filter.filter(channel,type))
			{
				crap::string512 buffer;
				i32 c = _formater.format(buffer,file,line);
				va_list args;
				va_start( args, format );
				vsprintf_s(&(buffer[c]), format, args );
				vsprintf(buffer, format, args );
				va_end( args );
				_writer.write(buffer);
			}
		}
};

}

#endif // CRAP_CONTROL_LOGGER_H
