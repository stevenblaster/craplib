#pragma once

#ifndef CONTENTMANAGER_H
#define CONTENTMANAGER_H

#include "container/map.h"
#include "container/fixedstring.h"
#include "stringhash.h"

namespace crap
{
	class memory_pool;
}

class content_manager
{
public:
	void init( const crap::string256& initfile, size_t32 memory = 10485760 /* 10 MB */ );

private:
	crap::memory_pool* _content_pool;
	std::map< u32, crap::string64 > _filelist;
};

#endif //CONTENTMANAGER_H