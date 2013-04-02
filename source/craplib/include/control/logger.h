////////////////////////////////////////////////////////
//	CRAP Library
//!		@file logger.h
//
//	Author(s):
//! 	@author Nikolaus Poettler <nikolaus.poettler@gmail.com>
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
#include "container/staticstring.h"
#include "config/config_types.h"
#include "config/config_logger.h"

#ifndef CRAP_CONFIG_NODEBUG 
#define CRAP_LOG_INFO(channel,msg, ...) do{ \
	crap::IntrusiveListNode* t; \
	t = crap::logger_list.root.next; \
	while(t != &crap::logger_list.root) { \
        reinterpret_cast<crap::base_logger *>(reinterpret_cast<char *>(t) - crap::logger_list._offset)->log(channel,crap::log_info,__FILE__,__LINE__,msg,__VA_ARGS__); \
		t = t->next; \
	} \
} while(0)

#define CRAP_LOG_WARN(channel,msg, ...) do{ \
	crap::IntrusiveListNode* t; \
	t = crap::logger_list.root.next; \
	while(t != &crap::logger_list.root) { \
        reinterpret_cast<crap::base_logger *>(reinterpret_cast<char *>(t) - crap::logger_list._offset)->log(channel,crap::log_warn,__FILE__,__LINE__,msg,__VA_ARGS__); \
		t = t->next; \
	} \
} while(0)

#define CRAP_LOG_ERROR(channel,msg, ...) do{ \
	crap::IntrusiveListNode* t; \
	t = crap::logger_list.root.next; \
	while(t != &crap::logger_list.root) { \
        reinterpret_cast<crap::base_logger *>(reinterpret_cast<char *>(t) - crap::logger_list._offset)->log(channel,crap::log_error,__FILE__,__LINE__,msg,__VA_ARGS__); \
		t = t->next; \
	} \
} while(0)

#define CRAP_LOG_VERBOSE(channel,msg, ...) do{ \
	crap::IntrusiveListNode* t; \
	t = crap::logger_list.root.next; \
	while(t != &crap::logger_list.root) { \
		reinterpret_cast<crap::base_logger *>(reinterpret_cast<char *>(t) - crap::logger_list._offset)->log(channel,crap::log_type::log_verbose,__FILE__,__LINE__,msg,__VA_ARGS__); \
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
const crap::static_string<CRAP_LOGGER_CHANNEL_SIZE> channel_string[] = 
{
	"[CORE    ]",
	"[MEMORY  ]",
	"[OPENGL  ]"
};

namespace filter_policy 
{
	struct no_filter_policy
	{
		bool filter(const size_t32 channel, const size_t32 type)
		{
			// no filter at all
            return sizeof(channel)==sizeof(type);
		}
	};

	struct verbosity_filter_policy
	{
		bool filter(const size_t32 channel, const size_t32 type)
		{
            return type <= (size_t32) CRAP_LOGGER_VERBOSITY_LEVEL && sizeof(channel)==sizeof(type);
		}
	};

	struct channel_filter_policy
	{
		bool filter(const size_t32 channel, const size_t32 type)
		{
            return channel == (size_t32) CRAP_LOGGER_FILTER_CHANNEL && sizeof(channel)==sizeof(type);
		}
	};
	
	//This could be used to make loggers that overrule the config
	/*
	//in config_logger.h
	#define CRAP_LOGGER_ALLOW_OVERRULE 1
	
	template <int N> 
	struct verbosity_filter_policy
	{
		bool filter(const size_t32 channel, const size_t32 type)
		{
			#if CRAP_LOGGER_ALLOW_OVERRULE == 1
				return type <= N;
			#else
				return type <= CRAP_LOGGER_VERBOSITY_LEVEL;
			#endif
		}
	};
	
	template <int N>
	struct channel_filter_policy
	{
		bool filter(const size_t32 channel, const size_t32 type)
		{
			#if CRAP_LOGGER_ALLOW_OVERRULE == 1
				return channel == N;
			#else
				return channel == CRAP_LOGGER_FILTER_CHANNEL;
			#endif
		}
	};
	
	*/

	template <class FilterPolicy1, class FilterPolicy2>
	struct composite_filter_policy
	{
		bool filter(const size_t32 channel, const size_t32 type)
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
		void format(char* buffer,const char* file, const int line)
		{
			//"MSG"
		}
	};

	struct simple_format_policy
	{
		void format(char* buffer,const char* file, const int line)
		{
			//"[Channel] (TYPE) MSG"
		}
	};

	struct extended_format_policy
	{
		void format(char* buffer,const char* file, const int line)
		{
			//"File.cpp:line [Channel] (Type) MSG"
		}
	};
}

namespace writer_policy
{	
	struct console_writer_policy
	{
		void write(const char* buffer)
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
		virtual void log(size_t channel, size_t type,  const char* file, const int line, const char* format, ...) = 0;
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

		virtual void log(size_t channel, size_t type,  const char* file, const int line, const char* format, ...)
		{
			if (_filter.filter(channel,type))
			{
				char buffer[CRAP_LOGGER_MSG_SIZE];
				//int c = _formater.format(buffer,file,line);
				va_list args;
				va_start( args, format );
				//vsprintf_s(&(buffer[c]), format, args );
				vsprintf(buffer, format, args );
				va_end( args );
				buffer[CRAP_LOGGER_MSG_SIZE-1] = 0;
				_writer.write(buffer);
			}
		}
};

}

#endif // CRAP_CONTROL_LOGGER_H
