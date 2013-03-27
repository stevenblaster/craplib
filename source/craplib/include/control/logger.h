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


//okay hau die sachen vom config erstmal direkt in die logger klasse, dass man von aussen über crap::logger::type usw zugreifen kann, dann kannst auch gleich die static_string klasse für den text verwenden
//[20:07:40] Nikolaus Pöttler: k
//[20:08:13] Steffen: ausserdem nimm size_t32 statt size_t, weil wenn mans 64bit kompiliert brauchts immer 8 byte statt 4 byte, beim size_t32 is immer 32
//[20:08:24] Nikolaus Pöttler: roger that
//[20:08:29] Steffen: und glaub net dass ma so grosse zahlen brauchen ^^
//[20:08:50] Nikolaus Pöttler: du das war einfach iwas.. short würd reichen^^
//[20:08:58] Nikolaus Pöttler: 32 verscheidene lvl sind scho einiges :D
//[20:09:51] Steffen: wennst immer noch drüber nachdenkst das mit der va-list ginge, halt vorne was freilassen wennst sie in den buffer parst
//[20:10:06] Nikolaus Pöttler: und wie?
//[20:10:16] Steffen: naja wennst zum beispiel 4 byte vorher frei brauchst
//[20:10:35] Steffen: mach einfach &(buffer[4])
//[20:11:01] Nikolaus Pöttler: mkay
//[20:11:05] Steffen: oder (buffer+4) geht auch

#pragma once

#ifndef CRAP_CONTROL_LOGGER_H
#define CRAP_CONTROL_LOGGER_H

#include "crap.h"
#include "container/staticstring.h"
#include "config/config_types.h"
#include "config/config_logger.h"

namespace crap
{
	#define CRAP_LOG_INFO(channel,msg, ...) do{	\
	/*PARSE THROUGH INTRUSIVE LINKED LIST*/		\
	while(0)

	
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
			return true;
		}
	};

	struct verbosity_filter_policy
	{
		bool filter(const size_t32 channel, const size_t32 type)
		{
			return type <= CRAP_LOGGER_VERBOSITY_LEVEL;
		}
	};

	struct channel_filter_policy
	{
		bool filter(const size_t32 channel, const size_t32 type)
		{
			return channel == CRAP_LOGGER_FILTER_CHANNEL;
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

struct IntrusiveListNode {
  IntrusiveListNode* next;
  IntrusiveListNode* prev;
};

struct IntrusiveList {
	IntrusiveListNode root;
	size_t32 _offset;

	IntrusiveList(size_t32 offset) {
		_offset = offset;
		root.next = &root;
		root.prev = &root;
	}

	void add(IntrusiveListNode* node, IntrusiveListNode* prev, IntrusiveListNode* next) {
		node->next = next;
		node->prev = prev;
		next->prev = node;
		prev->next = node;
	}

	void remove(IntrusiveListNode* node) {
		node->next->prev = node->prev;
		node->prev->next = node->next;
		node->next = NULL;
		node->prev = NULL;
	}

	void add_head(IntrusiveListNode * node) {
		add(node, &root, root.next);
	}
};




/******************************************************************************
*
*   List definition macros
*
***/

// Define a linked list:
// T    = type of object being linked
// link = member within object which is the link field
#define LIST_DECLARE(T, link) TListDeclare<T, offsetof(T, link)>

// Define a field within a structure that will be used to link it into a list
#define LIST_LINK(T) TLink<T>

// Define a pointer to a list
#define LIST_PTR(T) TList<T> *


/******************************************************************************
*
*   TLink
*
***/

//=============================================================================
template<class T>
class TLink {
public:
    ~TLink ();
    TLink ();

    bool IsLinked () const;
    void Unlink ();

    T * Prev ();
    T * Next ();
    const T * Prev () const;
    const T * Next () const;

    // For use by list-type classes, not user code;
    // the alternative is to friend TList<T>, THash<T>,
    // and (eventually) many other structures.
    TLink (size_t offset);
    void SetOffset (size_t offset);
    TLink<T> * NextLink ();
    TLink<T> * PrevLink ();
    void InsertBefore (T * node, TLink<T> * nextLink);
    void InsertAfter (T * node, TLink<T> * prevLink);

private:
    T *         m_nextNode; // pointer to the next >object<
    TLink<T> *  m_prevLink; // pointer to the previous >link field<
    void RemoveFromList ();

    // Hide copy-constructor and assignment operator
    TLink (const TLink &);
    TLink & operator= (const TLink &);
};

//=============================================================================
template<class T>
TLink<T>::~TLink () {
    RemoveFromList();
}

//=============================================================================
template<class T>
TLink<T>::TLink () {
    // Mark this node as the end of the list, with no link offset
    m_nextNode = (T *) ((size_t) this + 1 - 0);
    m_prevLink = this;
}

//=============================================================================
template<class T>
TLink<T>::TLink (size_t offset) {
    // Mark this node as the end of the list, with the link offset set
    m_nextNode = (T *) ((size_t) this + 1 - offset);
    m_prevLink = this;
}

//=============================================================================
template<class T>
void TLink<T>::SetOffset (size_t offset) {
    // Mark this node as the end of the list, with the link offset set
    m_nextNode = (T *) ((size_t) this + 1 - offset);
    m_prevLink = this;
}

//=============================================================================
template<class T>
TLink<T> * TLink<T>::NextLink () {
    // Calculate the offset from a node pointer to a link structure
    size_t offset = (size_t) this - ((size_t) m_prevLink->m_nextNode & ~1);

    // Get the link field for the next node
    return (TLink<T> *) (((size_t) m_nextNode & ~1) + offset);
}

//=============================================================================
template<class T>
void TLink<T>::RemoveFromList () {
    NextLink()->m_prevLink = m_prevLink;
    m_prevLink->m_nextNode = m_nextNode;
}

//=============================================================================
template<class T>
void TLink<T>::InsertBefore (T * node, TLink<T> * nextLink) {
    RemoveFromList();

    m_prevLink = nextLink->m_prevLink;
    m_nextNode = m_prevLink->m_nextNode;

    nextLink->m_prevLink->m_nextNode = node;
    nextLink->m_prevLink = this;
}

//=============================================================================
template<class T>
void TLink<T>::InsertAfter (T * node, TLink<T> * prevLink) {
    RemoveFromList();

    m_prevLink = prevLink;
    m_nextNode = prevLink->m_nextNode;

    prevLink->NextLink()->m_prevLink = this;
    prevLink->m_nextNode = node;
}

//=============================================================================
template<class T>
bool TLink<T>::IsLinked () const {
    return m_prevLink != this;
}

//=============================================================================
template<class T>
void TLink<T>::Unlink () {
    RemoveFromList();

    // Mark this node as the end of the list with no link offset
    m_nextNode = (T *) ((size_t) this + 1);
    m_prevLink = this;
}

//=============================================================================
template<class T>
TLink<T> * TLink<T>::PrevLink () {
    return m_prevLink;
}

//=============================================================================
template<class T>
T * TLink<T>::Prev () {
    T * prevNode = m_prevLink->m_prevLink->m_nextNode;
    if ((size_t) prevNode & 1)
        return NULL;
    return prevNode;
}

//=============================================================================
template<class T>
const T * TLink<T>::Prev () const {
    const T * prevNode = m_prevLink->m_prevLink->m_nextNode;
    if ((size_t) prevNode & 1)
        return NULL;
    return prevNode;
}

//=============================================================================
template<class T>
T * TLink<T>::Next () {
    if ((size_t) m_nextNode & 1)
        return NULL;
    return m_nextNode;
}

//=============================================================================
template<class T>
const T * TLink<T>::Next () const {
    if ((size_t) m_nextNode & 1)
        return NULL;
    return m_nextNode;
}


/******************************************************************************
*
*   TList
*
***/

//=============================================================================
template<class T>
class TList {
public:
    ~TList ();
    TList ();

    bool Empty () const;
    void UnlinkAll ();
    void DeleteAll ();

    T * Head (); 
    T * Tail ();
    const T * Head () const;
    const T * Tail () const;

    T * Prev (T * node);
    T * Next (T * node);
    const T * Prev (const T * node) const;
    const T * Next (const T * node) const;

    void InsertHead (T * node);
    void InsertTail (T * node);
    void InsertBefore (T * node, T * before);
    void InsertAfter (T * node, T * after);

private:
    TLink<T>    m_link;
    size_t      m_offset;

    TList (size_t offset);
    TLink<T> * GetLinkFromNode (const T * node) const;
    template<class T, size_t offset> friend class TListDeclare;

    // Hide copy-constructor and assignment operator
    TList (const TList &);
    TList & operator= (const TList &);
};

//=============================================================================
template<class T>
TList<T>::~TList () {
    UnlinkAll();
}

//=============================================================================
template<class T>
TList<T>::TList () :
    m_link(),
    m_offset((size_t) -1)
{}

//=============================================================================
template<class T>
TList<T>::TList (size_t offset) :
    m_link(offset),
    m_offset(offset)
{}

//=============================================================================
template<class T>
bool TList<T>::Empty () const {
    return m_link.Next() == NULL;
}

//=============================================================================
template<class T>
void TList<T>::UnlinkAll () {
    for (;;) {
        TLink<T> * link = m_link.PrevLink();
        if (link == &m_link)
            break;
        link->Unlink();
    }
}

//=============================================================================
template<class T>
void TList<T>::DeleteAll () {
    while (T * node = m_link.Next())
        delete node;
}

//=============================================================================
template<class T>
T * TList<T>::Head () {
    return m_link.Next();
}

//=============================================================================
template<class T>
T * TList<T>::Tail () {
    return m_link.Prev();
}

//=============================================================================
template<class T>
const T * TList<T>::Head () const {
    return m_link.Next();
}

//=============================================================================
template<class T>
const T * TList<T>::Tail () const {
    return m_link.Prev();
}

//=============================================================================
template<class T>
T * TList<T>::Prev (T * node) {
    return GetLinkFromNode(node)->Prev();
}

//=============================================================================
template<class T>
const T * TList<T>::Prev (const T * node) const {
    return GetLinkFromNode(node)->Prev();
}

//=============================================================================
template<class T>
T * TList<T>::Next (T * node) {
    return GetLinkFromNode(node)->Next();
}

//=============================================================================
template<class T>
const T * TList<T>::Next (const T * node) const {
    return GetLinkFromNode(node)->Next();
}

//=============================================================================
template<class T>
void TList<T>::InsertHead (T * node) {
    InsertAfter(node, NULL);
}

//=============================================================================
template<class T>
void TList<T>::InsertTail (T * node) {
    InsertBefore(node, NULL);
}

//=============================================================================
template<class T>
void TList<T>::InsertBefore (T * node, T * before) {
    GetLinkFromNode(node)->InsertBefore(
        node,
        before ? GetLinkFromNode(before) : &m_link
    );
}

//=============================================================================
template<class T>
void TList<T>::InsertAfter (T * node, T * after) {
    GetLinkFromNode(node)->InsertAfter(
        node,
        after ? GetLinkFromNode(after) : &m_link
    );
}

//=============================================================================
template<class T>
TLink<T> * TList<T>::GetLinkFromNode (const T * node) const {
    return (TLink<T> *) ((size_t) node + m_offset);
}

/******************************************************************************
*
*   TListDeclare - declare a list with a known link offset
*
***/

//=============================================================================
template<class T, size_t offset>
class TListDeclare : public TList<T> {
public:
    TListDeclare ();
};

//=============================================================================
template<class T, size_t offset>
TListDeclare<T, offset>::TListDeclare () : TList<T>(offset)
{}


//===================================
// MIT License
//
// Copyright (c) 2010 by Patrick Wyatt
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//===================================


class base_logger
{
	public:
		virtual ~base_logger(void) {}
		virtual void log(size_t channel, size_t type,  const char* file, const int line, const char* format, ...) = 0;
		IntrusiveListNode logger_list_node;
		//LIST_LINK(base_logger) _logger_list_node;
};

//LIST_DECLARE(base_logger, _logger_list_node) listByData;
//LIST_PTR(base_logger) m_listPtr = &listByData;

IntrusiveList logger_list(offsetof(base_logger,logger_list_node));

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
				vsprintf_s(&(buffer[c]), format, args );
				va_end( args );
				buffer[CRAP_LOGGER_MSG_SIZE-1] = 0;
				_writer.write(buffer);
			}
		}
};

}

#endif // CRAP_CONTROL_LOGGER_H