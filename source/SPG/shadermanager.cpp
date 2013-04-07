#include "precompiled.h"

#include "opengl/shader.h"
#include "container/fixedstring.h"
#include "stringhash.h"
#include "contentmanager.h"
#include "sbo.h"
#include "shadermanager.h"

shader_manager::shader_manager( content_manager* cm ) : _cm(cm)
{

}

shader_manager::~shader_manager( void )
{
	_shaderlist.clear();
}

void shader_manager::add( const crap::fixed_string<64>& vs, const crap::fixed_string<64>& ps )
{
	crap::string64 id_string = vs;
	id_string += ps;
	u32 str_hash = string_to_hash( id_string );
	_shaderlist.insert( std::pair< u32, sbo* >( str_hash, new sbo( vs, ps, _cm) ) );
}

void shader_manager::set_current( const crap::fixed_string<64>& vs, const crap::fixed_string<64>& ps )
{
	crap::string64 id_string = vs;
	id_string += ps;
	u32 str_hash = string_to_hash( id_string );
	_current = _shaderlist.find( str_hash )->second;
}

bool shader_manager::is_current( const crap::fixed_string<64>& vs, const crap::fixed_string<64>& ps )
{
	crap::string64 id_string = vs;
	id_string += ps;
	u32 str_hash = string_to_hash( id_string );
	sbo* check = _shaderlist.find( str_hash )->second;
	return check == _current;
}

void shader_manager::activate( void )
{
	(*_current)->activate();
}

sbo& shader_manager::current( void )
{
	return *_current;
}