#include "precompiled.h"

#include "opengl/shader.h"
#include "container/fixedstring.h"
#include "contentmanager.h"
#include "shadercontent.h"

#include "sbo.h"

sbo::sbo( const crap::string64& vs, const crap::string64& ps, content_manager* cm )
{
	shader_content sc_vs;
	cm->create_content( vs , &sc_vs, type_name::shader );

	shader_content sc_ps;
	cm->create_content( ps , &sc_ps, type_name::shader );

	crap::object vs_o = crap::shader::compile( sc_vs.data, crap::vertex_shader );
	crap::object ps_o = crap::shader::compile( sc_vs.data, crap::fragment_shader );

	*_program = crap::shader::link( vs_o, ps_o, 0 );

	cm->delete_content( vs , &sc_vs, type_name::shader );
	cm->create_content( ps , &sc_ps, type_name::shader );
}

crap::program* sbo::operator->( void )
{
	return _program;
}