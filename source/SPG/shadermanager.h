#pragma once

#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <map>

namespace crap
{
template<size_t32 S> class fixed_string;
typedef fixed_string<64> string64;
}

class sbo;
class content_manager;

class shader_manager
{
public:
	shader_manager( content_manager* cm );
	~shader_manager( void );

	void add( const crap::fixed_string<64>& vs, const crap::fixed_string<64>& ps );
	void set_current( const crap::fixed_string<64>& vs, const crap::fixed_string<64>& ps );
	bool is_current( const crap::fixed_string<64>& vs, const crap::fixed_string<64>& ps );

	void activate( void );

	sbo& current( void );

private:
	shader_manager( const shader_manager& other ) {}

	std::map< u32, sbo*> _shaderlist;
	content_manager* _cm;
	sbo* _current;
};

#endif //SHADERMANAGER_H