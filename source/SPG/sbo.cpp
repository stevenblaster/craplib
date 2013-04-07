#include "precompiled.h"

#include "opengl/shader.h"
#include "container/fixedstring.h"
#include "contentmanager.h"
#include "shadercontent.h"

#include "sbo.h"

sbo::sbo( const crap::string64& vs, const crap::string64& ps, content_manager* cm ) : _program(0)
{
	shader_content sc_vs;
	cm->create_content( vs , &sc_vs, type_name::shader );
	crap::object vs_o = crap::shader::compile( sc_vs.data.cstring(), crap::vertex_shader );

	shader_content sc_ps;
	cm->create_content( ps , &sc_ps, type_name::shader );
	crap::object ps_o = crap::shader::compile( sc_ps.data.cstring(), crap::fragment_shader );

	crap::program tmp_program = crap::shader::link( vs_o, ps_o, 0 );
	_program._id = tmp_program._id;
	tmp_program._id = 0;

	sc_vs.~sc_vs();
	sc_ps.~sc_ps();
	cm->delete_content( vs , &sc_vs, type_name::shader );
	cm->delete_content( ps , &sc_ps, type_name::shader );
}

crap::program* sbo::operator->( void )
{
	return &_program;
}

crap::program& sbo::operator*( void )
{
	return _program;
}
