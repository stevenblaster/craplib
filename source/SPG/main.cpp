#include "precompiled.h"
#include "contentmanager.h"

#include "audio/test.h"

int main( void )
{
	content_manager cm;
	cm.init( "spg.ini" );

	playme();

	return 0;
}